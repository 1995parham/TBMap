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
/*
 * Bitmaps should be saved in a file that uses the established bitmap
 * file format and assigned a name with the three-character .bmp extension.
 * The established bitmap file format consists of a BITMAP_FILE_HEADER structure
 * followed by a BITMAP_INFO_HEADER, BITMAP_V4_HEADER, or
 * BITMAP_V5_HEADER structure.
 * An array of RGBQUAD structures (also called a color table) follows the bitmap
 * information header structure.
 * The color table is followed by a second array of indexes into
 * the color table (the actual bitmap data).
 * The bitmap file format is shown in the following illustration.
 * +--------------------+
 * | BITMAP_FILE_HEADER |
 * +--------------------+
 * | BITMAP_INFO_HEADER |
 * +--------------------+
 * |   RGBQUAD array    |
 * +--------------------+
 * | color-index array  |
 * +--------------------+
 */
#ifndef BITMAP_H
#define BITMAP_H

/* constants for the BITMAP_INFO_HEADER.compression field */
#define BI_RGB        0L
#define BI_RLE8       1L
#define BI_RLE4       2L
#define BI_BITFIELDS  3L
#define BI_JPEG       4L
#define BI_PNG        5L

#include <stdint.h>
#include <stdio.h>
#include <fcntl.h>
#include "common.h"

struct RGBAX {
	/*
	 * The intensity of blue in the color.
	 */
	uint32_t blue;
	/*
	 * The intensity of green in the color.
	 */
	uint32_t green;
	/*
	 * The intensity of red in the color.
	 */
	uint32_t red;
	/*
	 *
	 */
	uint32_t alpha;
	/*
	 *
	 */
	uint32_t none;
};

struct RGBQUAD {
	/*
	 * The intensity of blue in the color.
	 */
	uint8_t blue;
	/*
	 * The intensity of green in the color.
	 */
	uint8_t green;
	/*
	 * The intensity of red in the color.
	 */
	uint8_t red;
	/*
	 * This member is reserved and must be zero.
	 */
	uint8_t reserved;
};

struct BITMAP_FILE_HEADER {
	/*
	 * The file type; must be BM.
	*/
	uint16_t signature;
	/*
	 * The size, in bytes, of the bitmap file.
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
	 * The offset, in bytes, from the beginning of the BITMAP_FILE_HEADER
	 * structure to the bitmap bits.
	*/
	uint32_t file_offset_to_pixel_array;
} __attribute__((packed));

struct BITMAP_INFO_HEADER {
	/*
	 * The number of bytes required by the structure.
	 * our supported values are 40, 108, 124
	*/
	uint32_t dib_header_size;
	/*
	 * The width of the bitmap, in pixels.
	*/
	int32_t image_width;
	/*
	 * The height of the bitmap, in pixels.
	 * If image_height is positive, the bitmap is a bottom-up DIB
	 * and its origin is the lower-left corner.
	 * If image_height is negative, the bitmap is a top-down DIB
	 * and its origin is the upper-left corner.
	*/
	int32_t image_height;
	/*
	 * The number of planes for the target device.
	 * This value must be set to 1.
	*/
	uint16_t planes;
	/*
	 * The number of bits-per-pixel.
	 * The bits_per_pixel member of the BITMAP_INFO_HEADER structure
	 * determines the number of bits that define each pixel and the
	 * maximum number of colors in the bitmap.
	 * This member must be one of the following values:
	 * 0, 1, 4, 8, 16, 24, 32
	*/
	uint16_t bits_per_pixel;
	/*
	 * The type of compression for a compressed bottom-up bitmap
	 * (top-down DIBs cannot be compressed).
	 * This member can be one of the following values:
	 * BI_RGB       An uncompressed format
	 * BI_RLE8      A run-length encoded (RLE) format for bitmaps with 8 bpp.
	 *              The compression format is a 2-byte format consisting of
	 *              a count byte followed by a byte containing a color index.
	 *              For more information, see Bitmap Compression.
	 *              https://msdn.microsoft.com/en-us/library/windows/desktop/dd183383(v=vs.85).aspx
	*/
	uint32_t compression;
	/*
	 * The size, in bytes, of the image.
	 * This may be set to zero for BI_RGB bitmaps.
	*/
	uint32_t image_size;
	/*
	 * The horizontal resolution, in pixels-per-meter, of the target device for the bitmap.
	*/
	uint32_t x_pixels_per_meter;
	/*
	 * The vertical resolution, in pixels-per-meter, of the target device for the bitmap.
	*/
	uint32_t y_pixels_per_meter;
	/*
	 * The number of color indexes in the color table that are actually used by the bitmap.
	 * If this value is zero, the bitmap uses the maximum number of colors corresponding
	 * to the value of the bits_per_pixels member for
	 * the compression mode specified by compression.
	*/
	uint32_t colors_in_color_table;
	/*
	 * The number of color indexes that are required for
	 * displaying the bitmap. If this value is zero, all colors are required.
	*/
	uint32_t important_color_count;
} __attribute__((packed));

struct BITMAP_IMAGE {
	int fd;
	struct BITMAP_FILE_HEADER *file_header;
	struct BITMAP_INFO_HEADER *info_header;
	struct RGBQUAD *color_table;
	struct RGBAX **pixel_table;
};

#define TEST_W_FD(fd)                                                      \
        do {                                                               \
                if (!(fcntl(fd, F_GETFL) & O_RDWR))                        \
                        udie("Please open file  with write permission");   \
        } while (0)                                                        \


void bitmap_image_delete(struct BITMAP_IMAGE *image, int is_write);

struct BITMAP_IMAGE *bitmap_image_new_from_fd(int fd);

ssize_t bitmap_image_header(struct BITMAP_IMAGE *image);

ssize_t bitmap_image_color_table(struct BITMAP_IMAGE *image);

ssize_t bitmap_image_pixel_table(struct BITMAP_IMAGE *image);

#endif
