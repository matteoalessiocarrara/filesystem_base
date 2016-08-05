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


# include "filesystem.h"
# include "config.h"
# include "utils.h"
# include "types.h"


byte
read_8bit(disk d, disk_position_t position)
{
	byte tmp;

	fseek(d.fp, position, SEEK_SET);
	fread(&tmp, 1, 1, d.fp);

	return tmp;
}


/* TODO Gestire endian */


uint_least16_t
read_16bit(disk d, disk_position_t position)
{
	uint_least16_t tmp;

	fseek(d.fp, position, SEEK_SET);
	fread(&tmp, 2, 1, d.fp);

	return tmp;
}


uint_least32_t
read_32bit(disk d, disk_position_t position)
{
	uint_least32_t tmp;

	fseek(d.fp, position, SEEK_SET);
	fread(&tmp, 4, 1, d.fp);

	return tmp;
}
