/* Synthetic 1x1 RGB PNG. This test never opens or executes the game. */
#include <stdio.h>
#include <stddef.h>
#include <string.h>
#include "pngpriv.h"

static const unsigned char image[] = {
    137,80,78,71,13,10,26,10,0,0,0,13,73,72,68,82,
    0,0,0,1,0,0,0,1,8,2,0,0,0,144,119,83,222,
    0,0,0,12,73,68,65,84,120,156,99,224,81,178,0,0,
    0,164,0,103,152,208,224,152,0,0,0,0,73,69,78,68,
    174,66,96,130
};
static size_t position;

static void read_memory(png_structp png, png_bytep out, png_size_t count)
{
    if (position + count > sizeof(image))
        png_error(png, "unexpected end of synthetic PNG");
    memcpy(out, image + position, count);
    position += count;
}

int main(void)
{
    png_structp png = png_create_read_struct("1.5.2", NULL, NULL, NULL);
    png_infop info;
    unsigned char row[8] = {0};
    if (!png || strcmp(png_get_header_ver(NULL), "1.5.2") != 0)
        return 1;
    if (offsetof(struct png_info_def, width) != 0 ||
        offsetof(struct png_info_def, height) != 4 ||
        offsetof(struct png_info_def, rowbytes) != 12 ||
        offsetof(struct png_info_def, bit_depth) != 24 ||
        offsetof(struct png_info_def, interlace_type) != 28 ||
        offsetof(struct png_info_def, channels) != 29 ||
        offsetof(struct png_info_def, pixel_depth) != 30)
        return 2;
    if (setjmp(png_jmpbuf(png)))
        return 3;
    info = png_create_info_struct(png);
    if (!info)
        return 4;
    png_set_read_fn(png, NULL, read_memory);
    png_read_info(png, info);
    png_set_bgr(png);
    png_read_row(png, row, NULL);
    png_read_end(png, NULL);
    if (info->width != 1 || info->height != 1 ||
        row[0] != 56 || row[1] != 34 || row[2] != 12)
        return 5;
    png_destroy_read_struct(&png, &info, NULL);
    puts("libpng 1.5.2: version, target prefix offsets and synthetic 1x1 decode pass");
    return 0;
}
