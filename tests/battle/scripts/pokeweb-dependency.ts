import { resolve } from "node:path";
import { fileURLToPath, pathToFileURL } from "node:url";

const repo = fileURLToPath(new URL("../../../", import.meta.url));
const pokeweb = resolve(process.env.POKEWEB_ROOT || resolve(repo, "../Port-Pokeweb/Pokeweb-Serverless"));

export function pokewebFile(path: string): URL {
  return pathToFileURL(resolve(pokeweb, path));
}
