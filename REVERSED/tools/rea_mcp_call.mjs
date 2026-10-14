// rea_mcp_call.mjs - drive REA's MCP server over stdio so one analysis session
// serves many tool calls.
//
// Why this exists: every CLI invocation (`rea decompile ...`) starts a *new*
// provider session, and each new Ghidra session re-imports and re-analyses
// groove.exe (~13 min, measured).  An MCP session imports once and then answers
// per-function calls in milliseconds.  This is also exactly what a client such
// as LM Studio/Bionic does when the server is registered in `mcp.json`.
//
//   node tools/rea_mcp_call.mjs <spec.json> [out.json]
//
// <spec.json>:
//   { "calls": [ { "name": "open_binary", "arguments": { ... }, "timeoutMs": 900000 } ] }
//
// Optional keys:
//   "dumpToolSchemas": ["open_binary"], "dumpToolSchemasOut": "schemas.json"
//
// Env: GHIDRA_INSTALL_DIR (required by REA), JAVA_HOME (optional but the JDK on
// PATH here is JDK 8, which Ghidra rejects - point it at a 21+ JDK).
import { spawn } from "node:child_process";
import { readFileSync, writeFileSync } from "node:fs";

const REA_PACKAGE = process.env.REA_PACKAGE ?? "rea-agents@6.4.0";

const callsFile = process.argv[2];
const outFile = process.argv[3];
if (!callsFile) {
  console.error("usage: node tools/rea_mcp_call.mjs <spec.json> [out.json]");
  process.exit(2);
}
const spec = JSON.parse(readFileSync(callsFile, "utf8"));

const launcher = process.env.REA_COMMAND;
const command = launcher ? ["/d", "/c", launcher, "mcp"] :
                          ["/d", "/c", "npx", "-y", REA_PACKAGE, "mcp"];
const child = spawn("cmd.exe", command, {
  env: { ...process.env },
  cwd: process.env.REA_CWD ?? process.cwd(),
  stdio: ["pipe", "pipe", "pipe"],
  windowsHide: true,
});

let buf = "";
const pending = new Map();
let nextId = 1;

child.stdout.on("data", (chunk) => {
  buf += chunk.toString("utf8");
  let idx;
  while ((idx = buf.indexOf("\n")) >= 0) {
    const line = buf.slice(0, idx);
    buf = buf.slice(idx + 1);
    if (!line.trim()) continue;
    let msg;
    try {
      msg = JSON.parse(line);
    } catch {
      process.stderr.write(`[non-json stdout] ${line.slice(0, 200)}\n`);
      continue;
    }
    if (msg.id != null && pending.has(msg.id)) {
      pending.get(msg.id)(msg);
      pending.delete(msg.id);
    }
  }
});

child.stderr.on("data", (c) => process.stderr.write(`[server] ${c.toString("utf8").slice(0, 300)}\n`));

function rpc(method, params, timeoutMs) {
  const id = nextId++;
  return new Promise((resolve, reject) => {
    const timer = setTimeout(() => reject(new Error(`timeout: ${method}`)), timeoutMs);
    pending.set(id, (m) => {
      clearTimeout(timer);
      resolve(m);
    });
    child.stdin.write(JSON.stringify({ jsonrpc: "2.0", id, method, params }) + "\n");
  });
}

const init = await rpc("initialize", {
  protocolVersion: "2025-06-18",
  capabilities: {},
  clientInfo: { name: "rea-driver", version: "1.0" },
}, 120000);
process.stderr.write(`[session] ${JSON.stringify(init.result?.serverInfo)}\n`);
child.stdin.write(JSON.stringify({ jsonrpc: "2.0", method: "notifications/initialized", params: {} }) + "\n");

if (spec.dumpToolSchemas) {
  const list = await rpc("tools/list", {}, 60000);
  const tools = (list.result?.tools ?? []).filter((t) => spec.dumpToolSchemas.includes(t.name));
  const out = {};
  for (const t of tools) out[t.name] = { description: t.description, inputSchema: t.inputSchema };
  writeFileSync(spec.dumpToolSchemasOut ?? "schemas.json", JSON.stringify(out, null, 2));
  process.stderr.write(`[schemas] wrote ${Object.keys(out).join(", ")}\n`);
  child.kill();
  process.exit(0);
}

const results = [];
for (const call of spec.calls) {
  const started = Date.now();
  let response;
  try {
    response = await rpc("tools/call", { name: call.name, arguments: call.arguments ?? {} }, call.timeoutMs ?? 1800000);
  } catch (error) {
    response = { error: String(error) };
  }
  const seconds = Number(((Date.now() - started) / 1000).toFixed(1));
  process.stderr.write(`[call] ${call.name} ${seconds}s\n`);
  const record = { name: call.name, arguments: call.arguments ?? {}, seconds, response };
  results.push(record);
  console.log(JSON.stringify(record));
}

if (outFile) writeFileSync(outFile, JSON.stringify(results, null, 2));
child.kill();
process.exit(0);
