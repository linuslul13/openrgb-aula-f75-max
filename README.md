# OpenRGB driver for AULA F75 MAX

**Community-maintained, experimental OpenRGB controller extension for the EPOMAKER × AULA F75 MAX.**

> **Status:** A Fedora 44 user reported that the initial prototype builds, detects the keyboard and changes its RGB colors. This branch contains additional **untested-on-hardware** reliability and Off-mode fixes. There is no standalone OpenRGB plugin binary and this is not yet merged upstream.

[Deutsche Anleitung](README.de.md) · [Test plan](docs/TESTING.md) · [Attribution](NOTICE.md)

## Hardware and scope

| Component | USB ID | Interface | Purpose |
| --- | --- | --- | --- |
| 2.4 GHz dongle | `05ac:024f` | HID usage page `ff60` | **OpenRGB RGB commands** |
| F75 MAX wired keyboard, tested variant | `0c45:80b1` | `ff13`/`ff68` | Clock/display through other tools, **not this extension** |
| F75 MAX wired keyboard, other known variant | `0c45:800a` | `ff13`/`ff68` | Not used by this extension |

The dongle reports as an Apple keyboard on some systems. Detection is restricted to usage page `ff60`, so generic input interfaces are not controlled. This does **not** mean other devices sharing that interface can never collide; verify your USB ID before use.

### Implemented lighting features

- One **global backlight zone**, not per-key RGB.
- Modes: Off, Static, Breathing, Spectrum, Rolling Rainbow, Ripples.
- Color, brightness (1–5), and speed (1–5) where applicable.
- Does **not** turn the keyboard itself off; only controls backlighting. Indicator LEDs and the TFT may remain on.
- Does **not** upload GIFs, sync time, remap keys, update firmware or change keyboard power state.

### Known limitations

- The hardware does not send a documented acknowledgment for these RGB commands. A successful `hid_write()` only means an OUTPUT report was accepted by the OS. To reduce occasional ignored changes, the extension sends each lighting sequence twice with a short delay. **This is a test candidate, not a verified fix.**
- OpenRGB's "set all LEDs to black" color path now selects the hardware Off mode instead of re-applying the previous preset. Both this fix and direct Off mode require another hardware test.
- Only the 2.4 GHz dongle pathway is implemented. Put the keyboard in **2.4G mode** while testing. Do not run another RGB controller application that opens the same receiver simultaneously.
- Lighting will not necessarily reflect OpenRGB's last selected color after unplug/replug or keyboard sleep. A future read-back implementation would require protocol research.
- May not work with every F75 MAX revision. The `80b1` cable ID alone is not proof of RGB firmware compatibility.

## Install on Fedora

```bash
sudo dnf install -y automake gcc-c++ git make hidapi-devel libusbx-devel \
  mbedtls-devel pkgconf qt5-qtbase-devel qt5-linguist

# Clone OpenRGB if you haven't already (the upstream primary repo is on GitLab).
git clone https://gitlab.com/CalcProgrammer1/OpenRGB.git ~/OpenRGB

# From this repository:
./install-into-openrgb.sh ~/OpenRGB

cd ~/OpenRGB/build  # run mkdir -p ~/OpenRGB/build first if missing
qmake-qt5 ../OpenRGB.pro
make -j4
./openrgb
```

Fedora may package `qmake` as `qmake-qt5`. Do not use `sudo` to launch OpenRGB. Ensure HID permissions are configured; see [Udev rules](docs/UDEV.md).

**Updating from an earlier prototype:** Rerun `./install-into-openrgb.sh ~/OpenRGB`. It backs up the existing controller outside the OpenRGB `Controllers` directory, replaces files, then you **must rebuild** OpenRGB.

## Tests

```bash
./tests/run_tests.sh
```

This verifies packet layouts and exercises the adapter against a mocked HID API. It does **not** prove behavior on real hardware. See [hardware acceptance checklist](docs/TESTING.md) before calling a release stable.

## Uninstall

Remove `~/OpenRGB/Controllers/AulaF75MaxController` and rebuild OpenRGB. Previous copies saved by the installer live in `~/OpenRGB/.aula-controller-backups/`.

## License and upstream

GPL-2.0-or-later, compatible with OpenRGB. See [LICENSE](LICENSE) and [NOTICE.md](NOTICE.md). Independent community code, not endorsed by AULA, EPOMAKER or OpenRGB.

**Upstream is hosted on GitLab:** <https://gitlab.com/CalcProgrammer1/OpenRGB>. Their contribution guidelines require human-reviewed, independently understood code and generally disallow directly AI-generated contributions. This work was developed with AI assistance, so **do not submit it as an upstream merge request without substantial human review and rewriting**. This repository is an experimental community prototype, not an official upstream contribution.