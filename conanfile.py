from conan import ConanFile

class GoofCppConan(ConanFile):
    """
    Workshop App Demo - Goof (C++ Edition)
    Deliberately using VULNERABLE dependency versions for security demonstration
    DO NOT use in production!
    """
    
    name = "goof-cpp"
    version = "1.0.0"
    settings = "os", "compiler", "build_type", "arch"
    
    # Intentionally vulnerable dependencies with known CVEs
    requires = (
        # OpenSSL 1.0.1t - Contains Heartbleed (CVE-2014-0160) and multiple other critical CVEs
        "openssl/1.0.1t",
        
        # zlib 1.2.8 - CVE-2016-9840, CVE-2016-9841, CVE-2016-9842, CVE-2016-9843
        "zlib/1.2.8",
        
        # libcurl 7.58.0 - Multiple security vulnerabilities
        "libcurl/7.58.0",
        
        # Boost 1.69.0 - Known vulnerabilities
        "boost/1.69.0",
        
        # SQLite 3.16.0 - Multiple CVEs
        "sqlite3/3.16.0",
        
        # libxml2 2.9.4 - Multiple CVEs including XXE vulnerabilities
        "libxml2/2.9.4",
        
        # JsonCpp 1.8.4 - Older version with potential issues
        "jsoncpp/1.8.4"
    )
    
    generators = "cmake", "cmake_find_package"
    
    def configure(self):
        # Configure package options
        self.options["openssl"].shared = False
        self.options["libcurl"].shared = False
        self.options["boost"].shared = False
        self.options["sqlite3"].shared = False
        self.options["libxml2"].shared = False

