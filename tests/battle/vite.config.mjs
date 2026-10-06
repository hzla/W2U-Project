import { resolve } from "node:path";
import { fileURLToPath } from "node:url";

const repo = fileURLToPath(new URL("../../", import.meta.url));
const pokeweb = resolve(process.env.POKEWEB_ROOT || resolve(repo, "../Port-Pokeweb/Pokeweb-Serverless"));

// Reuse production ROM/save editors, not tests from the web application.
export default {
  root: repo,
  resolve: { alias: { "@pokeweb": resolve(pokeweb, "src") } },
  server: { fs: { allow: [repo, pokeweb] } },
  cacheDir: resolve(repo, "work/battle-tests/vite-cache"),
};
