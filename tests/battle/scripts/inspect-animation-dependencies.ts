/** Read-only inspection of repository-owned animation scripts and SPA assets. */
import { readFileSync } from "node:fs";
import { fileURLToPath } from "node:url";
import { decompileMoveAnimationBytes } from "@pokeweb/pokeweb/moveAnimationModel";
import { parseSpaArchive } from "@pokeweb/pokeweb/nitroSpa";

for (const token of process.argv.slice(2)) {
  const move = Number(token);
  if (!Number.isInteger(move) || move < 0 || move > 1023) throw new Error("Use numeric move IDs");
  const script = decompileMoveAnimationBytes(readFileSync(fileURLToPath(new URL(
    `../../../data/graphics/move_animations/5_${String(move).padStart(8, "0")}.bin`, import.meta.url))));
  console.log(JSON.stringify({ move, script }));
  for (const id of new Set([...script.matchAll(/^\s*LoadSPA\s+(\d+)/gm)].map(m => Number(m[1])))) {
    const archive = parseSpaArchive(readFileSync(fileURLToPath(new URL(
      `../../../data/graphics/move_spas/6_${String(id).padStart(8, "0")}.bin`, import.meta.url))));
    console.log(JSON.stringify({ spa: id, warnings: archive.warnings,
      resources: archive.resources.map(r => ({ index: r.index, texture: r.textureIndex, flags: r.flags })),
      textures: archive.textures.map(t => ({ index: t.index, width: t.width, height: t.height,
        format: t.format, shared: t.sharedTexId, bytes: t.textureSize, palette: t.paletteSize })) }));
  }
}
