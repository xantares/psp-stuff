#!/bin/sh

PSPDIR=/media/disk
NAME=Show\ Foot
mkdir -p $PSPDIR/PSP/GAME/$NAME
cp EBOOT.PBP $PSPDIR/PSP/GAME/$NAME
cp data $PSPDIR/PSP/GAME/$NAME
# ls EBOOT.PBP *.png | xargs -i -t cp {} $PSPDIR/PSP/GAME/$NAME
