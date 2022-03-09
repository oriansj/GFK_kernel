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

#include "termio.h"
#include <stddef.h>

// This is the x86's VGA textmode buffer. To display text, we write data to this memory location
int _term_col = 0;
int _term_row = 0;

void scroll_screen()
{
	int i = 0;
	int max = ((VGA_ROWS - 1) * (VGA_COLS << 1));
	char* buffer = VGA_BUFFER;
	while(i < max)
	{
		buffer[i] = buffer[i+(VGA_COLS << 1)];
		i = i + 1;
	}

	int j = VGA_COLS;
	while(j >= 0)
	{
		buffer[i] = ' ';
		buffer[i+1] = 0x0;
		i = i + 2;
		j = j - 1;
	}
}

void term_write_char(char c, char color, int col, int row)
{
	if(col > VGA_COLS)
	{
		term_error("term_write_char col exceeds col limit\n");
		return;
	}

	if(row > VGA_ROWS)
	{
		term_error("term_write_char row exceeds row limit\n");
		return;
	}

	// Entries in the VGA buffer take the binary form CCCCCCCCBBBBFFFF, where:
	// - B is the background color
	// - F is the foreground color
	// - C is the ASCII character
	char* buffer = VGA_BUFFER;
	int index = ((VGA_COLS * row) + col) << 1;
	buffer[index + 1] = color;
	buffer[index] = c;
}

void term_write_raw(char* s, char color)
{
	if(NULL == s)
	{
		term_error("term_write received a null string\n");
		return;
	}

	int i = 0;
	int c = s[0];
	while(0 != c)
	{
		/* deal with newline char */
		if(('\n' == c) || ('\r' == c))
		{
			_term_row = _term_row + 1;
			_term_col = 0;
			i = i + 1;
			c = s[i];
			continue;
		}

		/* wrap around */
		if(_term_col > VGA_COLS)
		{
			_term_row = _term_row + 1;
			_term_col = 0;
		}

		if(_term_row >= VGA_ROWS)
		{
			scroll_screen();
			_term_row = VGA_ROWS - 1;
		}

		/* now write it */
		term_write_char(c, color, _term_col, _term_row);
		_term_col = _term_col + 1;
		i = i + 1;
		c = s[i];
	}
}

void term_error(char* msg)
{
	term_write_raw(msg, 0x0C);
}

void term_write(char*msg)
{
	term_write_raw(msg, 0x0A);
}

void term_init()
{
	_term_col = 0;
	_term_row = 0;
	int col = 0;
	int row = 0;
	while (row < VGA_ROWS)
	{
		while (col < VGA_COLS)
		{
			term_write_char(' ', 0x00, col, row);
			col = col + 1;
		}
		col = 0;
		row = row + 1;
	}
}
