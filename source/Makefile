# Copyright 2015
# Author: Prasanna Navaratna
# Date of creation : 03/01/2015
#
# Make file to build the peruse-elf
#

CC=gcc
IDIR=../include
CFLAGS=-I$(IDIR)
DEPS = $(IDIR)

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

peruse-elf: peruse-elf.o
	gcc -o peruse-elf peruse-elf.o $(CFLAGS)
