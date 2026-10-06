/** Read-only inspection of repository-owned animation scripts and SPA assets. */
import { readFileSync } from "node:fs";
import { fileURLToPath } from "node:url";
import { decompileMoveAnimationBytes } from "@pokeweb/pokeweb/moveAnimationModel";
import { parseSpaArchive } from "@pokeweb/pokeweb/nitroSpa";
import { NintendoDSRom } from "@pokeweb/nds/rom";
import { NARC } from "@pokeweb/nds/narc";
import { createHash } from "node:crypto";

const args = process.argv.slice(2);
let rom: NintendoDSRom | undefined;
if (args[0] === "--rom") {
  if (!args[1]) throw new Error("--rom requires a ROM path");
  rom = new NintendoDSRom(readFileSync(args[1]), { fileData: "view" });
  args.splice(0, 2);
}
const scripts = rom && new NARC(rom.getFileByName("a/0/6/5"));
const particles = rom && new NARC(rom.getFileByName("a/0/0/6"));
const hash = (bytes: Uint8Array) => createHash("sha256").update(bytes).digest("hex");
for (const token of args) {
  const move = Number(token);
  if (!Number.isInteger(move) || move < 0 || move > 1023) throw new Error("Use numeric move IDs");
  const bytes = scripts ? scripts.files[move] : readFileSync(fileURLToPath(new URL(
    `../../../data/graphics/move_animations/5_${String(move).padStart(8, "0")}.bin`, import.meta.url)));
  if (!bytes) throw new Error(`Missing script member ${move}`);
  const script = decompileMoveAnimationBytes(bytes);
  console.log(JSON.stringify({ move, bytes: bytes.length, sha256: hash(bytes), script }));
  for (const id of new Set([...script.matchAll(/^\s*LoadSPA\s+(\d+)/gm)].map(m => Number(m[1])))) {
    const spa = particles ? particles.files[id] : readFileSync(fileURLToPath(new URL(
      `../../../data/graphics/move_spas/6_${String(id).padStart(8, "0")}.bin`, import.meta.url)));
    if (!spa) throw new Error(`Missing SPA member ${id}`);
    const archive = parseSpaArchive(spa);
    console.log(JSON.stringify({ spa: id, bytes: spa.length, sha256: hash(spa), warnings: archive.warnings,
      resources: archive.resources.map(r => ({ index: r.index, texture: r.textureIndex, flags: r.flags })),
      textures: archive.textures.map(t => ({ index: t.index, width: t.width, height: t.height,
        format: t.format, shared: t.sharedTexId, bytes: t.textureSize, palette: t.paletteSize })) }));
  }
}
