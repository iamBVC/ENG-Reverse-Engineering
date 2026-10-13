"""Account for original assembly entries and every exported reconstruction body."""
import csv
import re
from collections import Counter
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent
sources = {p.stem: p for p in (ROOT / "decompiled").glob("sub_*.c")}
sources.update({p.stem: p for p in (ROOT / "src_recovered").glob("sub_*.c")})
with (ROOT / "functions.csv").open(newline="") as stream:
    entries = {row["name"]: row for row in csv.DictReader(stream)
               if re.fullmatch(r"sub_[0-9A-Fa-f]{6}", row["name"])}
clean_text = (ROOT / "src_generated/clean_subset.c").read_text()
included = set(re.findall(r"^/\* ==== (\w+) ==== \*/", clean_text, re.M))
runtime = set()
for filename in ("crt_bodies.txt", "substituted.txt"):
    for line in (ROOT / "harness" / filename).read_text().splitlines():
        if filename == "crt_bodies.txt":
            runtime.add(line.split("#")[0].strip())
calls = Counter(re.findall(r"\b(sub_[0-9A-F]{6})\s*\(", clean_text))
rows = []
for name in sorted(set(entries) | set(sources)):
    status = ("runtime replacement" if name in runtime else
              "included" if name in included else
              "exported; needs reconstruction" if name in sources else
              "not exported")
    address = int(name[4:], 16)
    rows.append({"name": name, "address": f"{address:08X}",
                 "region": "game" if address < 0x559000 else "runtime",
                 "status": status, "source": str(sources.get(name, "")),
                 "direct_references_in_included_code": max(0, calls[name] - (name in included))})
output = ROOT / "build/recovery_inventory.csv"
with output.open("w", newline="") as stream:
    writer = csv.DictWriter(stream, fieldnames=list(rows[0]))
    writer.writeheader()
    writer.writerows(rows)
print("Original assembly/export inventory:", dict(Counter(row["status"] for row in rows)))
print("Game entries remaining:")
pending = [row for row in rows if row["region"] == "game" and
           row["status"] in {"not exported", "exported; needs reconstruction"}]
for row in sorted(pending, key=lambda row: -row["direct_references_in_included_code"]):
    print(f"  {row['name']}: {row['status']}; direct references={row['direct_references_in_included_code']}")
print(output)
