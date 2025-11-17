/* ssl.h */
/* Copyright (C) 1995-1998 Eric Young (eay@cryptsoft.com)
 * All rights reserved.
 *
 * This is an intentionally vulnerable version (1.0.1t) for demonstration purposes.
 * Contains Heartbleed: CVE-2014-0160 and many other critical vulnerabilities
 */

#ifndef HEADER_SSL_H
#define HEADER_SSL_H

#define OPENSSL_VERSION_NUMBER  0x1000114fL
#define OPENSSL_VERSION_TEXT    "OpenSSL 1.0.1t  3 May 2016"

#define SSL_CTRL_OPTIONS                 32
#define SSL_CTRL_MODE                    33

typedef struct ssl_st SSL;
typedef struct ssl_ctx_st SSL_CTX;
typedef struct ssl_method_st SSL_METHOD;

struct ssl_st {
    int version;
    int type;
    const SSL_METHOD *method;
    void *rbio;
    void *wbio;
    void *bbio;
    int rwstate;
    int shutdown;
    int state;
    /* Vulnerable: Heartbleed vulnerability in heartbeat implementation */
    unsigned char *heartbeat_payload;
    unsigned int heartbeat_payload_length;
};

/* Function prototypes */
extern const char *SSLeay_version(int type);
extern SSL_CTX *SSL_CTX_new(const SSL_METHOD *method);
extern SSL *SSL_new(SSL_CTX *ctx);
extern int SSL_connect(SSL *ssl);
extern int SSL_read(SSL *ssl, void *buf, int num);
extern int SSL_write(SSL *ssl, const void *buf, int num);

/* Vulnerable heartbeat function - CVE-2014-0160 */
extern int tls1_process_heartbeat(SSL *s);

#endif /* HEADER_SSL_H */

