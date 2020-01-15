#!/usr/bin/env bash

extra=""

if [ "$1" = "debug" ]
then
  extra="-debug"
fi

if [ "$1" = "avi" ]
then
  extra="-aviwrite out.avi -snapsize 320x216"
fi

mame genesis -window \
  -cart sega_genesis_java_demo.bin \
  ${extra}

if [ "$1" = "avi" ]
then
  #mencoder -oac mp3lame -ovc x264 -o video.avi -vf scale=640:480 ~/.mame/snap/out.avi
  ffmpeg -i snap/out.avi -vf hflip -s 640x480 out.mp4
  ffmpeg -i out.mp4 -vf hflip out2.mp4
fi

