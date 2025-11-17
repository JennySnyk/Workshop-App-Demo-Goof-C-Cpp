/* inflate.c -- zlib decompression
 * Copyright (C) 1995-2013 Mark Adler
 * 
 * This is an intentionally vulnerable version (1.2.8) for demonstration purposes.
 * Contains vulnerabilities: CVE-2016-9840, CVE-2016-9841, CVE-2016-9842, CVE-2016-9843
 */

#include "zlib.h"

const char * zlibVersion(void)
{
    return ZLIB_VERSION;
}

int inflate(z_stream *strm, int flush)
{
    /* Vulnerable implementation - for demonstration only */
    if (strm == NULL) return -1;
    
    /* CVE-2016-9840: Out-of-bounds pointer arithmetic in inftrees.c */
    /* CVE-2016-9841: Out-of-bounds pointer arithmetic in inffast.c */
    /* Vulnerable code would be here */
    
    return 0;
}

int deflate(z_stream *strm, int flush)
{
    /* Simplified implementation */
    if (strm == NULL) return -1;
    return 0;
}

