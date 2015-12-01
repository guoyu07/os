#!/bin/bash -x

IMG=../boot.img

dd if=kernel of=$IMG seek=1 conv=notrunc
