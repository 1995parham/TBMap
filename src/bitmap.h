/*
 * In The Name Of God
 * ========================================
 * [] File Name : bitmap.h
 *
 * [] Creation Date : 22-12-2015
 *
 * [] Created By : Parham Alvani (parham.alvani@gmail.com)
 * =======================================
*/
/*
 * Copyright (c) 2015 Parham Alvani.
*/
#ifndef BITMAP_H
#define BITMAP_H

#include <stdint.h>
#include <stdio.h>

struct BITMAP_FILE_HEADER {
	/*
	 * specifies the file type
	*/
	uint16_t signature;
	/*
	 * specifies the size in bytes of the bitmap file
	*/
	uint32_t file_size;
	/*
	 * reserved; must be 0
	*/
	uint16_t reserved1;
	/*
	 * reserved; must be 0
	*/
	uint16_t reserved2;
	/*
	 * species the offset in bytes from the
	 * bitmap_file_header to the bitmap bits
	*/
	uint32_t file_offset_to_pixel_array;
} __attribute__((packed));

struct BITMAP_INFO_HEADER {
	/*
	 * specifies the number of bytes required by the struct
	*/
	uint32_t dib_header_size;
	//specifies width in pixels
	uint32_t image_width;
	//species height in pixels
	uint32_t image_height;
	//specifies the number of color planes, must be 1
	uint16_t biPlanes;
	//specifies the number of bit per pixel
	uint16_t biBitCount;
	//spcifies the type of compression
	uint32_t biCompression;
	//size of image in bytes
	uint32_t biSizeImage;
	uint32_t biXPelsPerMeter;  //number of pixels per meter in x axis
	uint32_t biYPelsPerMeter;  //number of pixels per meter in y axis
	uint32_t biClrUsed;  //number of colors used by th ebitmap
	uint32_t biClrImportant;  //number of colors that are important
} __attribute__((packed));

struct BITMAP_HEADER {
	struct BITMAP_FILE_HEADER file_header;
	struct BITMAP_INFO_HEADER info_header;
} __attribute__((packed));

struct BITMAP_HEADER *bitmap_header_new();

struct BITMAP_HEADER *bitmap_header_new_from_fd(int fd);

struct BITMAP_HEADER *bitmap_header_new_from_file(FILE *file);

#endif
