# v0.2.0-rc2 — Community prerelease

An experimental OpenRGB RGB controller for the **EPOMAKER × AULA F75 MAX**, operating through the **2.4 GHz receiver** (`05ac:024f`, HID usage page `ff60`).

### Confirmed by the original Fedora 44 hardware tester (October 19, 2026)

- OpenRGB builds and detects `AULA F75 MAX (2.4G)`.
- RGB modes and static color configuration work.
- All lighting functions requested by the original tester now work on their device, including **Off** and setting **all LEDs to black** to turn off the keyboard backlighting.
- The original tester reports that changing colors now works without the previously observed need to repeat the action.

### Fixes in this candidate

- Map global all-black LED selection to the actual hardware Off lighting mode.
- Avoid interleaved HID writes and repeat complete RGB command sequences with short delays for receiver reliability.
- Add packet and mocked-adapter tests, bilingual setup information and privacy review.

### Important limitations

This is **not** an official OpenRGB, EPOMAKER or AULA release. Hardware-verified by one Fedora 44 user on one keyboard/receiver setup; no assurance across all hardware revisions, effect presets, or operating systems. One global keyboard-lighting zone only, **no per-key RGB**, and no LCD/GIF/clock control. Does not power down the keyboard. No firmware flashing.

Installation: see [`README.md`](README.md) or [`README.de.md`](README.de.md). This repository is source code to be copied into OpenRGB and rebuilt, **not** a ready-to-install OpenRGB plugin or binary.
