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
# include <string.h>

# include "filesystem.h"
# include "config.h"
# include "files.h"
# include "types.h"
# include "utils.h"


void
write_entry_header(disk d, disk_position_t where, entry_header header)
{
	fseek(d.fp, where, SEEK_SET);

	fwrite(&(header.attributes), sizeof(header.attributes), 1, d.fp);
	fwrite(&(header.modification_time), sizeof(header.modification_time), 1, d.fp);
	fwrite(&(header.data_length), sizeof(header.data_length), 1, d.fp);
	fwrite(&(header.name), sizeof(header.name), 1, d.fp);
	fwrite(&(header.continuation_header_position), sizeof(header.continuation_header_position), 1, d.fp);
}


entry_header
read_entry_header(disk d, disk_position_t start)
{
	entry_header header;
	entry_data_lenght_t data_lenght;
	char name[FILENAME_LENGHT + 1];
	disk_position_t continuation_header_position;

	header.attributes = read_8bit(d, start + 0);
	header.modification_time = read_32bit(d, start + 1);

	fseek(d.fp, start + 5, SEEK_SET);
	fread(&data_lenght, sizeof(entry_data_lenght_t), 1, d.fp);
	header.data_length = data_lenght;

	fread(&(header.name), sizeof(header.name), 1, d.fp);

	fread(&continuation_header_position, sizeof(disk_size_t), 1, d.fp);
	header.continuation_header_position = continuation_header_position;

	return header;
}


void
write_continuation_header(disk d, disk_position_t where, continuation_header header)
{
	fseek(d.fp, where, SEEK_SET);

	fwrite(&(header.data_length), sizeof(header.data_length), 1, d.fp);
	fwrite(&(header.continuation_header_position), sizeof(header.continuation_header_position), 1, d.fp);
}


continuation_header
read_continuation_header(disk d, disk_position_t start)
{
	continuation_header header;
	entry_data_lenght_t data_lenght;
	disk_position_t continuation_header_position;

	fseek(d.fp, start, SEEK_SET);

	fread(&data_lenght, sizeof(data_lenght), 1, d.fp);
	header.data_length = data_lenght;

	fread(&continuation_header_position, sizeof(continuation_header_position), 1, d.fp);
	header.continuation_header_position = continuation_header_position;

	return header;
}

