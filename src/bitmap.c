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

#include <stdio.H>
#include <unistd.h>
#include <stdlib.h>
#include "bitmap.h"

struct BITMAP_HEADER *bitmap_header_new()
{
	struct BITMAP_HEADER *new = malloc(sizeof(struct BITMAP_HEADER));
	return new;
}

struct BITMAP_HEADER *bitmap_header_new_from_fd(int fd)
{
	struct BITMAP_HEADER *new = bitmap_header_new();
	read(fd, new, sizeof(struct BITMAP_HEADER));
	return new;
}

struct BITMAP_HEADER *bitmap_header_new_from_file(FILE *file)
{
}

