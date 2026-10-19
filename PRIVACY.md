# Privacy and public-repository policy

This project ships **source code, generic hardware compatibility IDs, documentation and offline tests only**. It does not include any uploaded system logs, terminal output, screenshots, user profiles, computer names, personal domains, email addresses, device MAC addresses, hardware serial numbers, or unique identifiers.

## Identifiers explained

- `05ac:024f` is the USB vendor/product ID of the supported 2.4 GHz receiver.
- `0c45:80b1` / `0c45:800a` are USB vendor/product IDs of wired F75 MAX variants; they are included only for compatibility documentation.
- HID usage pages `ff60`, `ff13` and `ff68` are protocol selectors.
- These values are **not** a MAC address and do not identify a specific device owner.

The runtime path displayed locally by OpenRGB is not transmitted anywhere by this project. GitHub Actions test compilation and packet serialization only, with no actual device attached.

## Before sharing an issue, screenshot or log

Remove MAC addresses (`xx:xx:xx:xx:xx:xx`), hardware serial numbers, IP addresses, user directories (`/home/USERNAME`, `C:\Users\USERNAME`), hostnames, user handles, email addresses, access tokens, and geolocation. Report only the **non-unique USB model ID**, driver version, Fedora/OpenRGB version, and reproduction steps.

Run `python3 tools/privacy_check.py` to check tracked project files for likely accidental data disclosures. The scanner is conservative and is **not** a guarantee that all private strings can be detected. Read every file before uploading it publicly.

## GitHub account visibility

Publishing to a public repository under your own GitHub account necessarily exposes your account username and normally the commit author attribution. To avoid linking the project to your personal account, publish using an appropriate separate pseudonymous account instead. Do not attempt to strip Git history after a secret has been pushed; revoke the secret and consult GitHub's sensitive-data removal guidance.
