from pathlib import Path
from subprocess import run
import shutil

WkPath = Path('src/arc/graphics/pokemon/icons')

for File in WkPath.glob('*'):
    New = File.rename(File.parent / f'7_{str(int(File.stem)).zfill(8)}{File.suffix}')
    print(New.as_posix())