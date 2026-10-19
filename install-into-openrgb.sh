#!/usr/bin/env bash
set -euo pipefail
if [[ $# -ne 1 || ! -f "$1/OpenRGB.pro" ]]; then
    echo "Usage: ./install-into-openrgb.sh ~/OpenRGB" >&2
    exit 2
fi
root="$(cd "$1" && pwd)"
here="$(cd "$(dirname "$0")" && pwd)"
source="$here/Controllers/AulaF75MaxController"
target="$root/Controllers/AulaF75MaxController"
if [[ ! -d "$source" ]]; then
    echo "Missing controller folder: $source" >&2
    exit 2
fi
if [[ -e "$target" ]]; then
    backups="$root/.aula-controller-backups"
    mkdir -p "$backups"
    timestamp="$(date +%Y%m%d-%H%M%S)-$$"
    cp -a "$target" "$backups/$timestamp"
    echo "Previous driver backed up to: $backups/$timestamp"
    rm -rf -- "$target"
fi
cp -a "$source" "$target"
echo "Installed driver sources at: $target"
echo "Rebuild OpenRGB: cd '$root/build' && qmake-qt5 ../OpenRGB.pro && make -j4"
