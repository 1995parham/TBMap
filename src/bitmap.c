/*
 * In The Name Of God
 * ========================================
 * [] File Name : bitmap.c
 *
 * [] Creation Date : 22-12-2015
 *
 * [] Created By : Parham Alvani (parham.alvani@gmail.com)
 * =======================================
*/
/*
 * Copyright (c) 2015 Parham Alvani.
*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "bitmap.h"

void bitmap_image_delete(struct BITMAP_IMAGE *image, int is_write)
{
	int i;

	if (is_write) {
		TEST_W_FD(image->fd);

		lseek(image->fd, (off_t) (sizeof(struct BITMAP_FILE_HEADER) +
		                          image->info_header->dib_header_size),
			SEEK_SET);

		if (image->color_table) {
			for (i = 0; i <
			            image->info_header->colors_in_color_table; i++) {
				write(image->fd, image->color_table + i,
					sizeof(struct RGBQUAD));
			}
		}
	}
	close(image->fd);

	if (image->pixel_table) {
		for (i = 0; i < image->info_header->image_width; i++) {
			free(image->pixel_table[i]);
		}
		free(image->pixel_table);
	}
	if (image->file_header)
		free(image->file_header);
	if (image->info_header)
		free(image->info_header);
	if (image->color_table)
		free(image->color_table);

	free(image);

}

struct BITMAP_IMAGE *bitmap_image_new_from_fd(int fd)
{
	struct BITMAP_IMAGE *image = malloc(sizeof(struct BITMAP_IMAGE));
	image->fd = fd;
	image->info_header = NULL;
	image->file_header = NULL;
	image->color_table = NULL;
	image->pixel_table = NULL;
	return image;
}

ssize_t bitmap_image_pixel_table(struct BITMAP_IMAGE *image)
{
	lseek(image->fd, image->file_header->file_offset_to_pixel_array,
		SEEK_SET);

	int i;
	ssize_t retval = 0;

	image->pixel_table = malloc(
		image->info_header->image_width * sizeof(struct RGBAX *));
	for (i = 0; i < image->info_header->image_width; i++) {
		image->pixel_table[i] = malloc(
			image->info_header->image_height *
			sizeof(struct RGBAX));
	}

	return retval;
}

ssize_t bitmap_image_color_table(struct BITMAP_IMAGE *image)
{
	if (image->file_header == NULL || image->info_header == NULL)
		return -1;
	if (image->info_header->colors_in_color_table == 0)
		return 0;

	lseek(image->fd, (off_t) (sizeof(struct BITMAP_FILE_HEADER) +
	                          image->info_header->dib_header_size),
		SEEK_SET);

	int i;
	ssize_t retval = 0;

	image->color_table = malloc(image->info_header->colors_in_color_table *
	                            sizeof(struct RGBQUAD));
	for (i = 0; i < image->info_header->colors_in_color_table; i++) {
		retval += read(image->fd, image->color_table + i,
			sizeof(struct RGBQUAD));
	}

	return retval;

}


ssize_t bitmap_image_header(struct BITMAP_IMAGE *image)
{
	lseek(image->fd, 0, SEEK_SET);

	ssize_t retval;

	image->file_header = malloc(sizeof(struct BITMAP_FILE_HEADER));
	retval = read(image->fd, image->file_header,
		sizeof(struct BITMAP_FILE_HEADER));
	if (retval < sizeof(struct BITMAP_FILE_HEADER))
		return retval;

	image->info_header = malloc(sizeof(struct BITMAP_INFO_HEADER));
	retval += read(image->fd, image->info_header,
		sizeof(struct BITMAP_INFO_HEADER));
	if (retval - sizeof(struct BITMAP_FILE_HEADER) <
	    sizeof(struct BITMAP_INFO_HEADER))
		return retval;

	return retval;
}


