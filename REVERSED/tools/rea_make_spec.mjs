// rea_make_spec.mjs - build a call spec for tools/rea_mcp_call.mjs out of the
// project's own tables.
//
//   node tools/rea_make_spec.mjs dossier  > spec.json   # analyze_function per stub
//   node tools/rea_make_spec.mjs batch    > spec.json   # one batch_decompile
//   node tools/rea_make_spec.mjs --all dossier          # every game function
//
// Note on names: the project keys functions by IDA's `sub_<addr>`.  Ghidra does
// not know those names - pass addresses (`0x404db0`) or Ghidra's own symbols
// (`FUN_00404db0`, `exception::~exception`).
import { readFileSync } from "node:fs";
import { dirname, resolve } from "node:path";
import { fileURLToPath } from "node:url";

const HERE = dirname(fileURLToPath(import.meta.url));
const ROOT = resolve(HERE, "..");
const TARGET = resolve(ROOT, "..", "WAD", "groove.exe");

const mode = process.argv[2] ?? "dossier";
const scope = process.argv[3] ?? "stubs";

/** IDA-keyed function addresses from the tables the project already maintains. */
function addresses() {
  if (scope === "all") {
    const csv = readFileSync(resolve(HERE, "..", "functions.csv"), "utf8");
    return csv
      .split(/\r?\n/)
      .slice(1)
      .map((l) => l.split(","))
      .filter((f) => f[0]?.startsWith("sub_") && f[4] === "game")
      .map((f) => "0x" + f[0].replace("sub_", ""));
  }
  const csv = readFileSync(resolve(ROOT, "src_generated", "link_stubs.csv"), "utf8");
  return csv
    .split(/\r?\n/)
    .filter((l) => l.startsWith("_sub_"))
    .map((l) => "0x" + l.split(",")[1].replace("sub_", ""));
}

const list = addresses();
const open = {
  name: "open_binary",
  arguments: { path: TARGET.replace(/\\/g, "/"), provider_id: "ghidra" },
  timeoutMs: 900000,
};

const calls = mode === "batch"
  ? [open, { name: "batch_decompile", arguments: { addresses: list }, timeoutMs: 1800000 }]
  : [open, { name: "binary_session", arguments: {}, timeoutMs: 60000 },
     ...list.map((a) => ({ name: "analyze_function", arguments: { procedure: a }, timeoutMs: 600000 }))];

console.log(JSON.stringify({ calls }, null, 2));
process.stderr.write(`[spec] mode=${mode} scope=${scope} procedures=${list.length}\n`);
