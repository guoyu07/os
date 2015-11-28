#!/bin/bash

LOOP=$(sudo losetup -f)
IMG=../boot.img
BIN=./boot.bin

[ "X$LOOP" == "X" ] && echo "loop busy" && exit 1

sudo losetup $LOOP $IMG
sudo dd if=$BIN of=$LOOP
sudo losetup -d $LOOP

