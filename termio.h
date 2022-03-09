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

extern char* VGA_BUFFER;
#define VGA_COLS 80
#define VGA_ROWS 25

void scroll_screen();
void term_write_char(char c, char color, int col, int row);
void term_write_raw(char* s, char color);
void term_write(char* msg);
void term_error(char* msg);
void term_init();
