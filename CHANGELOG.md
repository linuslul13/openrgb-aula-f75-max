# Changelog

## 0.2.0-rc1 (2026-10-19)

- Adjust OpenRGB global-color path: all LEDs black requests hardware Off, nonblack picks Static.
- Repeat complete 2-packet RGB update with delays to mitigate intermittently ignored changes.
- Serialize writes to the receiver to avoid interleaved command streams.
- Add automated mock-transport tests, English/German documentation and release checklist.
- **Hardware validation pending for the fixes. Do not mark this release as stable.**

## 0.1.0 (prototype)

- Detect `05ac:024f` interface `ff60` and show one RGB zone in OpenRGB.
- Off / Static / Breathing / Spectrum / Rolling Rainbow / Ripples modes.
- A Fedora 44 user confirmed OpenRGB build, device detection and basic color changes.
- Known user-reported issues: Off did not always turn backlighting off; some color changes needed a second attempt.