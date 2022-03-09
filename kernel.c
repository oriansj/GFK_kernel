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

#include <stdint.h>
#include "multiboot.h"
#include "termio.h"

// First, let's do some basic checks to make sure we are using our x86-elf cross-compiler correctly
#if defined(__linux__)
	#error "This code must be compiled with a cross-compiler"
#elif !defined(__i386__)
	#error "This code must be compiled with an x86-elf compiler"
#endif


void kmain(multiboot_info_t* mbd, uint32_t magic)
{
	term_init();
	term_write("Hello, World!\n");

	for(int i = 0; i < 256; i = i + 1)
	{
		if(0 == (i & 0xF)) term_write_raw("\n", 0x00);
		term_write_raw("Z", i);
	}

	term_error("\nWelcome to the kernel.\n");

	for(int i = 0; i < 256; i = i + 1)
	{
		if(0 == (i & 0xF)) term_write_raw("\n", 0x00);
		term_write_raw("Z", i);
	}
	scroll_screen();
	term_write_char('A', 0x0A, 3, 24);
	scroll_screen();
	term_write_char('B', 0x0B, 3, 24);
	scroll_screen();
	term_write_char('C', 0x0C, 3, 24);
	scroll_screen();
	term_write_char('D', 0x0D, 3, 24);
	return;
}
