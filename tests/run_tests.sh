#!/usr/bin/env bash
set -euo pipefail
cd "$(dirname "$0")/.."
compiler="${CXX:-g++}"
out="$(mktemp -d)"
trap 'rm -rf "$out"' EXIT
"$compiler" -std=c++17 -Wall -Wextra -Werror -pedantic tests/test_packets.cpp -o "$out/test_packets"
"$out/test_packets"
"$compiler" -std=c++17 -Wall -Wextra -Werror -pedantic -Itests/stubs \
    -IControllers/AulaF75MaxController \
    tests/test_controller_mock.cpp \
    Controllers/AulaF75MaxController/AulaF75MaxController.cpp \
    Controllers/AulaF75MaxController/RGBController_AulaF75Max.cpp \
    -pthread -o "$out/test_controller"
"$out/test_controller"
