#ifndef LIMITS_H
#include <limits.h>
#define LIMITS_H
#endif

#ifndef MAX_PATH
#define MAX_PATH 256
#endif

/* Structure pixel : rouge, bleu, vert */
typedef struct _pixel
{
    unsigned char blue;
    unsigned char green;
    unsigned char red;
} PIXEL;

typedef struct _bitmap
{
    char file_path[MAX_PATH + 1];
    char magic_number[3];             /* Offset : 0x0000 */
    unsigned int size;                /* Offset : 0x0002 */
    unsigned char application[5];     /* Offset : 0x0006 */
    unsigned int start_offset;        /* Offset : 0x000a */
    unsigned int bitmap_header_size;  /* Offset : 0x000e */
    unsigned int width;               /* Offset : 0x0012 */
    unsigned int height;              /* Offset : If bitmap_header_size<=12 then 0x0014 else 0x0016 */
    /*unsigned short int bit_plane;*/ /* Offset : If bitmap_header_size<=12 then 0x0016 else 0x001a (just for good understanding purpose, no need to be stored) */
    unsigned short int depth;         /* Offset : If bitmap_header_size<=12 then 0x0018 else 0x001c */
    unsigned char *header;            /* Stores the header of the file */
    PIXEL *raster;                    /* Stores the picture raster (all the pixels from the picture) */
} BITMAP;

typedef enum _filter
{
    BLUE,
    GREEN,
    RED,
    BLUR,
    MIRROR,
    UNKNOWN
} FILTER;

typedef enum _bool
{
    false,
    true
} bool;

BITMAP *loadBitmap(const char *);
bool allowedBitmapFormat(BITMAP *);
void destroyBitmap(BITMAP *);
void applyFilter(BITMAP *, FILTER);
FILTER getCorrespondingFilter(const char *);
void saveBitmap(BITMAP *);
PIXEL* getPixel(PIXEL* raster, int width, int height, int x, int y);
void setPixel(PIXEL* raster, int width, int height, int x, int y, PIXEL* value);
void applyFilterColor(BITMAP* bmp, FILTER filter);
void applyFilterSimpleBlur(BITMAP* bmp);
void applyFilterMirror(BITMAP* bmp);