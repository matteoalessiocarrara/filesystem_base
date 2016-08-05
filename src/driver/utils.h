/*
 * Copyright 2016 Matteo Alessio Carrara <sw.matteoac@gmail.com>
 * Copyright 2016 Andrea Drius
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 */


# ifndef UTILS_H
# define UTILS_H

# include "filesystem.h"
# include "config.h"
# include "types.h"


/* Restituisce un byte contenente solo il bit */
# define get_bit(buffer_pnt, offset) \
	((*((unsigned char *)(buffer_pnt) + (offset) / 8) >> (7 - (offset) % 8)) & 1)

# define enable_bit(buffer_pnt, offset) \
	(*((unsigned char *)(buffer_pnt) + (offset) / 8) |= (1 << (7 - (offset) % 8)))

# define disable_bit(buffer_pnt, offset) \
	(*((unsigned char *)(buffer_pnt) + (offset) / 8) &= ~(1 << (7 - (offset) % 8)))

byte read_8bit(disk d, disk_position_t position);
uint_least16_t read_16bit(disk d, disk_position_t position);
uint_least32_t read_32bit(disk d, disk_position_t position);


# endif /* UTILS_H */
