# Vulnerable Dependencies Source Code

This directory contains **actual source code** from intentionally vulnerable versions of popular C/C++ libraries for Snyk Open Source scanning demonstration.

## ⚠️ WARNING

These are **REAL vulnerable libraries** downloaded from official sources. Never use these in production!

## How to Download

Run the download script from the repository root:

```bash
./scripts/download-vulnerable-deps.sh
```

This downloads:
- **OpenSSL 1.0.1t** (4.4 MB) - Contains Heartbleed and 45+ other CVEs
- **zlib 1.2.8** (557 KB) - Contains 4 critical CVEs  
- **libcurl 7.58.0** (3.8 MB) - Contains 88+ vulnerabilities including RCE

Total download size: ~8.8 MB

## Included Vulnerable Libraries

### OpenSSL 1.0.1t
**Location**: `openssl-1.0.1t/`  
**Source**: https://www.openssl.org/source/old/1.0.1/  
**Critical CVEs**:
- CVE-2014-0160 (Heartbleed) - Memory disclosure vulnerability
- CVE-2016-2105 - Integer overflow
- CVE-2016-2106 - Integer overflow  
- CVE-2016-2107 - Padding oracle
- CVE-2016-2108 - Memory corruption in ASN.1 encoder
- And 40+ more vulnerabilities

**Snyk Detected**: 45+ vulnerabilities (17 Critical, 18 High, 8 Medium, 2 Low)

### zlib 1.2.8
**Location**: `zlib-1.2.8/`  
**Source**: https://www.zlib.net/fossils/  
**Critical CVEs**:
- CVE-2016-9840 - Out-of-bounds pointer arithmetic in inftrees.c
- CVE-2016-9841 - Out-of-bounds pointer arithmetic in inffast.c
- CVE-2016-9842 - Undefined left shift of negative number
- CVE-2016-9843 - Big shift exponents

**Snyk Detected**: 6 vulnerabilities (2 Critical, 3 High, 1 Medium)

### libcurl 7.58.0
**Location**: `curl-7.58.0/`  
**Source**: https://github.com/curl/curl/releases/  
**Critical CVEs**:
- CVE-2018-1000120 - FTP path trickery leads to NIL byte out of bounds write
- CVE-2018-1000121 - LDAP NULL pointer dereference
- CVE-2018-1000122 - RTSP RTP buffer over-read
- And 85+ more vulnerabilities

**Snyk Detected**: 88+ vulnerabilities (11 Critical, 13 High, 44 Medium, 7 Low)

## How Snyk Scanning Works

According to the [Snyk C/C++ troubleshooting documentation](https://docs.snyk.io/supported-languages/supported-languages-list/c-c++/troubleshooting-c-c++-for-open-source):

1. **Scans source code files** - Collects `.c`, `.cpp`, `.h`, `.hpp` files from deps/ directory
2. **Creates file hashes** - Converts files to hashes (your code is NOT sent to Snyk servers)
3. **Matches against database** - Compares hashes to known vulnerable library versions
4. **Reports CVEs** - Shows all vulnerabilities found in the matched libraries

## How to Scan

From the repository root, run:

```bash
# Scan all dependencies in the deps/ directory
snyk test --unmanaged

# Scan with severity threshold
snyk test --unmanaged --severity-threshold=high

# Generate JSON report
snyk test --unmanaged --json > scan-results.json
```

## Expected Results

When you run `snyk test --unmanaged`, Snyk should detect:

✅ **133 total vulnerabilities** across the three libraries:
- 17 Critical severity issues
- 36 High severity issues
- 69 Medium severity issues
- 11 Low severity issues

## Troubleshooting

### "Why did Snyk not find any dependencies?"

If Snyk doesn't detect these libraries, check:

1. **Source code present**: Make sure the actual library files are extracted in `deps/`
2. **Run the download script**: Use `./scripts/download-vulnerable-deps.sh`
3. **Scan from repo root**: Make sure you're in the repository root directory
4. **Recent Snyk database**: The Snyk database updates twice monthly

### Re-downloading Libraries

If you need to re-download the libraries:

```bash
cd deps
rm -rf openssl-* zlib-* curl-*
cd ..
./scripts/download-vulnerable-deps.sh
```

## Privacy

🔒 **Your source code is not sent to Snyk servers**. Only file hashes are transmitted for matching against the vulnerability database. See the [Snyk C/C++ troubleshooting docs](https://docs.snyk.io/supported-languages/supported-languages-list/c-c++/troubleshooting-c-c++-for-open-source) for details.

## Why Not Use Package Managers?

Snyk C/C++ scanning is different from other languages:
- ❌ Does NOT scan `conanfile.txt`, `CMakeLists.txt`, or `vcpkg.json`
- ❌ Does NOT work with SBOM files directly for C/C++
- ✅ DOES scan actual `.c`, `.cpp`, `.h`, `.hpp` source files
- ✅ DOES work with the `--unmanaged` flag

This approach works because C/C++ dependencies are often included as source code in projects, unlike other languages that use centralized package repositories.

## File Structure

```
deps/
├── openssl-1.0.1t/     # OpenSSL source code (~4.4 MB)
│   ├── crypto/         # Cryptographic functions
│   ├── ssl/            # SSL/TLS implementation  
│   ├── apps/           # OpenSSL applications
│   └── include/        # Header files
├── zlib-1.2.8/         # zlib source code (~557 KB)
│   ├── *.c             # Implementation files
│   └── *.h             # Header files
└── curl-7.58.0/        # libcurl source code (~3.8 MB)
    ├── lib/            # Library implementation
    ├── include/        # Public headers
    └── src/            # curl tool source
```

## Additional Resources

- [Snyk C/C++ Support Documentation](https://docs.snyk.io/supported-languages/supported-languages-list/c-c++)
- [Snyk C/C++ Troubleshooting Guide](https://docs.snyk.io/supported-languages/supported-languages-list/c-c++/troubleshooting-c-c++-for-open-source)
- [OpenSSL Security Advisories](https://www.openssl.org/news/secadv_20160503.txt)
- [zlib Security Advisories](https://www.cvedetails.com/vulnerability-list/vendor_id-72/product_id-1820/GNU-Zlib.html)
- [curl Security Advisories](https://curl.se/docs/security.html)

---

**Remember**: These are intentionally vulnerable libraries for training purposes only. Never use them in production!

