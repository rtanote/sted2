# sted2

STed2 is a step-input MIDI sequencer in the Recomposer tradition, originally
written by Takayuki "TURBO" Toda for the Sharp X68000 (1991–1997) and ported
to Linux/UNIX by Daisuke Nagano (Studio Breeze) starting in 1998. The Linux
port last shipped in Debian as `2.07m+20010303-4` and has not built cleanly
on a modern system in many years.

This repository revives that port: builds on current Ubuntu / Debian, runs
on a 64-bit X11 desktop without a compositor, and ships a turnkey FluidSynth
hookup so you can hear what you sequence on a stock soft-synth install.

## What's fixed since `2.07m+20010303-4`

| Area | Symptom on a modern system | Fix |
| --- | --- | --- |
| 64-bit malloc | `Cannot allocate track buffers.` at startup. | `_dos_malloc` no longer returns the Human68k `0x82000000` sentinel; callers in `sted.c` test for `NULL` instead of casting pointers to `int`. |
| GCC ≥ 14 build | Implicit declarations are errors; raw multi-line string literals are errors; `-fno-common` breaks header-level globals; C99 inline drops external symbols. | `CFLAGS` set documented below; raw multiline `sprintf` in `rcptomid.c` joined with C string continuation. |
| Debian build-deps | Package names from 2002 (`xlibs-dev`, `libxr-dev`, `libncurses5-dev`) no longer exist. | `debian/control` updated; `debian/compat` set to a working debhelper level. |
| X11 minimize / restore | Without a compositor, restoring an iconified window leaves it black. | Window contents are mirrored to a private pixmap and copied back on `Expose` / `MapNotify` / `VisibilityNotify`. |
| FluidSynth integration | STed2 wants `/dev/midi`-style raw devices and forks an external player; neither maps to a stock soft-synth. | Launcher wires `snd-virmidi` ↔ FluidSynth via `aconnect`; `sted2-play` forwards SMF tempfiles to FluidSynth via `aplaymidi`. |

## Build

Tested on Ubuntu 22.04 / 24.04 (x86_64 and aarch64).

```bash
sudo apt install build-essential autoconf automake \
    libx11-dev libxaw7-dev libxpm-dev libxt-dev libxmu-dev \
    libncurses-dev libasound2-dev pkg-config

cd sted2-2.07m+20010303
./configure --prefix=/usr/local
make CFLAGS="-g -O2 -fgnu89-inline -fcommon \
             -Wno-implicit-function-declaration -Wno-unused-result"
```

`CFLAGS` notes:

| Flag | Why |
| --- | --- |
| `-fgnu89-inline` | C99 inline semantics do not emit external symbols and break linking. |
| `-fcommon` | Header-level globals rely on the pre-GCC 10 default. |
| `-Wno-implicit-function-declaration` | Many call sites lack prototypes; GCC 14 makes this an error. |
| `-Wno-unused-result` | A handful of `fread()` calls discard the return value. |

The `po/` (gettext) subdirectory will fail because of non-ASCII comments in
source. The main binary (`sted2/sted2/sted2`) is already done by then. Either
ignore the trailing error or pre-create empty catalogs:

```bash
touch po/sted2.pot po/sted2.po
```

## Install

The bundled autotools `make install` is broken (`po/` failure, and the
generated cnf hard-codes `/etc/sted2/deffile` which doesn't exist). Install
manually:

```bash
sudo install -d /usr/local/lib/sted/deffile
sudo install -m 0755 sted2/sted2 /usr/local/lib/sted/sted2
sudo install -m 0644 etc/sted2.fon /usr/local/lib/sted/sted2.fon
sudo install -m 0644 etc/deffile/*.def /usr/local/lib/sted/deffile/

sudo install -m 0664 etc/sted2.cnf.in /usr/local/lib/sted/sted2.cnf
sudo sed -i 's|^#def_path=/etc/sted2/deffile|#def_path=/usr/local/lib/sted/deffile|' \
    /usr/local/lib/sted/sted2.cnf

# Allow the launcher to update midi_port at startup (see below).
sudo chgrp audio /usr/local/lib/sted /usr/local/lib/sted/sted2.cnf
sudo chmod g+w  /usr/local/lib/sted /usr/local/lib/sted/sted2.cnf

sudo install -m 0755 launchers/sted2      /usr/local/bin/sted2
sudo install -m 0755 launchers/sted2-play /usr/local/bin/sted2-play

# Make sure your user is in the audio group (log out / in afterwards):
sudo usermod -aG audio "$USER"
```

## FluidSynth + virmidi

STed2 has two distinct MIDI paths and both must be wired up for full use:

| cnf key | Role | What this fork uses |
| --- | --- | --- |
| `#midi_port=` | Raw character device opened for **MIDI IN** (step-input echo, external MIDI keyboard). | A `snd-virmidi` raw device (`/dev/snd/midiC<n>D0`). |
| `#player=` | External command forked on **PLAY** to render the song. | `sted2-play`, which calls `aplaymidi -p <FluidSynth port>`. |

```bash
sudo apt install fluidsynth fluid-soundfont-gm

# Auto-load virmidi at boot
echo snd-virmidi | sudo tee /etc/modules-load.d/snd-virmidi.conf
sudo modprobe snd-virmidi

# Optional: pin the card index so the device path stays stable across reboots
echo 'options snd-virmidi index=2' | sudo tee /etc/modprobe.d/snd-virmidi.conf
```

At launch the wrapper discovers the current `Virtual Raw MIDI` and
`FLUID Synth` ALSA sequencer clients, updates `midi_port` in the cnf to match
the actual `/dev/snd/midiC*D0` device, and runs `aconnect virmidi → FluidSynth`.
No manual port-number bookkeeping is required.

## Run

```bash
sted2                  # full-screen X11 editor
sted2 mysong.RCP       # open a file
sted2 -h               # show all options
```

The binary itself is a small X11 client (Xaw / ncurses). `STED_LOCALE_DIR`
follows the configure prefix; data lookup is anchored to the binary's path
via `strmfe(argv[0], "cnf")`, which is why the launcher `cd`s into the data
directory before `exec`'ing the real binary.

## Notes for the ClockworkPi DevTerm A06

This fork was originally written for the DevTerm A06; everything above
applies, plus:

- The DevTerm's 1280×480 screen does not fit the default 768×512 STed2
  window vertically. The cnf template lists several font sizes already; set
  the active one to `-14-`:

  ```
  #font_name=-*-fixed-*-r-normal--14-*-*-*
  ```

  giving a 32×14 = 448 px window.

- xfwm4 on the DevTerm runs without an active compositor, which is exactly
  the case the minimize/restore fix targets. No further configuration needed.

- A06 CPU governor can be controlled with the
  [`devterm-gearbox-a06`](https://github.com/clockworkpi) package
  (binary: `a06-gearbox`). `sudo a06-gearbox -s 4` is a reasonable default
  for running STed2 + FluidSynth.

## Repository layout

```
sted2/
├── README.md
├── launchers/
│   ├── sted2          # /usr/local/bin/sted2 — bash launcher
│   └── sted2-play     # /usr/local/bin/sted2-play — PLAY-time player
├── sted2-2.07m+20010303/   # source tree (upstream + Debian + this fork)
└── upstream/          # Debian snapshot archive for reference
```

The source tree is laid out as a Debian `2.07m+20010303-4` checkout. Commit
history walks pristine upstream → Debian packaging → fixes for modern Linux.

## License

Per the upstream notice in [`debian/copyright`](sted2-2.07m+20010303/debian/copyright):

> Right for modification and improvement is granted. However it is requested
> that when a modified version is publicly released, the accompanying DOC and
> HIS files are distributed along with it.

The original documentation (`doc/original_docs/sted207/`) is preserved in
this tree to satisfy that request. Changes in this fork are © 2026
contributors and offered under the same terms.

Original authors:

- Takayuki "TURBO" Toda (1991–1997, X68000)
- Daisuke Nagano / Studio Breeze (1998–, Linux/UNIX port)
- Junichi Uekawa (Debian packaging, 2001–)
