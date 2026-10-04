"""Regression checks for portable reports and mechanically sanitized archives."""
from pathlib import Path
import json
import struct
import sys
import tempfile
import unittest
import zipfile

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
from pwan.report_paths import portable_report, report_path, write_report
from sanitize_private_artifacts import class_parts, sanitize_animation_text, sanitize_archive, sanitize_class
from check_source_privacy import check_content


def class_fixture():
    path = chr(90) + chr(58) + "\\legacy\\input.elf"
    values = [path.encode(), b"https://example.test/schema", b"relative/input.elf"]
    pool = b"".join(b"\1" + struct.pack(">H",len(v)) + v for v in values)
    # A double-width constant consumes an additional pool index.
    pool += b"\5" + b"\0"*8
    tail = b"opaque method code and attributes"
    return b"\xca\xfe\xba\xbe\0\0\0=" + struct.pack(">H",6) + pool + tail


class ReportPrivacy(unittest.TestCase):
    def test_internal_external_paths_and_idempotence(self):
        with tempfile.TemporaryDirectory() as directory:
            base = Path(directory) / "checkout"
            inside, outside = base / "assets/one.gif", Path(directory) / "inputs/two.gif"
            value = {"sources":[inside, str(outside)], "message":f"Missing '{inside}'",
                     "link":"https://example.test/home/reference", "count":42}
            result = portable_report(value, base)
            self.assertEqual(result["sources"], ["assets/one.gif", "../inputs/two.gif"])
            self.assertEqual(result["message"], "Missing 'assets/one.gif'")
            self.assertEqual(result["link"], value["link"])
            self.assertEqual(portable_report(result,base),result)
            self.assertEqual(report_path(outside,base), "../inputs/two.gif")

    def test_writer_normalizes_nested_paths_without_mutating_input(self):
        from pwan.report_paths import ROOT
        with tempfile.TemporaryDirectory() as directory:
            target = Path(directory) / "report.json"
            value = {"nested":{"front":ROOT / "assets/front.gif"}, "missing":None}
            write_report(target,value)
            self.assertEqual(json.loads(target.read_text())["nested"]["front"], "assets/front.gif")
            self.assertIsInstance(value["nested"]["front"],Path)

    def test_path_keys_are_normalized_and_collisions_fail_closed(self):
        from pwan.report_paths import ROOT
        absolute = str(ROOT / "assets/front.gif")
        self.assertEqual(portable_report({absolute: 42}), {"assets/front.gif": 42})
        with self.assertRaises(ValueError):
            portable_report({absolute: 42, "assets/front.gif": 43})

    @unittest.skipIf(sys.platform == "win32", "Only a foreign-drive path on POSIX")
    def test_foreign_filesystem_path_fails_closed(self):
        with self.assertRaises(ValueError):
            report_path(chr(90) + chr(58) + "\\legacy\\input.gif")

    def test_pwan_report_writers_do_not_bypass_normalization(self):
        import ast
        folder=Path(__file__).resolve().parents[1]/"pwan"
        for path in folder.glob("*.py"):
            if path.name == "report_paths.py": continue
            with self.subTest(path=path.name):
                for node in ast.walk(ast.parse(path.read_text())):
                    if isinstance(node,ast.Call) and isinstance(node.func,ast.Attribute) and node.func.attr=="write_text" and node.args:
                        value=node.args[0]
                        self.assertFalse(any(isinstance(item,ast.Call) and isinstance(item.func,ast.Attribute) and item.func.attr=="dumps"
                                             for item in ast.walk(value)))

    def test_checker_rejects_private_paths_but_not_relative_paths_or_urls(self):
        legacy=chr(90)+chr(58)+"\\legacy\\input.elf"
        self.assertIn("absolute host path",check_content(legacy.encode(),[]))
        self.assertIn("absolute host path",check_content((chr(90)+chr(58)+"\\input.elf").encode(),[]))
        self.assertEqual(check_content(b"../inputs/file.json https://example.test/home/reference",[]),[])
        self.assertEqual(check_content(b"line %d:\\n%s", []), [])
        self.assertEqual(check_content(b"sample-private-token",["sample-private-token"]),["private token"])


class ArchivePrivacy(unittest.TestCase):
    def test_constant_pool_rewrite_preserves_indices_code_and_urls(self):
        data=class_fixture()
        before,tail=class_parts(data)
        result=sanitize_class(data)
        after,new_tail=class_parts(result)
        self.assertEqual(after[0],(1,b"input.elf"))
        self.assertEqual(after[1:],before[1:])
        self.assertEqual(tail,new_tail)
        self.assertEqual(result,sanitize_class(result))

    def test_malformed_class_rejected(self):
        for data in (b"invalid",class_fixture()[:15]):
            with self.assertRaises(ValueError): sanitize_class(data)

    def test_archive_integrity_and_unrelated_payloads(self):
        with tempfile.TemporaryDirectory() as directory:
            path=Path(directory)/"bundle.jar"
            animation=b"\0animation payload\xff"
            with zipfile.ZipFile(path,"w",compression=zipfile.ZIP_DEFLATED) as archive:
                info=zipfile.ZipInfo("Sample.class")
                archive.writestr(info,class_fixture())
                info.external_attr=0
                archive.writestr("animation.bin",animation)
            original=path.read_bytes()
            self.assertEqual(sanitize_archive(path),["Sample.class"])
            self.assertEqual(path.read_bytes(),original)
            self.assertEqual(sanitize_archive(path,True),["Sample.class"])
            with zipfile.ZipFile(path) as archive:
                self.assertIsNone(archive.testzip())
                self.assertEqual(archive.namelist(),["Sample.class","animation.bin"])
                self.assertEqual(archive.getinfo("Sample.class").external_attr,0)
                self.assertEqual(archive.read("animation.bin"),animation)
            self.assertEqual(sanitize_archive(path,True),[])

    def test_signed_archive_refused(self):
        with tempfile.TemporaryDirectory() as directory:
            path=Path(directory)/"signed.jar"
            with zipfile.ZipFile(path,"w") as archive: archive.writestr("META-INF/EXAMPLE.SF",b"signature")
            with self.assertRaises(ValueError): sanitize_archive(path,True)

    def test_relative_imports_and_urls_are_not_scrubbed(self):
        text='import "../../Pokeweb-Serverless/src/nds/rom"; https://example.test/home/ref'
        self.assertEqual(sanitize_animation_text(text),text)


if __name__ == "__main__": unittest.main()
