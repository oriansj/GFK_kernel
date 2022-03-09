/* Copyright (C) 2022 Jeremiah Orians
 * This file is part of stage0.
 *
 * stage0 is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * stage0 is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with stage0.  If not, see <http://www.gnu.org/licenses/>.
 */

.extern kmain
	.global start
	.global VGA_BUFFER

// the section we need to be booted by grub
// MB_CHECKSUM + MB_FLAGS + MB_MAGIC = 0
.section .multiboot
	.align 8
	.long 0x1BADB002   //MB_MAGIC
	.long 0x00000003   //MB_FLAGS
	.long 0xE4524FFB   //MB_CHECKSUM

// setup 4KB stack
.section .bss
	.align 16
stack_bottom: .skip 4096
stack_top:

.section .text
start:
	// setup C stack
	mov $stack_top, %esp
	push %eax
	push %ebx
	call kmain

shutdown:
	cli      // Disable CPU interrupts
	hlt      // Halt the CPU
	jmp shutdown // If that didn't work, loop around and try again.

.section .rodata
// pointer to where VGA memory block is
VGA_BUFFER: .long 0xB8000
