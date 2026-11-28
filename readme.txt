ZERO SPRITE EDITOR - SETUP
==========================

Redraw Zero's animations from Mega Man Zero 3 in your browser and build a
playable USA or Japanese ROM with them. These steps are for Ubuntu, or WSL
on Windows (run everything inside WSL; the editor opens in your Windows
browser).


1. Install the tools

    sudo apt update
    sudo apt install build-essential git pkg-config libpng-dev gcc-arm-none-eabi binutils-arm-none-eabi python3 curl unzip


2. Install Deno (the build uses it to convert sprite files)

    curl -fsSL https://deno.land/install.sh | sh

   Open a new terminal afterwards and check that "deno --version" works.


3. Get the code and the compiler

    git clone -b sprite-editor https://github.com/brodieberger/rmz3
    git clone https://github.com/pret/agbcc
    cd agbcc
    ./build.sh
    ./install.sh ../rmz3
    cd ../rmz3


4. First build (proves the setup works)

    DEVKITARM=/usr make REGION=us

   The first build takes several minutes and needs internet once, for a
   small Deno package. It should end with:

    rmz3-us.gba: OK

   If you installed devkitPro instead of the apt packages, DEVKITARM is
   already set: leave out "DEVKITARM=/usr".


5. Start the editor

    tools/sprite_editor/start.sh

   It opens http://localhost:8766 in your browser. Ctrl+C in the terminal
   stops it. Run it again whenever you want to come back.


USING IT

   - Pick an animation, paint, then click Save.
   - Pick USA or Japan and click Build ROM. "Last build" on the right shows
     where the ROM is. Open it in an emulator.
   - The Help button in the editor explains the tools and the limits.

   To undo every saved change:

    git checkout sprites/

   Building by hand works too: "make REGION=us" or "make REGION=jp". Once
   sprites change, make ends with "rmz3-us.gba: FAILED" and "Error 1". That
   only means the ROM no longer matches the original game. The build worked.

   tools/sprite_editor/README.md has more on the editor.
