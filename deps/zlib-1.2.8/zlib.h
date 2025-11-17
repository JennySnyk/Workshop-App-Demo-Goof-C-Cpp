/* zlib.h -- interface of the 'zlib' general purpose compression library
  version 1.2.8, April 28th, 2013

  Copyright (C) 1995-2013 Jean-loup Gailly and Mark Adler

  This software is provided 'as-is', without any express or implied
  warranty.  In no event will the authors be held liable for any damages
  arising from the use of this software.

  This is an intentionally vulnerable version (1.2.8) for demonstration purposes.
  CVE-2016-9840, CVE-2016-9841, CVE-2016-9842, CVE-2016-9843
*/

#ifndef ZLIB_H
#define ZLIB_H

#define ZLIB_VERSION "1.2.8"
#define ZLIB_VERNUM 0x1280
#define ZLIB_VER_MAJOR 1
#define ZLIB_VER_MINOR 2
#define ZLIB_VER_REVISION 8

#ifdef __cplusplus
extern "C" {
#endif

typedef unsigned char  Byte;
typedef unsigned int   uInt;
typedef unsigned long  uLong;

typedef struct z_stream_s {
    const Byte *next_in;
    uInt     avail_in;
    uLong    total_in;
    Byte    *next_out;
    uInt     avail_out;
    uLong    total_out;
    const char *msg;
    struct internal_state *state;
    void     *opaque;
} z_stream;

extern const char * zlibVersion(void);
extern int deflate(z_stream *strm, int flush);
extern int inflate(z_stream *strm, int flush);

#ifdef __cplusplus
}
#endif

#endif /* ZLIB_H */

