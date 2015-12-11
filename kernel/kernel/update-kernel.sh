#!/bin/bash -x

IMG=../boot.img

dd if=kernel.elf of=$IMG seek=1 conv=notrunc
