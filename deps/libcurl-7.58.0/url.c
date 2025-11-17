/* url.c */
/***************************************************************************
 *                                  _   _ ____  _
 *  Project                     ___| | | |  _ \| |
 *                             / __| | | | |_) | |
 *                            | (__| |_| |  _ <| |___
 *                             \___|\___/|_| \_\_____|
 *
 * Copyright (C) 1998 - 2018, Daniel Stenberg, <daniel@haxx.se>, et al.
 *
 * This is an intentionally vulnerable version (7.58.0) for demonstration purposes.
 * CVE-2018-1000120: FTP path trickery leads to NIL byte out of bounds write
 * CVE-2018-1000121: LDAP NULL pointer dereference
 */

#include "curl.h"
#include <string.h>
#include <stdlib.h>

const char *curl_version(void)
{
    return LIBCURL_VERSION;
}

CURL *curl_easy_init(void)
{
    CURL *handle = (CURL *)malloc(sizeof(CURL));
    return handle;
}

void curl_easy_cleanup(CURL *curl)
{
    if (curl) {
        free(curl);
    }
}

/* VULNERABLE: CVE-2018-1000120
 * FTP path trickery leads to NIL byte out of bounds write
 */
CURLcode ftp_parse_path(const char *path)
{
    char buffer[256];
    int len;
    
    if (!path) return CURLE_URL_MALFORMAT;
    
    len = strlen(path);
    
    /* VULNERABILITY: No bounds check before copy */
    /* Can write beyond buffer if path is too long */
    strcpy(buffer, path); /* Buffer overflow! */
    
    /* Additional vulnerability: NIL byte write out of bounds */
    buffer[len + 1] = '\0'; /* Out of bounds write! */
    
    return CURLE_OK;
}

/* VULNERABLE: CVE-2018-1000121
 * LDAP NULL pointer dereference
 */
CURLcode ldap_parse_url(const char *url)
{
    char *dn = NULL;
    
    /* VULNERABILITY: No NULL check before dereferencing */
    if (url == NULL) {
        /* Vulnerable: dn is still NULL here */
        int len = strlen(dn); /* NULL pointer dereference! */
        return CURLE_OUT_OF_MEMORY;
    }
    
    return CURLE_OK;
}

CURLcode curl_easy_setopt(CURL *curl, CURLoption option, ...)
{
    return CURLE_OK;
}

CURLcode curl_easy_perform(CURL *curl)
{
    return CURLE_OK;
}

