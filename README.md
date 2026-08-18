# sted2

STed2 is a step-input MIDI sequencer in the Recomposer tradition, originally
written by Takayuki "TURBO" Toda for the Sharp X68000 (1991–1997) and ported
to Linux/UNIX by Daisuke Nagano (Studio Breeze) starting in 1998. The Linux
port last shipped in Debian as `2.07m+20010303-4` and has not built cleanly
on a modern system in many years.

This repository revives that port: builds on current Ubuntu / Debian, runs
on a 64-bit X11 desktop without a compositor, and ships a turnkey FluidSynth
hookup so you can hear what you sequence on a stock soft-synth install.

![STed2 running on a Clockwork DevTerm A06 — data list on the left, the
Ctrl+G score view on the right with MusiXTeX-derived note glyphs, and the
controller-graph pane below it](docs/screenshot.png)

## What's fixed since `2.07m+20010303-4`

| Area | Symptom on a modern system | Fix |
| --- | --- | --- |
| 64-bit malloc | `Cannot allocate track buffers.` at startup. | `_dos_malloc` no longer returns the Human68k `0x82000000` sentinel; callers in `sted.c` test for `NULL` instead of casting pointers to `int`. |
| GCC ≥ 14 build | Implicit declarations are errors; raw multi-line string literals are errors; `-fno-common` breaks header-level globals; C99 inline drops external symbols. | `CFLAGS` set documented below; raw multiline `sprintf` in `rcptomid.c` joined with C string continuation. |
| Debian build-deps | Package names from 2002 (`xlibs-dev`, `libxr-dev`, `libncurses5-dev`) no longer exist. | `debian/control` updated; `debian/compat` set to a working debhelper level. |
| X11 minimize / restore | Without a compositor, restoring an iconified window leaves it black. | Window contents are mirrored to a private pixmap and copied back on `Expose` / `MapNotify` / `VisibilityNotify`. |
| Ctrl+G score view | The X68000 original drew treble/bass clefs, note heads, flags, rests, and accidentals in the graphical score display using CGROM 外字 (gaiji) tiles. Those byte sequences didn't survive an EUC-JP → UTF-8 round trip somewhere in the source's history, so on Linux the `g_print(..., "??", ...)` calls rendered nothing and the score panel came up as an empty staff. | Redraw from 1bpp bitmaps extracted from MusixTeX-rendered glyphs — clefs, whole/half/quarter heads, 8th–64th upstem flags and rests, sharp, flat, augmentation dot. See `tools/extract_clefs.py` and `tools/extract_notation.py` for the extraction pipeline. |
| Flat-key note-letter input | On ARM (unsigned-char default), typing a letter flatted by the current key signature — `B` in F major, `B` / `E` in Bb major, etc. — was silently rejected because `key_shi[]`'s -1 sentinels decoded as 0xFF and made `ctc()` overflow past MIDI 127. Sharp keys were fine (`+1` sentinels are unaffected). | Declare `key_shi[]` and `sharp_yp[]` as `signed char` explicitly. |
| `make install` workflow | `po/` died on EUC-JP comments; cnf substitution was a no-op; binary and cnf were installed to incompatible paths; launchers had no install rule. | `po/` and `intl/` dropped from `SUBDIRS`; cnf substitution fixed; the real binary is installed alongside the cnf (`${prefix}/lib/sted/`) and a bash launcher at `${prefix}/bin/sted2` is what users actually invoke. |
| FluidSynth integration | STed2 wants a `/dev/midi`-style raw device and forks an external player; neither maps to a stock soft-synth. | Launcher wires `snd-virmidi` ↔ FluidSynth via `aconnect`; `sted2-play` forwards SMF tempfiles to FluidSynth via `aplaymidi`. |

## Quick start

Tested on Ubuntu 22.04 / 24.04 (x86_64 and aarch64).

```bash
sudo apt install build-essential autoconf automake \
    libx11-dev libxaw7-dev libxpm-dev libxt-dev libxmu-dev \
    libncurses-dev libasound2-dev pkg-config

cd sted2-2.07m+20010303
./configure --prefix=/usr/local
make CFLAGS="-g -O2 -fgnu89-inline -fcommon \
             -Wno-implicit-function-declaration -Wno-unused-result"
sudo make install

sudo usermod -aG audio "$USER"   # log out / log in once
```

Then just type `sted2`. To get sound out of the box, see
[FluidSynth + virmidi setup](#fluidsynth--virmidi-setup) below.

### What `make install` produces

```text
/usr/local/lib/sted/                 # data dir (root:audio, g+w)
    sted2                            # the real binary
    sted2.cnf                        # editable config (see "Customizing")
    sted2.fon
    deffile/{cm64,sc55,sc55mk2,sc88}.def
/usr/local/bin/
    sted2                            # bash launcher — what users invoke
    sted2-play                       # PLAY-time wrapper around aplaymidi
```

The real binary lives in the data directory because STed2 derives its
config-file path from `argv[0]` via `strmfe()`; keeping binary and cnf
adjacent is the simplest way to make that lookup succeed for any `--prefix`.

### CFLAGS notes

| Flag | Why |
| --- | --- |
| `-fgnu89-inline` | C99 inline semantics do not emit external symbols and break linking. |
| `-fcommon` | Header-level globals rely on the pre-GCC 10 default. |
| `-Wno-implicit-function-declaration` | Many call sites lack prototypes; GCC 14 makes this an error. |
| `-Wno-unused-result` | A handful of `fread()` calls discard the return value. |

## Customizing your install

All knobs live in **`/usr/local/lib/sted/sted2.cnf`**. Edit with any text
editor (the file is `root:audio` with group write, so members of the `audio`
group can change it directly; otherwise `sudo $EDITOR`).

The launcher's only automatic edit is `midi_port`, and only when the current
value still looks like a default (`/dev/midi` or `/dev/snd/midiC[0-9]+D0`).
Any other value is treated as user-customized and left alone. So you can
change `player`, `font_name`, `def_path`, key bindings, etc. freely.

### Smaller font (DevTerm-style 1280×480 screens)

Default window is 96×32 cells × 16 px = 768×512 px. On a 480 px-tall display
that doesn't fit. The cnf template already lists size alternatives; switch
the active one from `-16-` to `-14-` (giving 32×14 = 448 px):

```diff
-*#font_name=-\*-fixed-\*-r-normal--14-\*-\*-\*
-#font_name=-\*-fixed-\*-r-normal--16-\*-\*-\*
+#font_name=-\*-fixed-\*-r-normal--14-\*-\*-\*
+*#font_name=-\*-fixed-\*-r-normal--16-\*-\*-\*
```

(`*#` is the cnf's "commented out" marker, `#` is "active".)

### Hide the panel / titlebar on cramped screens

STed2 sets `min_size == max_size` on its X11 window, so window managers
treat it as non-resizable — F11, maximize buttons, and normal
Alt-space fullscreen shortcuts all no-op. On small displays (DevTerm
1280×480 in particular) the WM panel eats ~30 px off the top, so even
the 14-px font's 672×448 window ends up clipped at the bottom.

Push the window into WM fullscreen state via `wmctrl`: the STed2
window itself stays exactly its intrinsic size, but the panel and
title bar disappear so nothing overlaps it.

```bash
sudo apt install wmctrl
cat > ~/bin/sted2-fs <<'SCRIPT'
#!/bin/bash
# Launch STed2 and put its window into WM fullscreen state.
# Match by WM_CLASS ("sted") — WM_NAME is COMPOUND_TEXT and wmctrl
# reports it as "N/A", so title-based matching does not work.
sted2 &
STED_PID=$!
for i in $(seq 1 30); do
  if wmctrl -lx | awk '{print tolower($3)}' | grep -q '^\.sted'; then
    wmctrl -x -r sted -b add,fullscreen
    break
  fi
  sleep 0.2
done
wait $STED_PID
SCRIPT
chmod +x ~/bin/sted2-fs
```

Then invoke `sted2-fs` instead of `sted2`. To break out of fullscreen
without quitting STed2, from another terminal:

```bash
wmctrl -x -r sted -b remove,fullscreen
```

Tested on Xfce (xfwm4) 4.16; the recipe is WM-neutral in principle
(any EWMH-compliant WM should honor `_NET_WM_STATE_FULLSCREEN`).

### Use a USB-MIDI hardware synth instead of FluidSynth

1. Plug in the device. `aconnect -l` shows its ALSA seq client and port.
2. Edit cnf:

   ```text
   #midi_port=/dev/snd/midiC<your-card>D0
   #player=0,aplaymidi -p "<client>:<port>"
   ```

3. Don't install / load `snd-virmidi`. The launcher will see no virmidi
   client and leave your `midi_port` alone. FluidSynth, if present, just
   won't be used.

### Use an external player (TiMidity, etc.)

```text
#player=1,timidity -idq -f -EFchorus=0 -EFreverb=0 -s22.05
```

The launcher's `midi_port` rule still applies (only stomps on virmidi-style
defaults), so the two settings are independent.

## FluidSynth + virmidi setup

STed2 has two distinct MIDI paths:

| cnf key | Role | Default in this repo |
| --- | --- | --- |
| `#midi_port=` | Raw character device opened for **MIDI IN** (step input echo, external MIDI keyboard). | Auto-pointed at `snd-virmidi` by the launcher. |
| `#player=` | External command forked on **PLAY** to render the song. | `sted2-play`, which calls `aplaymidi -p <FluidSynth port>`. |

```bash
sudo apt install fluidsynth fluid-soundfont-gm

# Auto-load virmidi at boot
echo snd-virmidi | sudo tee /etc/modules-load.d/snd-virmidi.conf
sudo modprobe snd-virmidi

# Optional: pin the card index so the device path stays stable across reboots
echo 'options snd-virmidi index=2' | sudo tee /etc/modprobe.d/snd-virmidi.conf
```

The launcher does the rest at startup: discovers the current `Virtual Raw
MIDI` and `FLUID Synth` ALSA sequencer clients, updates `midi_port` in the
cnf to match, and `aconnect`s the two together. No manual port-number
bookkeeping required.

## Run

```bash
sted2                  # full-screen X11 editor
sted2 mysong.RCP       # open a file
sted2 -h               # show all options
```

A keyboard cheat sheet — including the X68000-to-PC-keyboard mapping you
will need to understand the in-app help — is in
[`docs/SHORTCUTS.md`](docs/SHORTCUTS.md). The original 1996 manuals (full
operation manual and online help) live in
[`sted2-2.07m+20010303/doc/original_docs/sted207/`](sted2-2.07m+20010303/doc/original_docs/sted207/)
in Shift-JIS. Those files, along with `doc/original_docs/tuitou.doc`
(a 1998 memorial to Takayuki "TURBO" Toda), are preserved verbatim as
required by the upstream license — please note that as vintage material
they contain era-appropriate personal contact information from
collaborators.

## Repository layout

```text
sted2/
├── README.md
├── LICENSE            # upstream license + fork terms
├── NOTICE             # third-party attributions (MusiXTeX)
├── docs/
│   └── SHORTCUTS.md   # UTF-8 keyboard cheat sheet (this fork)
├── sted2-2.07m+20010303/   # source tree (upstream + Debian + this fork)
│   ├── launchers/
│   │   ├── sted2      # ${prefix}/bin/sted2 — bash launcher
│   │   └── sted2-play # ${prefix}/bin/sted2-play — PLAY-time player
│   └── debian/        # dpkg-buildpackage-ready packaging (debhelper 13)
└── upstream/          # Debian snapshot archive for reference
```

The source tree is laid out as a Debian `2.07m+20010303-4` checkout. Commit
history walks pristine upstream → Debian packaging → fixes for modern Linux.

## License

See [`LICENSE`](LICENSE) at the repo root. In short: per the upstream
notice recorded in
[`sted2-2.07m+20010303/debian/copyright`](sted2-2.07m+20010303/debian/copyright):

> Right for modification and improvement is granted. However it is requested
> that when a modified version is publicly released, the accompanying DOC and
> HIS files are distributed along with it.

The original documentation (`doc/original_docs/`) is preserved in
this tree to satisfy that request. Changes in this fork are © 2026
contributors and offered under the same terms.

Third-party assets (the MusiXTeX-derived notation bitmaps) are covered
in [`NOTICE`](NOTICE).

Original authors:

- Takayuki "TURBO" Toda (1991–1997, X68000)
- Daisuke Nagano / Studio Breeze (1998–, Linux/UNIX port)
- Masayuki Hatta (initial Debian packaging, 2000)
- Junichi Uekawa (Debian packaging, 2001–)
