#!/bin/bash

# color convert functions - https://stackoverflow.com/questions/27159322/rgb-values-of-the-colors-in-the-ansi-extended-colors-index-17-255

rgbtohex() {
  # usage) `rgbtohex 17 0 26` ==> 1001A
  # usage) `rgbtohex -h 17 0 26` ==> #1001A
  addleadingzero () { awk '{if(length($0)<2){printf "0";} print $0;}';}
  if [[ ${1} == "-h" ]]; then
    r=${2}; g=${3}; b=${4};h='#';
  else
    r=${1}; g=${2}; b=${3};h='';
  fi
  r=`echo "obase=16; ${r}" | bc | addleadingzero`
  g=`echo "obase=16; ${g}" | bc | addleadingzero`
  b=`echo "obase=16; ${b}" | bc | addleadingzero`
  echo "${h}${r}${g}${b}"
}

rgbto256() {
  # usage: `rgbto256 0 95, 135` ==> 22
  echo "define trunc(x){auto os;os=scale;scale=0;x/=1;scale=os;return x;};" \
    "16 + 36 * trunc(${1}/51) + 6 * trunc(${2}/51) +" \
    " trunc(${3}/51)" | bc
  # XTerm Color Number = 16 + 36 * R + 6 * G + B | 0 <= R,G,B <= 5
}

hextorgb() {
  # usage) `hexttorgb "11001A" ==> 17 0 26
  # usage) `hexttorgb "#11001A" ==> 17 0 26
  hexinput=`echo ${1} | tr '[:lower:]' '[:upper:]'` # uppercase-ing
  hexinput=`echo ${hexinput} | tr -d '#'`# remove Hash if needed
  a=`echo ${hexinput} | cut -c-2`
  b=`echo ${hexinput} | cut -c3-4`
  c=`echo ${hexinput} | cut -c5-6`
  r=`echo "ibase=16; ${a}" | bc`
  g=`echo "ibase=16; ${b}" | bc`
  b=`echo "ibase=16; ${c}" | bc`
  echo ${r} ${g} ${b}
}

trueHexPrint() {
  # Generates Truecolor Escape Sequences from Hex Strings.
  # -fg     Prints as a foreground color. (default)
  # -bg     Prints as a background color.
  # usage) `trueHexPrint -fg "11001A" ==> '\e[38;2;17;0;26m'
  # usage) `trueHexPrint -bg "11001A" ==> '\e[48;2;17;0;26m'
  if [[ ${1} =~ "-fg" || ${1} =~ "-f" ]]; then
    fgbg=38; hexinput=${2};
  elif [[ ${1} =~ "-bg" || ${1} =~ "-b" ]]; then
    fgbg=48; hexinput=${2};
  else
    fgbg=38; hexinput=${1}
  fi
  hexinput=`echo ${hexinput} | tr '[:lower:]' '[:upper:]'` # uppercase-ing
  hexinput=`echo ${hexinput} | tr -d '#'` # remove Hash if needed
  a=`echo ${hexinput} | cut -c-2`
  b=`echo ${hexinput} | cut -c3-4`
  c=`echo ${hexinput} | cut -c5-6`
  r=`echo "ibase=16; ${a}" | bc`
  g=`echo "ibase=16; ${b}" | bc`
  b=`echo "ibase=16; ${c}" | bc`
  printf "\e[${fgbg};2;${r};${g};${b}m"
}

XColorTable() {
  i=16
  for ((r = 0; r <= 255; r+=40)); do # Do Tricolor
    for ((g = 0; g <= 255; g+=40)); do
      for ((b = 0; b <= 255; b+=40)); do
    echo "Color$((i++)) = (${r}, ${g}, ${b})"
        if ((b == 0)); then b=55; fi
      done
      if ((b == 0)); then g=55; fi
    done
    if ((r == 0)); then r=55; fi
  done
  for ((m = 8; m <= 238; m+=10)); do # Do Monochrome
    echo "Color$((i++)) = (${m}, ${m}, ${m})"
  done
}

# hex colors

cr1black=#000000
cr1pink=#FF00FF
cr1red=#FF0000
cr1orange=#FFCC00
cr1yellow=#FFFF00
cr1lightgreen=#00FF00
cr1darkgreen=#006600
cr1cyan=#00FFFF
cr1blue=#0000FF
cr1purple=#6600CC
cr1gray1=#333333
cr1gray2=#666666
cr1gray3=#999999
cr1gray4=#CCCCCC
cr1white=#FFFFFF

# stupid shell can't do shit pls use C for direct proc/cpu/mem/disk control

fg1black=$(trueHexPrint -fg $cr1black)
fg1pink=$(trueHexPrint -fg $cr1pink)
fg1red=$(trueHexPrint -fg $cr1red)
fg1orange=$(trueHexPrint -fg $cr1orange)
fg1yellow=$(trueHexPrint -fg $cr1yellow)
fg1lightgreen=$(trueHexPrint -fg $cr1lightgreen)
fg1darkgreen=$(trueHexPrint -fg $cr1darkgreen)
fg1cyan=$(trueHexPrint -fg $cr1cyan)
fg1blue=$(trueHexPrint -fg $cr1blue)
fg1purple=$(trueHexPrint -fg $cr1purple)
fg1gray1=$(trueHexPrint -fg $cr1gray1)
fg1gray2=$(trueHexPrint -fg $cr1gray2)
fg1gray3=$(trueHexPrint -fg $cr1gray3)
fg1gray4=$(trueHexPrint -fg $cr1gray4)
fg1white=$(trueHexPrint -fg $cr1white)

bg1black=$(trueHexPrint -bg $cr1black)
bg1pink=$(trueHexPrint -bg $cr1pink)
bg1red=$(trueHexPrint -bg $cr1red)
bg1orange=$(trueHexPrint -bg $cr1orange)
bg1yellow=$(trueHexPrint -bg $cr1yellow)
bg1lightgreen=$(trueHexPrint -bg $cr1lightgreen)
bg1darkgreen=$(trueHexPrint -bg $cr1darkgreen)
bg1cyan=$(trueHexPrint -bg $cr1cyan)
bg1blue=$(trueHexPrint -bg $cr1blue)
bg1purple=$(trueHexPrint -bg $cr1purple)
bg1gray1=$(trueHexPrint -bg $cr1gray1)
bg1gray2=$(trueHexPrint -bg $cr1gray2)
bg1gray3=$(trueHexPrint -bg $cr1gray3)
bg1gray4=$(trueHexPrint -bg $cr1gray4)
bg1white=$(trueHexPrint -bg $cr1white)

# cr_sq=($(set | awk '/^cr1/' | awk -F= '{print $1}'))
# cr_sl=${#cr_sq[*]}
# for ii in ${cr_sq[*]} # nothing can extract vars with index in for loop
# do
#   export fg_${ii}=$(trueHexPrint -fg ${ii}) # don't use export it affects sys env
#   export bg_${ii}=$(trueHexPrint -bg ${ii})
#   tmpf=$(trueHexPrint -fg ${ii})
#   tmpb=$(trueHexPrint -bg ${ii})
#   echo $tmpf
# done
fb1reset='\e[0m'

# word=fuk
# echo "${bg1white}"
# printf "${fb1reset}MEMO: ${bg1white}${word}${fb1reset}${word}"
