#!/bin/bash

MNTPOINT=/tmp/ABCDEFG
LOOP=$(sudo losetup -f)
IMG=../boot.img
BIN=./bootsector

[ "X$LOOP" == "X" ] && echo "loop busy" && exit 1

sudo losetup $LOOP $IMG -o 1048576
[ -d $MNTPOINT ] || mkdir $MNTPOINT
sudo mount $LOOP $MNTPOINT
sudo cp -f $BIN $MNTPOINT
sync
sudo umount $MNTPOINT
sudo losetup -d $LOOP

