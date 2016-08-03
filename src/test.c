/*
 * Copyright 2016 Matteo Alessio Carrara <sw.matteoac@gmail.com>
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

# include <malloc.h>
# include <stdio.h>
# include <math.h>



/* WARNING Queste funzioni sono qui solo per facilitare il debug. In futuro
 * dovranno essere spostate in una libreria condivisa */



/* EMULAZIONE C99 */



/* stdint.h */
typedef unsigned char uint_least8_t;
typedef unsigned short uint_least16_t;


/* stdbool.h */
# define true 1
# define false 0

typedef uint_least8_t bool;




/* TIPI */



/* Lunghezza della bitmap in byte.
 * WARNING Assicurarsi che il tipo sia abbastanza grande per evitare overflow.
 * Deve contenere un valore di 1/8 dei byte sul disco. Su un disco di 16 byte
 * per es. dovrà contenere il valore "2" (1/8*16) */
typedef uint_least16_t bitmap_byte_len_t;


struct bitmap
{
		bitmap_byte_len_t	byte_len;
		void				*content;
		
		/* Se per es. la bitmap è di 9 bit, devono essere allocati 2 byte. Gli
		 *  ultimi 7 bit del secondo byte comunque saranno solo di riempimento
		 * (NON DEVONO ESSERE CONSIDERATI VALIDI) */
		uint_least8_t			padding_bits;
};



/* ALTRO */



long file_get_byte_size(FILE *fp)
{
	long prev=ftell(fp), size;
	
	fseek(fp, 0, SEEK_END);
	size=ftell(fp);

	fseek(fp, prev, SEEK_SET);
	return size;
}



/* BITMAP */
/* TODO Compressione */


/* Offset in bit */
static void __set_bit(void *buffer, size_t offset, bool enable)
{
	if (enable)
		*((uint_least8_t*)buffer + offset/8) |= (1 << (7 - offset%8));
	else
		*((uint_least8_t*)buffer + offset/8) &= ~(1 << (7 - offset%8));
}


/* Imposta lo spazio utilizzato
 * Start e offset in byte */
static void __bitmap_set_used(struct bitmap *b, size_t start, size_t offset)
{
	size_t i = 0;
	for(; i < offset; i++)
		__set_bit(b->content, start + i, true);
}


/* Restituisce lo spazio fisicamente usato da una struct bitmap (in byte) */
static size_t __bitmap_get_size(struct bitmap *b)
{
	/* La bitmap contiene un puntatore a content, ma va considerata la dimensione
	 * del suo contenuto, non del puntatore */
	return sizeof(b->byte_len) + sizeof(b->padding_bits) + b->byte_len;
}


/* Restituisce la struct inizializzata */
static struct bitmap __bitmap_create(size_t disk_size)
{
	struct bitmap ret;
	
	ret.byte_len = ceil((float)disk_size / 8);
	ret.padding_bits = (disk_size % 8)? 8 - (disk_size % 8) : 0;
	ret.content = calloc(ret.byte_len, 1);
	
	/* Va segnato lo spazio occupato dalla bitmap stessa */
	__bitmap_set_used(&ret, 0, __bitmap_get_size(&ret));
	
	return ret;
}


/* Scrive la bitmap su un disco */
static void __bitmap_write(struct bitmap *b, FILE *dev)
{
	fwrite(&(b->byte_len), sizeof(b->byte_len), 1, dev);
	fwrite(&(b->padding_bits), sizeof(b->padding_bits), 1, dev);
	fwrite(b->content, 1, b->byte_len, dev);
}



/* API */



void create_fs(char *dev)
{
	FILE *devf = fopen(dev, "r+b");
	struct bitmap b = __bitmap_create(file_get_byte_size(devf));
	
	__bitmap_write(&b, devf);
}



/* TEST */



int main()
{	
	create_fs("./test");
	return 0;
}
