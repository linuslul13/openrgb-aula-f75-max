# Linux HID permissions

OpenRGB accesses the 2.4 GHz receiver (`05ac:024f`, `ff60`). Prefer seat-aware permissions via `uaccess`:

```bash
sudo tee /etc/udev/rules.d/60-aula-f75-max-openrgb.rules >/dev/null <<'EOF'
SUBSYSTEM=="hidraw", ATTRS{idVendor}=="05ac", ATTRS{idProduct}=="024f", TAG+="uaccess"
EOF
sudo udevadm control --reload-rules
sudo udevadm trigger
```

Replug the receiver. Avoid launching OpenRGB as root. `MODE="0666"` is not recommended for multi-user systems because it grants access to all local users. If your distribution's session manager doesn't implement `uaccess`, inspect access using `getfacl /dev/hidrawN` for the receiver's FF60 node and use a more restrictive rule.

Do not install this file automatically if you already have a working udev rule. The wired variant (`0c45:80b1`) is handled separately by display/clock tools.
