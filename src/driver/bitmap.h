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
# include "config.h"


/* Lo spazio che l'header usa su disco (la somma degli elementi di bitmap_header) */
# define BITMAP_HEADER_PHYSICAL_SIZE_BYTES sizeof(bitmap_length_t)

typedef struct _bitmap_header
{
	bitmap_length_t bitmap_len_bytes;
} bitmap_header;


/* Calcola la dimensione della bitmap basandosi sulla dimensione del disco (header
 * escluso) */
bitmap_length_t bitmap_calc_lenght_bytes(disk d);

/* Restituisce l'offset su disco per accedere ad una posizione nella bitmap */
size_t bitmap_get_physical_offset(size_t bitmap_offset);

/* Legge un byte fisico dalla bitmap, contenente (anche) il bit nella posizione
 * bitmap_offset (più i 7 bit vicini). Il bit richiesto può essere ottenuto con
 * bitmap_get_bit_in_byte() */
byte bitmap_get_byte(disk d, size_t bitmap_offset);

/* Estrae un bit specifico (quello alla posizione bitmap_offset) da un byte ottenuto
 * con bitmap_get_byte() */
byte bitmap_get_bit_in_byte(byte b, size_t bitmap_offset);

/* Restituisce il bit alla posizione bitmap_offset */
byte bitmap_get_bit(disk d, size_t bitmap_offset);

/* Inizializza un disco */
void bitmap_create(disk d);

/* Imposta lo spazio utilizzato: dal byte "start" del disco fino a start + offset */
void bitmap_set_used(disk d, size_t start, size_t offset, bool used);
bool bitmap_is_byte_free_at(disk d, size_t position);




# endif /* BITMAP_H */
