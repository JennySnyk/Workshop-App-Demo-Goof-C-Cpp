# Snyk Scanning Guide for C++ Goof Repository

This guide shows you how to scan the vulnerable C++ application with Snyk.

## Prerequisites

```bash
# Install Snyk CLI
npm install -g snyk
# or
brew install snyk

# Authenticate with Snyk
snyk auth
```

## Quick Start - Unmanaged C/C++ Scanning (Recommended for Demos)

The correct way to scan C/C++ dependencies with Snyk is using the `--unmanaged` flag:

```bash
# Scan C/C++ dependencies (scans source files in deps/ directory)
snyk test --unmanaged
```

**Why use --unmanaged for C/C++?**
- ✅ Correct method for C/C++ dependency scanning
- ✅ Scans actual source code files (`.c`, `.cpp`, `.h`)
- ✅ No need to build - just scans source files
- ✅ Detects vulnerabilities in OpenSSL (Heartbleed!), zlib, libcurl, etc.
- ✅ Privacy-focused: Only file hashes sent to Snyk (not source code)

## Scanning Options

### 1. Unmanaged C/C++ Scanning (Correct Method)

```bash
# Scan C/C++ dependencies
snyk test --unmanaged

# Scan specific directory
snyk test --unmanaged --target-dir=deps/

# Save results to JSON
snyk test --unmanaged --json > results.json

# Test with severity threshold
snyk test --unmanaged --severity-threshold=high

# Monitor for continuous tracking
snyk monitor --unmanaged
```

**How it works**: 
- Scans `.c`, `.cpp`, `.h`, `.hpp` files in the current directory and subdirectories
- Converts files to hashes (privacy-focused - only hashes sent to Snyk)
- Matches hashes against Snyk's vulnerability database
- Reports CVEs found in matched library versions

**Note**: C/C++ scanning does NOT use package manager files like `conanfile.txt` or SBOM files. It scans actual source code.

### 2. SAST (Static Application Security Testing)

```bash
# Scan C++ source code
snyk code test

# Focus on high severity issues
snyk code test --severity-threshold=high

# Generate detailed report
snyk code test --json > code-results.json
```

### 3. Container Scanning

```bash
# Build the image first
docker build -t goof-cpp:latest .

# Scan the container
snyk container test goof-cpp:latest

# Include Dockerfile scanning
snyk container test goof-cpp:latest --file=Dockerfile
```

### 4. Infrastructure as Code

```bash
# Scan Terraform files
snyk iac test terraform/

# JSON output
snyk iac test terraform/ --json > iac-results.json
```

## Complete Scan (All Types)

Use the provided script to run all scans:

```bash
./scripts/scan-with-snyk.sh
```

This will:
1. Run Snyk Code (SAST)
2. Scan SBOM and Conan files (SCA)
3. Build and scan Docker container
4. Scan Terraform infrastructure

Results are saved to `scan-results/` directory.

## Expected Findings

### C/C++ Dependencies (Unmanaged Scanning)

| Package | Version | Critical CVEs |
|---------|---------|---------------|
| OpenSSL | 1.0.1t | CVE-2014-0160 (Heartbleed), CVE-2016-2105, CVE-2016-2106 |
| zlib | 1.2.8 | CVE-2016-9840, CVE-2016-9841, CVE-2016-9842, CVE-2016-9843 |
| libcurl | 7.58.0 | CVE-2018-1000120, CVE-2018-1000121 |
| SQLite | 3.16.0 | Multiple CVEs |
| libxml2 | 2.9.4 | XXE vulnerabilities |

### Source Code (SAST)

- Buffer Overflow (CWE-120)
- Format String Vulnerability (CWE-134)
- SQL Injection (CWE-89)
- Command Injection (CWE-78)
- Path Traversal (CWE-22)
- Use After Free (CWE-416)
- Integer Overflow (CWE-190)
- Null Pointer Dereference (CWE-476)
- Memory Leak (CWE-401)
- Hardcoded Credentials (CWE-798)
- And more...

### Container

- Vulnerable Ubuntu 18.04 base image
- Running as root user
- Exposed unnecessary ports
- Hardcoded secrets
- No security best practices

### Infrastructure as Code

- Public S3 buckets
- Overly permissive security groups (0.0.0.0/0)
- Unencrypted storage
- Publicly accessible databases
- IMDSv1 enabled

## Tips for Workshops

### Demo 1: Quick Unmanaged Scan (5 minutes)
```bash
snyk test --unmanaged
```
Shows C/C++ vulnerability detection with no build required!

### Demo 2: SAST Code Analysis (10 minutes)
```bash
snyk code test
```
Demonstrates 12 different vulnerability types in C++ code.

### Demo 3: Multi-Layer Security (20 minutes)
```bash
./scripts/scan-with-snyk.sh
```
Shows comprehensive security scanning across all layers.

## Integration with CI/CD

### GitHub Actions

The repository includes `.github/workflows/snyk-security.yml` which automatically:
- Scans code on push/PR
- Tests dependencies
- Checks containers
- Validates IaC

### Jenkins

```groovy
stage('Snyk Security') {
    steps {
        sh 'snyk test --file=sbom.json'
        sh 'snyk code test'
    }
}
```

### GitLab CI

```yaml
snyk_scan:
  script:
    - snyk test --unmanaged
    - snyk code test
```

## Troubleshooting

### Unmanaged Scanning Issues

**Q: Getting "Could not detect package manager" error?**
A: For C/C++, don't use `--file=conanfile.txt`. Use `--unmanaged` instead:
```bash
snyk test --unmanaged
```

**Q: "Why did Snyk not find any dependencies?"**
A: According to the [Snyk C/C++ troubleshooting guide](https://docs.snyk.io/supported-languages/supported-languages-list/c-c++/troubleshooting-c-c++-for-open-source), check:
1. Source code files (`.c`, `.cpp`, `.h`) are present in the `deps/` directory
2. Files match official release patterns from open source components
3. Sufficient number of files are present for Snyk to recognize the library
4. The Snyk database has been recently updated (updates twice monthly)

**Q: Want to scan only a specific directory?**
A: Use the `--target-dir` option:
```bash
snyk test --unmanaged --target-dir=deps/openssl-1.0.1t/
```

**Q: Is my source code sent to Snyk?**
A: No! Only file hashes are sent to Snyk servers, not the actual source code. See the [troubleshooting documentation](https://docs.snyk.io/supported-languages/supported-languages-list/c-c++/troubleshooting-c-c++-for-open-source) for details.

## Documentation References

- [Snyk C/C++ Support](https://docs.snyk.io/supported-languages/supported-languages-list/c-c++)
- [SBOM Testing](https://docs.snyk.io/scan-with-snyk/snyk-open-source/scan-open-source-libraries-and-licenses/test-an-sbom-document-for-vulnerabilities)
- [Snyk CLI Commands](https://docs.snyk.io/snyk-cli/commands)

## Support

For issues with this demo repository, check:
1. `README.md` - Main documentation
2. `VULNERABILITIES.md` - Vulnerability reference
3. `SECURITY.md` - Security policy

---

**⚠️ REMINDER**: This is a deliberately vulnerable application for training purposes only. Never deploy in production!

