#!/usr/bin/env python3
"""Check the public source tree for likely accidental personal identifiers."""
import re
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
SKIP_DIRS = {".git", "build", "node_modules", "__pycache__"}
SKIP_SUFFIXES = {".png", ".jpg", ".jpeg", ".gif", ".webp", ".pdf", ".zip", ".exe", ".dll", ".so"}
# Comments/docs may describe patterns. Use narrow cases that only match actual-looking private values.
CHECKS = {
    "hardware MAC address": re.compile(r"(?<![\w])(?:[0-9a-fA-F]{2}:){5}[0-9a-fA-F]{2}(?![\w])"),
    "absolute user home": re.compile(r"/home/(?!USERNAME\b|user\b|<)[a-zA-Z][a-zA-Z0-9_.-]+/"),
    "Windows user directory": re.compile(r"[A-Za-z]:\\Users\\(?!USERNAME\b|user\b|<)[A-Za-z0-9_.-]+\\"),
    "email address": re.compile(r"(?<![\w])[-\w.]+@[-\w.]+\.[a-zA-Z]{2,}(?![\w])"),
    "private IPv4": re.compile(r"(?<![\d])(?:10\.\d{1,3}\.\d{1,3}\.\d{1,3}|192\.168\.\d{1,3}\.\d{1,3}|172\.(?:1[6-9]|2\d|3[01])\.\d{1,3}\.\d{1,3})(?![\d])"),
}

errors = []
checked = 0
for path in sorted(ROOT.rglob("*")):
    if not path.is_file() or any(part in SKIP_DIRS for part in path.relative_to(ROOT).parts):
        continue
    if path.suffix.lower() in SKIP_SUFFIXES:
        errors.append(f"Binary/unreviewable asset: {path.relative_to(ROOT)}")
        continue
    checked += 1
    try:
        txt = path.read_text(encoding="utf-8")
    except UnicodeError:
        errors.append(f"Non-UTF8 content: {path.relative_to(ROOT)}")
        continue
    for label, pattern in CHECKS.items():
        for match in pattern.finditer(txt):
            line = txt.count("\n", 0, match.start()) + 1
            errors.append(f"{path.relative_to(ROOT)}:{line}: possible {label}")
if errors:
    print("PUBLICATION PRIVACY CHECK FAILED:\n" + "\n".join(errors), file=sys.stderr)
    sys.exit(1)
print(f"PASS: inspected {checked} UTF-8 text files; no probable private identifiers or binaries found")
