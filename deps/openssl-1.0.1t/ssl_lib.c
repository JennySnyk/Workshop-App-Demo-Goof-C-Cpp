/* ssl_lib.c */
/* Copyright (C) 1995-1998 Eric Young (eay@cryptsoft.com)
 * All rights reserved.
 *
 * This is an intentionally vulnerable version (1.0.1t) for demonstration purposes.
 * Contains Heartbleed: CVE-2014-0160
 */

#include "ssl.h"
#include <string.h>
#include <stdlib.h>

const char *SSLeay_version(int type)
{
    return OPENSSL_VERSION_TEXT;
}

SSL_CTX *SSL_CTX_new(const SSL_METHOD *method)
{
    SSL_CTX *ctx = (SSL_CTX *)malloc(sizeof(SSL_CTX));
    return ctx;
}

SSL *SSL_new(SSL_CTX *ctx)
{
    SSL *s = (SSL *)malloc(sizeof(SSL));
    if (s != NULL) {
        s->version = 0x0301; /* TLS 1.0 */
        s->heartbeat_payload = NULL;
        s->heartbeat_payload_length = 0;
    }
    return s;
}

/* VULNERABLE: Heartbleed implementation
 * CVE-2014-0160: Missing bounds check in heartbeat extension
 * This allows reading beyond allocated memory
 */
int tls1_process_heartbeat(SSL *s)
{
    unsigned char *p;
    unsigned short hbtype;
    unsigned int payload_length;
    unsigned int padding = 16;
    
    /* Vulnerable: No validation of payload_length against actual data */
    /* An attacker can request more data than was sent */
    /* This is the Heartbleed bug! */
    
    p = s->heartbeat_payload;
    hbtype = *p++;
    payload_length = s->heartbeat_payload_length;
    
    /* VULNERABILITY: Missing bounds check here!
     * Should verify: payload_length <= actual_data_length
     * Without this check, we read beyond allocated memory
     */
    
    unsigned char *buffer = (unsigned char *)malloc(payload_length + padding);
    
    /* Vulnerable: Copying more data than was actually received */
    memcpy(buffer, p, payload_length); /* HEARTBLEED! */
    
    free(buffer);
    return 0;
}

int SSL_connect(SSL *ssl)
{
    return 1;
}

int SSL_read(SSL *ssl, void *buf, int num)
{
    return 0;
}

int SSL_write(SSL *ssl, const void *buf, int num)
{
    return num;
}

