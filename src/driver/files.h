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


# ifndef FILES_H
# define FILES_H

# include <time.h>

# include "config.h"
# include "types.h"


enum ENTRY_HEADER_ATTRIBUTES
{
	EXECUTE		= 0b00000001,
	WRITE		= 0b00000010,
	READ		= 0b00000100,
	DIRECTORY	= 0b00001000,
	HIDDEN		= 0b00010000,
	IN_USE		= 0b00100000
};

/* WARNING Tenere sincronizzato con la struct */
# define ENTRY_HEADER_SIZE_BYTES sizeof(byte) + sizeof(uint_least32_t) + \
	sizeof(entry_data_lenght_t) + FILENAME_LENGHT + 1 + sizeof(disk_position_t)

typedef struct _entry_header
{
	byte attributes;
	uint_least32_t modification_time;
	entry_data_lenght_t data_length;
	char name[FILENAME_LENGHT + 1];
	disk_position_t continuation_header_position;
} entry_header;

/* WARNING Tenere sincronizzato con la struct */
# define CONTINUATION_HEADER_SIZE_BYTES (sizeof(entry_data_lenght_t) + sizeof(disk_position_t))

typedef struct _continuation_header
{
	entry_data_lenght_t data_length;
	disk_position_t continuation_header_position;
} continuation_header;


/* Abilita attribute sulla variabile var */
# define entryheader_enable_attribute(attribute, var) (var |= attribute)
/* Disabilita attribute sulla variabile var */
# define entryheader_disable_attribute(attribute, var) (var &= (~attribute))
# define entryheader_is_enabled_attribute(attribute, var) (var & attribute)

void write_entry_header(disk d, disk_position_t where, entry_header header);
entry_header read_entry_header(disk d, disk_position_t start);
void write_continuation_header(disk d, disk_position_t where, continuation_header header);
continuation_header read_continuation_header(disk d, disk_position_t start);


# endif /* FILES_H */




