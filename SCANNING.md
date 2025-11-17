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

## Quick Start - SBOM Scanning (Recommended for Quick Demos)

The fastest way to demonstrate Snyk's vulnerability detection is using the pre-generated SBOM:

```bash
# Scan the SBOM file (no build required!)
snyk test --file=sbom.json

# Or use the XML format
snyk test --file=sbom.xml
```

**Why use SBOM scanning?**
- ✅ No need to install Conan or build dependencies
- ✅ Fast - results in seconds
- ✅ Perfect for workshops and demos
- ✅ Shows vulnerabilities in OpenSSL (Heartbleed!), zlib, libcurl, etc.

## Scanning Options

### 1. SBOM Scanning (No Build Required)

```bash
# Test SBOM for vulnerabilities
snyk test --file=sbom.json

# Save results to JSON
snyk test --file=sbom.json --json > results.json

# Test with severity threshold
snyk test --file=sbom.json --severity-threshold=high
```

### 2. Conan Dependency Scanning

```bash
# Scan conanfile.txt
snyk test --file=conanfile.txt

# Scan conanfile.py
snyk test --file=conanfile.py

# Monitor for continuous tracking
snyk monitor --file=conanfile.txt
```

### 3. SAST (Static Application Security Testing)

```bash
# Scan C++ source code
snyk code test

# Focus on high severity issues
snyk code test --severity-threshold=high

# Generate detailed report
snyk code test --json > code-results.json
```

### 4. Container Scanning

```bash
# Build the image first
docker build -t goof-cpp:latest .

# Scan the container
snyk container test goof-cpp:latest

# Include Dockerfile scanning
snyk container test goof-cpp:latest --file=Dockerfile
```

### 5. Infrastructure as Code

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

### SBOM / Conan Dependencies (SCA)

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

### Demo 1: Quick SBOM Scan (5 minutes)
```bash
snyk test --file=sbom.json
```
Shows immediate value with no setup required!

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
    - snyk test --file=sbom.json
    - snyk code test
```

## Troubleshooting

### SBOM Scanning Issues

**Q: Getting "No supported projects found"?**
A: Make sure you're using `--file=sbom.json` explicitly:
```bash
snyk test --file=sbom.json
```

**Q: Want to test a specific package?**
A: Use the package URL format:
```bash
snyk test --package-manager=cpp --packages=pkg:conan/openssl@1.0.1t
```

### Conan Scanning Issues

**Q: Conan not found?**
A: Install Conan first:
```bash
pip install conan
```

**Q: Dependencies not resolving?**
A: These are intentionally old versions. Some may not be available in default Conan repositories. Use SBOM scanning instead for demos.

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

