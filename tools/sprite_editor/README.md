# Zero Sprite Editor

Paint Zero's animations from the rmz3 decomp a frame at a time, in the browser, and save them
straight back into the decomp. Each frame is one whole picture. On save, the page cuts it into
8x8 tiles and the game's hardware-sprite boxes, and rewrites the files the build reads.

Needs only Python 3. Nothing to install.

```
tools/sprite_editor/start.sh
```

starts it and opens <http://localhost:8766> in your browser, from any folder. Ctrl+C stops it.
If it is already running, it just opens the page. On Windows, run it in WSL: the page opens in
the Windows browser. `--sprites` points it at another checkout's `sprites/`. The page's Help
button has these steps too.

- **Paint** with the pencil, eraser, fill and picker, in Zero's 16 colours. Colour 0 is
  see-through. Right-click paints 0.
- **Shift + arrows** moves the whole frame a pixel. **Left/right** changes frame.
- **Tile space** shows each sheet against its 48-tile limit as you paint. Past 48, Save is off
  and the sheet says which frames to trim. Moving one frame of a sheet costs tiles, because its
  art stops lining up with the frames it shares the sheet with.
- **Save** writes only the animation you changed: its sheet PNGs, `metasprite.json`,
  `sheet/header.inc`, and the sheets' `-num_tiles` in `sprites.mk`. Sheets whose frames you
  did not touch stay as they are.
- **Export/Import PNG** swaps one frame with Aseprite or another editor. Keep its size and
  palette.
- **Build ROM** runs `make` for the region beside it and shows where the ROM landed, with the
  end of make's output. It builds what is saved, so it waits until you save. `DEVKITARM` comes
  from the shell that started the editor, or `/usr` if unset.

`make REGION=us` or `make REGION=jp` by hand does the same. A `FAILED` checksum line is expected
once sprites change. `git checkout sprites/` undoes everything.

Zero faces left in the editor, as the game stores him. Eight animations (teleport, Gale
Attack, the smash, two rod charges, buster-air, `unk_51`) were packed by Capcom with
overlapping pieces, which this does not do, so redrawing them at full size runs past 48 tiles.
The door is not plain tiles, so it is not listed.
