# Security

This community driver writes user-selected RGB commands to a local USB HID device. It does not use the network, request administrator access at runtime, update firmware, or read device serial numbers. HID commands still interact with hardware: use at your own risk.

Never post a private log or full `lsusb -v`, `dmesg` or OpenRGB debug dump without reviewing it for identifying data. Report potential security problems to the maintainer privately via GitHub where possible, or omit sensitive details from a public issue.

Only the receiver's FF60 interface is targeted. Other models sharing the same VID/PID and usage page are not guaranteed compatible.
