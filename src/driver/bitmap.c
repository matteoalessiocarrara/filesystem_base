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

# include <stdio.h>
# include <math.h>

# include "filesystem.h"
# include "bitmap.h"
# include "types.h"
# include "utils.h"


/* TODO Compressione */


bitmap_length_t
bitmap_calc_lenght_bytes(disk d)
{
	return ceil(d.size_bytes/8.0);
}


size_t
bitmap_get_physical_offset(size_t bitmap_offset)
{
	return BITMAP_HEADER_PHYSICAL_SIZE_BYTES + bitmap_offset;
}


byte
bitmap_get_byte(disk d, size_t bitmap_offset)
{
	byte tmp;

	fseek(d.fp, bitmap_get_physical_offset(bitmap_offset), SEEK_SET);
	fread(&tmp, 1, 1, d.fp);

	return tmp;
}


byte
bitmap_get_bit_in_byte(byte b, size_t bitmap_offset)
{
	return get_bit(&b, bitmap_offset % 8);
}


byte
bitmap_get_bit(disk d, size_t bitmap_offset)
{
	byte tmp = bitmap_get_byte(d, bitmap_offset);
	return bitmap_get_bit_in_byte(tmp, bitmap_offset);
}


void
bitmap_create(disk d)
{
	bitmap_header header;
	uint_least8_t invalid_bits;

	header.bitmap_len_bytes = bitmap_calc_lenght_bytes(d);
	invalid_bits = (d.size_bytes % 8)? 8 - (d.size_bytes % 8) : 0;

	rewind(d.fp);

	/* WARNING L'header (struct) non va scritto direttamente: the compiler may
	 * add padding for alignment requirements */
	fwrite(&header.bitmap_len_bytes, sizeof(header.bitmap_len_bytes), 1, d.fp);

	/* Azzera la bitmap */
	bitmap_set_used(d, 0, d.size_bytes, false);

	/* Segna lo spazio utilizzato dalla bitmap stessa (attenzione, va considerato
	 * anche l'header) */
	bitmap_set_used(d, 0, BITMAP_HEADER_PHYSICAL_SIZE_BYTES + header.bitmap_len_bytes, true);

	/* Segna come utilizzati i bit non validi */
	if (invalid_bits > 0)
		bitmap_set_used(d, d.size_bytes + 1, invalid_bits - 1, true);
}


void
bitmap_set_used(disk d, size_t start, size_t offset, bool used)
{
	size_t i;
	byte tmp;

	fseek(d.fp, bitmap_get_physical_offset(start), SEEK_SET);

	/* Fa più scritture da un byte */
	for(i = offset / 8.0; i > 0; i--)
		fputc(used? 0xFF : 0x00, d.fp);

	/* Imposta i byte rimanenti */
	if (offset % 8)
	{
		fread(&tmp, 1, 1, d.fp);

		for(i = 0; i < offset % 8; i++)
			set_bit(&tmp, i, used);

		fwrite(&tmp, 1, 1, d.fp);
	}
}


bool
bitmap_is_byte_free_at(disk d, size_t position)
{
	return bitmap_get_bit(d, position) == 0? true : false;
}


/* Restituisce l'offset dall'inizio del disco, o 0 in caso di errore */
/* TODO Qui si può fare un hack, per trovare magari 8 byte liberi si legge direttamente
 * un byte della bitmap invece di chiamare per ogni byte bitmap_is_byte_free_at() */
size_t bitmap_find_free_space(disk d, size_t size)
{
	/* 0 di sicuro non può essere perché c'è l'header della bitmap */
	size_t offset = 0, curr_space_size = 0, i;

	/* La bitmap all'inizio segna lo spazio occupato dalla stessa bitmap, quindi
	 * iniziamo a cercare un po' dopo */
	for(i = BITMAP_HEADER_PHYSICAL_SIZE_BYTES + bitmap_calc_lenght_bytes(d) + 1;
		(i < d.size_bytes) && (curr_space_size < size); i++)
	{
		if (bitmap_is_byte_free_at(d, i))
			curr_space_size++;
		else
			curr_space_size = 0;
	}

	return offset;
}
