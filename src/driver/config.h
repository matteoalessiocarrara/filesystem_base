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

# ifndef CONFIG_H
# define CONFIG_H

# include "types.h"


# define _little_endian_

/* Lunghezza della bitmap in byte.
 * WARNING Assicurarsi che il tipo sia abbastanza grande per evitare overflow.
 * Deve contenere un valore di 1/8 dei byte sul disco. Su un disco di 16 byte
 * per es. dovrà contenere il valore "2" (1/8*16) */
typedef uint_least16_t bitmap_len_bytes_t;

/* Questo tipo è utilizzato per salvare la dimensione del disco (in byte) */
typedef uint_least16_t disk_size_t;

/* Questo tipo contiene la lunghezza della bitmap (in byte). La bitmap ha una
 * lunghezza pari ad 1/8 della dimensione del disco. */
typedef uint_least16_t bitmap_length_t;


# endif /* CONFIG_H */
