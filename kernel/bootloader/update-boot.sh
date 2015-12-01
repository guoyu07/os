#!/bin/bash -x

IMG=../boot.img
BIN=./boot.bin

dd if=$BIN of=$IMG conv=notrunc

