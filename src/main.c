/*
 * In The Name Of God
 * ========================================
 * [] File Name : main.c
 *
 * [] Creation Date : 22-12-2015
 *
 * [] Created By : Parham Alvani (parham.alvani@gmail.com)
 * =======================================
*/
/*
 * Copyright (c) 2015 Parham Alvani.
*/
#include "bitmap.h"
#include <fcntl.h>

int main(int argc, char *argv[])
{
	int fd = open("image.bmp", O_RDWR);
	struct BITMAP_IMAGE *bmp_image = bitmap_image_new_from_fd(fd);
	int i;
	bitmap_image_header(bmp_image);
	printf("%d\n", bmp_image->info_header->colors_in_color_table);
	printf("%u\n", bmp_image->info_header->image_width);
	bitmap_image_color_table(bmp_image);
	for (i = 0; i < bmp_image->info_header->colors_in_color_table; i++) {
		printf("****\n");
		printf("%u\n", bmp_image->color_table[i].red);
		bmp_image->color_table[i].red =
			255 - bmp_image->color_table[i].red;
		printf("%u\n", bmp_image->color_table[i].green);
		bmp_image->color_table[i].green =
			255 - bmp_image->color_table[i].green;
		printf("%u\n", bmp_image->color_table[i].blue);
		bmp_image->color_table[i].blue =
			255 - bmp_image->color_table[i].blue;
		printf("%u\n", bmp_image->color_table[i].reserved);
		printf("****\n");
	}
	bitmap_image_delete(bmp_image, 1);
}
