# v0.2.0-rc2 — Community prerelease

An experimental OpenRGB RGB controller for the **EPOMAKER × AULA F75 MAX**, operating through the **2.4 GHz receiver** (`05ac:024f`, HID usage page `ff60`).

### Working in the first reported Fedora 44 test

- OpenRGB builds and detects `AULA F75 MAX (2.4G)`.
- RGB modes and static color configuration work.
- The first tester reports that turning keyboard backlight Off, and changing colors reliably, now work after the fixes.

### Fixes in this candidate

- Map global all-black LED selection to the actual hardware Off lighting mode.
- Avoid interleaved HID writes and repeat complete RGB command sequences with short delays for receiver reliability.
- Add packet and mocked-adapter tests, bilingual setup information and privacy review.

### Important limitations

This is **not** an official OpenRGB, EPOMAKER or AULA release. Tested by one user on Fedora 44; no assurance across all hardware revisions or operating systems. One global keyboard-lighting zone only, **no per-key RGB**, and no LCD/GIF/clock control. Does not power down the keyboard. No firmware flashing.

Installation: see [`README.md`](README.md) or [`README.de.md`](README.de.md). This repository is source code to be copied into OpenRGB and rebuilt, **not** a ready-to-install OpenRGB plugin or binary.
