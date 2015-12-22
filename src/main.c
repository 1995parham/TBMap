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
#include <stdio.h>

int main(int argc, char *argv[])
{
	int fd = open("image.bmp", O_RDONLY);
	struct BITMAP_HEADER *bmph = bitmap_header_new_from_fd(fd);
	printf("%d\n", bmph->file_header.file_size);
}
