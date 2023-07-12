from pathlib import Path
from subprocess import run
import shutil

WkPath = Path('src/arc/graphics/pokemon/icons')

for File in WkPath.glob('*'):
    New = File.rename(File.parent / f'7_{str(int(File.stem[2:])).zfill(8)}.bin')
    print(New.as_posix())