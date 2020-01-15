#!/usr/bin/env bash

if [ -e /storage/roms/coco2 ]
then
  ROMPATH=/storage/roms
else
  ROMPATH=/usbdisk/roms/coco2
fi

extra=""

if [ "$1" = "debug" ]
then
  extra="-debug"
fi

if [ "$1" = "avi" ]
then
  extra="-aviwrite out.avi"
fi

mame coco2 -window -rompath ${ROMPATH} \
  -resolution0 640x480 \
  -cart1 java_trs80_demo.bin \
  ${extra}

if [ "$1" = "avi" ]
then
  #mencoder -oac mp3lame -ovc x264 -o video.avi -vf scale=640:480 ~/.mess/snap/out.avi
  ffmpeg -i snap/out.avi -vf hflip -s 640x480 out.mp4
  ffmpeg -i out.mp4 -vf hflip out2.mp4
fi

