## Copyright (C) 2016 Jeremiah Orians
## This file is part of stage0.
##
## stage0 is free software: you can redistribute it and/or modify
## it under the terms of the GNU General Public License as published by
## the Free Software Foundation, either version 3 of the License, or
## (at your option) any later version.
##
## stage0 is distributed in the hope that it will be useful,
## but WITHOUT ANY WARRANTY; without even the implied warranty of
## MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
## GNU General Public License for more details.
##
## You should have received a copy of the GNU General Public License
## along with stage0.  If not, see <http://www.gnu.org/licenses/>.

# Don't rebuild the built things in bin
VPATH = bin
CC := i686-elf-gcc

all: kernel.elf

kernel.elf: start.o kernel.o termio.o linker.ld | bin
	$(CC) -ffreestanding -nostdlib -g -T linker.ld bin/start.o bin/kernel.o bin/termio.o -o bin/kernel.elf -lgcc

start.o: start.S | bin
	$(CC) -std=gnu99 -lgcc -ffreestanding -g -c start.S -o bin/start.o

kernel.o: kernel.c | bin
	$(CC) -std=gnu99 -lgcc -ffreestanding -g -c kernel.c -o bin/kernel.o

termio.o: termio.c | bin
	$(CC) -std=gnu99 -lgcc -ffreestanding -g -c termio.c -o bin/termio.o

# Clean up after ourselves
.PHONY: clean
clean:
	rm -rf bin/

.PHONY: clean-hardest
clean-hardest:
	git reset --hard
	git clean -fd
	rm -rf bin/

clean-SO-hard-You-probably-do-NOT-want-this-option-because-it-will-destory-everything:
	@echo "I REALLY REALLY HOPE you know what you are doing"
	git reset --hard
	git clean -xdf
	rm -rf bin/

# Our essential folders
bin:
	mkdir -p bin

run: kernel.elf | bin
	qemu-system-i386  -kernel bin/kernel.elf -m 4096
