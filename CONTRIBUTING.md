# Contributing

Small reproducible improvements and hardware test reports welcome. Please document the exact receiver USB ID, keyboard model/revision, tested OpenRGB commit, and a non-destructive test procedure. Do not include private host information in debug logs. Please do not submit firmware writers or factory-reset automation here.

Prefer narrowly scoped patches; preserve `GPL-2.0-or-later` headers. Run `./tests/run_tests.sh` and complete `docs/TESTING.md` where hardware is available. A passing mock test does not prove the device actually applied the command.

The driver was developed with AI assistance and should be read and manually reviewed by human contributors. OpenRGB upstream's own AI contributions policy generally rejects directly generated submissions; upstreaming would require following their policy and fully understanding and reviewing the implementation. This repository does not represent an upstream-approved submission.