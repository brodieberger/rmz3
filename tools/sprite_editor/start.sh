#!/bin/sh
# Starts the sprite editor and opens it in the browser. Ctrl+C stops it.
cd "$(dirname "$0")" && exec python3 sprite_editor.py "$@"
