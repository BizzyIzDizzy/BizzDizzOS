#!/bin/bash

sudo losetup /dev/loop0 floppy.img
sudo mount /dev/loop0 /mnt
sudo cp kernel/kernel.bin /mnt/kernel.bin
sudo umount /dev/loop0
sudo losetup -d /dev/loop0

