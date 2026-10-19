# Release checklist

- [ ] Independent maintainer reviews all code and license statements.
- [ ] Run `./tests/run_tests.sh` on Linux.
- [x] Original tester reports a successful Fedora 44 OpenRGB build (exact commit not supplied).
- [ ] Full extended regression checklist across multiple devices; initial owner reports RGB controls and reported fixes working.
- [x] Original Fedora 44 hardware tester confirms all requested lighting functions work, including Off, all-black and formerly ignored color changes. More independent test reports welcome.
- [x] Update changelog with the user-reported Fedora 44 result and relevant non-unique USB IDs.
- [ ] Take original screenshot of OpenRGB showing device (do not include serial numbers).
- [x] Label as prerelease (`v0.2.0-rc2`): one successfully tested hardware setup, not broadly verified.
- [x] Verify release package contains source/docs/tests only and passes `tools/privacy_check.py`. Recheck before public upload.
- [x] Published as the dedicated public repository `linuslul13/openrgb-aula-f75-max`.
- [ ] Keep upstream GitLab AI contributions policy in mind before any merge request.
