# OpenRGB: EPOMAKER × AULA F75 MAX (Linux)

**Experimenteller OpenRGB-Treiber für die RGB-Beleuchtung über den 2,4-GHz-Empfänger.**

**Status:** Der ursprüngliche Prototyp wurde unter Fedora 44 erfolgreich kompiliert und konnte die Tastaturfarben steuern. Diese Version enthält zusätzliche Korrekturen für "Off" und gelegentlich ignorierte Farbwechsel. **Diese Korrekturen müssen noch an der echten Tastatur geprüft werden.**

## Unterstützte Funktionen

- RGB-Zone für die gesamte Tastatur (keine Einzeltastensteuerung).
- Off, Static, Breathing, Spectrum, Rolling Rainbow und Ripples.
- Je nach Modus Farbe, Helligkeit und Geschwindigkeit.
- **Nur über den 2,4-GHz-Empfänger** `05ac:024f` mit HID-Seite `ff60`, nicht über Bluetooth.

Das Abschalten der LEDs ist **nicht** das Abschalten der Tastatur. Display, Statusleuchten und normale Tastatureingaben bleiben gegebenenfalls aktiv.

## Installation / Update unter Fedora

```bash
# Falls OpenRGB bereits unter ~/OpenRGB vorhanden ist: kein neues Repository klonen!
cd ~/Downloads/openrgb-aula-f75-max
./install-into-openrgb.sh ~/OpenRGB

cd ~/OpenRGB/build
qmake-qt5 ../OpenRGB.pro
make -j4
./openrgb
```

Bei einer vorhandenen Treiberversion erstellt das Skript zunächst eine Sicherheitskopie in `~/OpenRGB/.aula-controller-backups/`. **OpenRGB muss nach jeder Treiberänderung neu kompiliert werden.** Andere OpenRGB-Instanzen vorher schließen.

Fehlende Fedora-Pakete: `sudo dnf install -y automake gcc-c++ git make hidapi-devel libusbx-devel mbedtls-devel pkgconf qt5-qtbase-devel qt5-linguist`. Für Linux-HID-Zugriff siehe [docs/UDEV.md](docs/UDEV.md).

## Test: zwei gemeldete Fehler

1. In OpenRGB **Modus Off** auswählen. Es sollen alle RGB-Tastenlichter ausgehen.
2. **Alle LEDs auf Schwarz** setzen. Das sollte jetzt den Hardware-Off-Modus anwenden.
3. Mehrmals hintereinander zwischen Rot, Blau und Grün wechseln. Änderungen sollten zuverlässiger übernommen werden.

Wenn Off nicht funktioniert, separat testen:

```bash
cd ~/Aula-F75-Max-Web/aula-f75
python3 aula.py rgb --mode off
```

Falls auch die CLI nicht abschaltet, ist das Problem wahrscheinlich nicht nur die OpenRGB-Zuordnung, sondern braucht weitere Hardware-/Protokollanalyse. **Keine Firmware-Experimente oder Factory-Resets erforderlich.**

[Komplette Testcheckliste](docs/TESTING.md) · [English README](README.md) · [Lizenz](LICENSE)