/*
 * In The Name Of God
 * ========================================
 * [] File Name : common.h
 *
 * [] Creation Date : 18-05-2015
 *
 * [] Created By : Parham Alvani (parham.alvani@gmail.com)
 * =======================================
*/
/*
 * Copyright (c) 2015 Parham Alvani.
*/
#ifndef COMMON_H
#define COMMON_H

#define MAX_BUFF (1000 * 1000)

void sdie(const char *fmt, ...)
	__attribute__((format(printf, 1, 2)));

void udie(const char *fmt, ...)
	__attribute__((format(printf, 1, 2)));

void ulog(const char *fmt, ...)
	__attribute__((format(printf, 1, 2)));

void slog(const char *fmt, ...)
	__attribute__((format(printf, 1, 2)));

#endif
