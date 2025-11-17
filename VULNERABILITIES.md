# Known Vulnerabilities in This Repository

This document lists the intentional vulnerabilities included in this demonstration repository.

## 🔴 Open Source Dependencies (SCA)

The following vulnerable dependencies are included in `conanfile.txt` and `conanfile.py`:

### OpenSSL 1.0.1t
**Severity**: 🔴 Critical

Known CVEs:
- **CVE-2014-0160** (Heartbleed) - CVSS 7.5 - Information disclosure vulnerability
- **CVE-2016-2105** - Integer overflow
- **CVE-2016-2106** - Integer overflow
- **CVE-2016-2107** - Padding oracle
- **CVE-2016-2108** - Memory corruption in ASN.1 encoder
- **CVE-2016-2109** - ASN.1 BIO excessive memory allocation
- **CVE-2016-2177** - Pointer arithmetic undefined behaviour
- **CVE-2016-2178** - Constant time flag not preserved in DSA signing

### zlib 1.2.8
**Severity**: 🔴 Critical

Known CVEs:
- **CVE-2016-9840** - Out-of-bounds pointer arithmetic in inftrees.c
- **CVE-2016-9841** - Out-of-bounds pointer arithmetic in inffast.c
- **CVE-2016-9842** - Undefined left shift of negative number
- **CVE-2016-9843** - Big shift exponents in inflate.c and inffast.c

### libcurl 7.58.0
**Severity**: 🔴 High

Known CVEs:
- **CVE-2018-1000120** - FTP path trickery leads to NIL byte out of bounds write
- **CVE-2018-1000121** - LDAP NULL pointer dereference
- **CVE-2018-1000122** - RTSP RTP buffer over-read
- **CVE-2018-1000301** - RTSP bad headers buffer over-read

### Boost 1.69.0
**Severity**: 🟠 Medium

Known issues:
- Various memory safety issues
- Potential buffer overflow vulnerabilities
- Integer overflow in specific modules

### SQLite 3.16.0
**Severity**: 🟠 High

Known CVEs:
- **CVE-2017-10989** - Heap-based buffer overflow
- **CVE-2017-13685** - Stack-based buffer overflow
- Multiple memory corruption issues

### libxml2 2.9.4
**Severity**: 🔴 High

Known CVEs:
- **CVE-2017-5969** - Null pointer dereference
- **CVE-2017-9047** - Buffer overflow
- **CVE-2017-9048** - Stack-based buffer overflow
- **CVE-2017-9049** - Heap-based buffer overflow
- **CVE-2017-9050** - Heap-based buffer over-read
- XXE (XML External Entity) vulnerabilities

### JsonCpp 1.8.4
**Severity**: 🟡 Medium

Known issues:
- Potential denial of service issues
- Memory handling issues

## 🔴 SAST Vulnerabilities (Code Analysis)

The `server.cpp` file contains 12 intentional SAST vulnerabilities:

1. **Buffer Overflow** (CWE-120) - Line ~27
2. **Format String Vulnerability** (CWE-134) - Line ~37
3. **SQL Injection** (CWE-89) - Line ~47
4. **Command Injection** (CWE-78) - Line ~64
5. **Path Traversal** (CWE-22) - Line ~74
6. **Use After Free** (CWE-416) - Line ~87
7. **Integer Overflow** (CWE-190) - Line ~102
8. **Null Pointer Dereference** (CWE-476) - Line ~115
9. **Memory Leak** (CWE-401) - Line ~130
10. **Hardcoded Credentials** (CWE-798) - Line ~141
11. **Insecure Randomness** (CWE-330) - Line ~154
12. **Race Condition** (CWE-362) - Line ~162

## 🔴 Container Vulnerabilities

### Dockerfile (Ubuntu 18.04)
- Vulnerable base image (Ubuntu 18.04 EOL)
- Running as root user
- Hardcoded passwords
- Exposing unnecessary ports (22, 3306, 8080)
- No healthcheck
- Missing security updates

### Dockerfile.alpine (Alpine 3.12)
- Older Alpine version with known vulnerabilities
- Running as root
- Environment variables with hardcoded secrets
- Multiple exposed ports

## 🔴 Infrastructure as Code (Terraform)

### terraform/main.tf
- Public S3 buckets (public-read ACL)
- Unencrypted S3 buckets
- S3 versioning disabled
- Security groups open to 0.0.0.0/0
- SSH (port 22) open to internet
- MySQL (port 3306) open to internet
- EC2 instance with unencrypted root volume
- IMDSv1 enabled (should use IMDSv2)
- RDS publicly accessible
- RDS unencrypted
- RDS with weak password in code
- Hardcoded credentials in user_data
- No backup retention
- No deletion protection

## How to Scan

### Snyk Code (SAST)
```bash
snyk code test
```

### Snyk Open Source (SCA)
```bash
# Scan C/C++ dependencies using unmanaged scanning
snyk test --unmanaged

# Scan specific directory
snyk test --unmanaged --target-dir=deps/
```

**Note**: C/C++ scanning uses the `--unmanaged` flag to scan actual source code files in the `deps/` directory. It does NOT use package manager files like `conanfile.txt` or SBOM files.

### Snyk Container
```bash
docker build -t goof-cpp:latest .
snyk container test goof-cpp:latest --file=Dockerfile
```

### Snyk IaC
```bash
snyk iac test terraform/
```

## Important Notes

⚠️ **WARNING**: All vulnerabilities in this repository are **INTENTIONAL** for educational purposes.

- **DO NOT** use any of these dependency versions in production
- **DO NOT** deploy this code in production environments
- **DO NOT** expose this application to public networks
- **USE ONLY** in isolated, controlled environments for training

## References

- [OWASP Top 10](https://owasp.org/www-project-top-ten/)
- [CWE Top 25](https://cwe.mitre.org/top25/)
- [Snyk Vulnerability Database](https://security.snyk.io/)
- [CVE Database](https://cve.mitre.org/)
- [National Vulnerability Database](https://nvd.nist.gov/)

