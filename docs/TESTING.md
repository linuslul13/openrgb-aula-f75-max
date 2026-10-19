# Hardware test checklist

Run against an **actual** F75 MAX, 2.4G mode, receiver `05ac:024f` (FF60). Close other RGB control programs. Log observations and exact OpenRGB commit hash. No firmware flashing or reset needed.

- [ ] OpenRGB built cleanly after installing these files, no duplicate controller detected.
- [ ] OpenRGB device `AULA F75 MAX (2.4G)` appears on 2.4G, not confused with generic Apple keyboard interfaces.
- [ ] Mode `Static`: pure red `FF0000`, green `00FF00`, blue `0000FF`, white `FFFFFF` display correctly.
- [ ] Mode `Off` turns off keyboard *backlighting* (keyboard remains usable; status lights/TFT are separate).
- [ ] "Set all LEDs to black" turns off backlighting and does not leave previous preset running.
- [ ] From `Off` change to `Static` and back at least five times.
- [ ] Quickly change colors 20 times; record ignored changes, if any.
- [ ] Breathing, Spectrum, Rolling Rainbow and Ripples give plausible results.
- [ ] Brightness 1 to 5 works in a supported mode.
- [ ] Speed 1 to 5 works where shown.
- [ ] Disconnect/reconnect dongle, change mode, restore connection; no crash or hang.
- [ ] Keyboard sleep/wake and computer reboot do not hang OpenRGB.
- [ ] `python3 aula.py rgb --mode off` separately tested if OpenRGB Off fails (avoid simultaneous access).
- [ ] No unexpected firmware operations or display/RTC changes.

## Diagnosis

The device protocol has no verified RGB ACK. Duplicate writes are a *mitigation*, not a confirmed solution. If OpenRGB Off remains faulty but `aula.py rgb --mode off` works, send: exact steps, selected OpenRGB mode, keyboard connection selector position, and version; no private logs necessary.

If **both** OpenRGB and `aula.py` Off fail, keep it listed as a known issue and do not advertise "Off" as supported on that hardware variant until validated.

## Report back

- Fedora version / desktop
- OpenRGB commit (run `git -C ~/OpenRGB rev-parse --short HEAD`)
- Receiver USB ID and usage page
- Static colors OK? / Off mode OK? / black LEDs OK? / 20 changes missed count?
- Whether USB-C cable was also connected

## Confirmed initial field report (2026-10-19)

A Fedora 44 user confirms compilation, OpenRGB detection, RGB control, and that the follow-up Off/color-change corrections work. No personal device details are stored. The full matrix above has not been independently recorded; keep remaining test cases open.
