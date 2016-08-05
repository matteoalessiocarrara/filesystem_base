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


# ifndef BITMAP_H
# define BITMAP_H

# include "filesystem.h"
# include "utils.h"
# include "config.h"


/* Lo spazio che l'header usa su disco (la somma degli elementi di bitmap_header) */
# define BITMAP_HEADER_PHYSICAL_SIZE_BYTES sizeof(bitmap_length_t)

typedef struct _bitmap_header
{
	bitmap_length_t bitmap_len_bytes;
} bitmap_header;


/* Calcola la dimensione della bitmap basandosi sulla dimensione del disco (header
 * escluso) */
# define bitmap_calc_lenght_bytes(disk_) ceil(disk_.size_bytes/8.0)

/* Restituisce l'offset su disco per accedere ad un bit nella bitmap */
# define bitmap_get_physical_offset(bitmap_bit_position) \
	(BITMAP_HEADER_PHYSICAL_SIZE_BYTES + ceil((bitmap_bit_position)/8.0))

/* Legge un byte fisico dalla bitmap, contenente (anche) il bit nella posizione
 * bitmap_bit_position (più i 7 bit vicini) */
# define bitmap_get_byte(disk_, bitmap_bit_position)\
	read_byte(disk_, bitmap_get_physical_offset(bitmap_bit_position))

/* Restituisce il bit nella bitmap alla posizione bitmap_bit_position */
byte bitmap_get_bit(disk d, size_t bitmap_bit_position);

/* Inizializza un disco */
void bitmap_create(disk d);

/* Imposta lo spazio utilizzato: dal byte "start" del disco fino a start + offset */
void bitmap_set_used(disk d, size_t start, size_t offset, bool used);
bool bitmap_is_byte_free_at(disk d, size_t position);







# endif /* BITMAP_H */
