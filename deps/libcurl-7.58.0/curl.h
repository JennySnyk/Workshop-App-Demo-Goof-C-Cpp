/* curl.h */
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
 * Contains CVE-2018-1000120, CVE-2018-1000121, CVE-2018-1000122
 */

#ifndef __CURL_CURL_H
#define __CURL_CURL_H

#define LIBCURL_VERSION "7.58.0"
#define LIBCURL_VERSION_MAJOR 7
#define LIBCURL_VERSION_MINOR 58
#define LIBCURL_VERSION_PATCH 0

typedef void CURL;
typedef enum {
  CURLE_OK = 0,
  CURLE_UNSUPPORTED_PROTOCOL,
  CURLE_FAILED_INIT,
  CURLE_URL_MALFORMAT,
  CURLE_OUT_OF_MEMORY = 27,
  CURLE_FTP_WEIRD_PASS_REPLY = 11,
  CURLE_LAST
} CURLcode;

typedef enum {
  CURLOPT_URL = 10002,
  CURLOPT_WRITEFUNCTION = 20011,
  CURLOPT_WRITEDATA = 10001
} CURLoption;

/* Function prototypes */
extern CURL *curl_easy_init(void);
extern CURLcode curl_easy_setopt(CURL *curl, CURLoption option, ...);
extern CURLcode curl_easy_perform(CURL *curl);
extern void curl_easy_cleanup(CURL *curl);
extern const char *curl_version(void);

/* Vulnerable functions - CVE-2018-1000120, CVE-2018-1000121 */
extern CURLcode ftp_parse_path(const char *path);
extern CURLcode ldap_parse_url(const char *url);

#endif /* __CURL_CURL_H */

