# Changelog

## 0.2.0-rc2 (2026-10-19)

- **User-confirmed on real hardware (Fedora 44):** all requested OpenRGB lighting functions now work on the original test keyboard.
- Hardware Off and OpenRGB's all-black LED selection now switch off the keyboard backlighting.
- Previously occasionally ignored color updates no longer occur in the tester's follow-up test.
- Updated English/German instructions and hardware test status without publishing private device details.
- Scope remains one confirmed 2.4 GHz receiver setup; other firmware revisions and full extended regression tests are not verified.

## 0.2.0-rc1 (2026-10-19)

- Adjust OpenRGB global-color path: all LEDs black requests hardware Off, nonblack picks Static.
- Repeat complete 2-packet RGB update with delays to mitigate intermittently ignored changes.
- Serialize writes to the receiver to avoid interleaved command streams.
- Add automated mock-transport tests, English/German documentation and release checklist.
- At the initial rc1 draft, hardware validation for the fixes was still pending. The tester later confirmed them in rc2 (see above).

## 0.1.0 (prototype)

- Detect `05ac:024f` interface `ff60` and show one RGB zone in OpenRGB.
- Off / Static / Breathing / Spectrum / Rolling Rainbow / Ripples modes.
- A Fedora 44 user confirmed OpenRGB build, device detection and basic color changes.
- Known user-reported issues: Off did not always turn backlighting off; some color changes needed a second attempt.