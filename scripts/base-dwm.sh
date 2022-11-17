#!/bin/bash

export LC_ALL="en_US.UTF-8"

feh --bg-fill ~/F0_user_files/F/Rec/Image/screen_photos/11.jpg

# xrdb merge ~/.Xresources
xset -dpms
xset s off
xset r rate 300 45 &

setxkbmap -option caps:swapescape

# First run picom --diagnostics, if glx backend fails because of fuking nvidia card then change a backend
picom --backend xrender &

source ~/.base-dwm-bar &
# while type dwm >/dev/null; do dwm && continue || break; done
exec dwm
