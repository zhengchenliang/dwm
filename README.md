Forked from David Chen

Install using make:
  make
  make clean
  make clean install
  make clean uninstall
Destination (PREFIX) should be in /usr/local (see config.mk -> Makefile)

Run with script:
  startx ~/.base-dwm

Settings:
  config.h:
    6: #pixel of windows' borders
    12-15: #pixel of gaps between windows and screen
    18: display bar on top/bottom
    20: dwm fonts
    21: dmenu fonts -> 92: implement
    22-36: colors for dwm & dmenu -> 92: implement
    52: chars for tags
    54-65: default window type settings for programs
    72-77: chars for layout modes
    80-85: define MODKEY & TAGKEYS (Win or Alt)
    88: can use SHCMD below
    92-110: can add your scripts linking to keybinds
    113-173 specification of keybinds -> sh .v commands & func in dwm.c: implementation
    176-190 specification of mouse -> sh .v commands & func in dwm.c: implementation
  dwm.c:
    X11 application. Press '/' to search for functions & implementations
    Go to https://www.x.org/releases/X11R7.7/doc/ for the manual
    > func -> config.h keybinds/mouse control
  scripts/base-dwm.sh
    3: locale export
    5: screen
    7: xrdb -> X settings load
    8-10: xset -> screen power saver, screen off time, repeated key time & rate
    12: bar of system status via shell -> scripts/base-dwm-bar.sh: implementation
    13: launch dwm
  scripts/base-dwm-bar.sh
    3: load colors -> base-dwm-color.sh: implementation
    5-42: shell func for get system info with awk
    54: xsetroot -> display that bar
  scripts/base-dwm-color.sh
    5-81: shell func for converting colors (work for bash)
    85-99: set same colors as in config.h

Git commands:
  git add *
  git commit -m "ababababa"
  git push

Comments:
  .myXresources -> ~/.Xresources not applied
  bar colors not configured; can go to suckless.org to patch and configure
  only default patches were applied; for new patches
  > download abababa.diff
  > patch -p1 abababa.diff
  > manual patch if this auto patch fails
