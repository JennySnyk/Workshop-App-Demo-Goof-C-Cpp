/*
 * Workshop App Demo - Goof (C++ Edition)
 * 
 * This is a DELIBERATELY VULNERABLE application for security training purposes.
 * DO NOT use in production environments.
 * 
 * This application demonstrates various OWASP Top 10 vulnerabilities in C++
 */

#include <iostream>
#include <cstring>
#include <cstdlib>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <memory>

// Simulated database
std::map<int, std::string> userDatabase = {
    {1, "Alice"},
    {2, "Bob"},
    {3, "Charlie"}
};

// ============================================================================
// VULNERABILITY 1: Buffer Overflow (CWE-120)
// ============================================================================
void bufferOverflowVulnerability(const char* input) {
    char buffer[64];
    // VULNERABLE: No bounds checking
    strcpy(buffer, input);
    std::cout << "Processed: " << buffer << std::endl;
}

// ============================================================================
// VULNERABILITY 2: Format String Vulnerability (CWE-134)
// ============================================================================
void formatStringVulnerability(const char* userInput) {
    // VULNERABLE: User input directly in format string
    printf(userInput);
    printf("\n");
}

// ============================================================================
// VULNERABILITY 3: SQL Injection (Simulated) (CWE-89)
// ============================================================================
std::string sqlInjectionVulnerability(const std::string& userId) {
    // VULNERABLE: Direct string concatenation in SQL query
    std::string query = "SELECT * FROM users WHERE id = " + userId;
    std::cout << "Executing query: " << query << std::endl;
    
    // Simulated database lookup
    try {
        int id = std::stoi(userId);
        if (userDatabase.find(id) != userDatabase.end()) {
            return userDatabase[id];
        }
    } catch (...) {
        return "Error or injection detected: " + query;
    }
    return "User not found";
}

// ============================================================================
// VULNERABILITY 4: Command Injection (CWE-78)
// ============================================================================
void commandInjectionVulnerability(const std::string& host) {
    // VULNERABLE: Executing system command with user input
    std::string command = "ping -c 1 " + host;
    std::cout << "Executing: " << command << std::endl;
    system(command.c_str());
}

// ============================================================================
// VULNERABILITY 5: Path Traversal (CWE-22)
// ============================================================================
std::string pathTraversalVulnerability(const std::string& filename) {
    // VULNERABLE: No path sanitization
    std::string filepath = "./files/" + filename;
    std::ifstream file(filepath);
    
    if (file.is_open()) {
        std::stringstream buffer;
        buffer << file.rdbuf();
        return buffer.str();
    }
    return "File not found: " + filepath;
}

// ============================================================================
// VULNERABILITY 6: Use After Free (CWE-416)
// ============================================================================
void useAfterFreeVulnerability() {
    int* ptr = new int(42);
    std::cout << "Value: " << *ptr << std::endl;
    
    // VULNERABLE: Freeing memory
    delete ptr;
    
    // VULNERABLE: Using freed memory
    std::cout << "Value after free: " << *ptr << std::endl;
    
    // VULNERABLE: Double free possibility
    delete ptr;
}

// ============================================================================
// VULNERABILITY 7: Integer Overflow (CWE-190)
// ============================================================================
void integerOverflowVulnerability(int size) {
    // VULNERABLE: No overflow checking
    int bufferSize = size + 100;
    
    if (bufferSize > 0) {
        char* buffer = new char[bufferSize];
        std::cout << "Allocated buffer of size: " << bufferSize << std::endl;
        delete[] buffer;
    }
}

// ============================================================================
// VULNERABILITY 8: Null Pointer Dereference (CWE-476)
// ============================================================================
void nullPointerDereferenceVulnerability(bool allocate) {
    int* ptr = nullptr;
    
    if (allocate) {
        ptr = new int(100);
    }
    
    // VULNERABLE: No null check before dereference
    std::cout << "Value: " << *ptr << std::endl;
    
    if (ptr) {
        delete ptr;
    }
}

// ============================================================================
// VULNERABILITY 9: Memory Leak (CWE-401)
// ============================================================================
void memoryLeakVulnerability() {
    for (int i = 0; i < 1000; i++) {
        // VULNERABLE: Memory allocated but never freed
        int* leak = new int[1000];
        leak[0] = i;
    }
}

// ============================================================================
// VULNERABILITY 10: Hardcoded Credentials (CWE-798)
// ============================================================================
bool hardcodedCredentialsVulnerability(const std::string& username, const std::string& password) {
    // VULNERABLE: Hardcoded credentials
    const char* ADMIN_USERNAME = "admin";
    const char* ADMIN_PASSWORD = "password123";
    
    if (username == ADMIN_USERNAME && password == ADMIN_PASSWORD) {
        std::cout << "Login successful!" << std::endl;
        return true;
    }
    return false;
}

// ============================================================================
// VULNERABILITY 11: Insecure Randomness (CWE-330)
// ============================================================================
int insecureRandomnessVulnerability() {
    // VULNERABLE: Using rand() for security-sensitive operation
    return rand() % 1000000;
}

// ============================================================================
// VULNERABILITY 12: Race Condition (CWE-race)
// ============================================================================
int globalCounter = 0;

void raceConditionVulnerability() {
    // VULNERABLE: Unsynchronized access to shared resource
    for (int i = 0; i < 1000; i++) {
        globalCounter++;
    }
}

// ============================================================================
// Main Menu
// ============================================================================
void printMenu() {
    std::cout << "\n=== Workshop App Demo - Goof (C++ Edition) ===" << std::endl;
    std::cout << "=== DELIBERATELY VULNERABLE - FOR TRAINING ONLY ===" << std::endl;
    std::cout << "\nSelect a vulnerability to demonstrate:\n" << std::endl;
    std::cout << "1.  Buffer Overflow" << std::endl;
    std::cout << "2.  Format String Vulnerability" << std::endl;
    std::cout << "3.  SQL Injection (Simulated)" << std::endl;
    std::cout << "4.  Command Injection" << std::endl;
    std::cout << "5.  Path Traversal" << std::endl;
    std::cout << "6.  Use After Free" << std::endl;
    std::cout << "7.  Integer Overflow" << std::endl;
    std::cout << "8.  Null Pointer Dereference" << std::endl;
    std::cout << "9.  Memory Leak" << std::endl;
    std::cout << "10. Hardcoded Credentials" << std::endl;
    std::cout << "11. Insecure Randomness" << std::endl;
    std::cout << "12. Race Condition" << std::endl;
    std::cout << "0.  Exit" << std::endl;
    std::cout << "\nChoice: ";
}

int main() {
    std::cout << "Starting vulnerable application..." << std::endl;
    std::cout << "WARNING: This application contains intentional security flaws!" << std::endl;
    
    while (true) {
        printMenu();
        
        int choice;
        std::cin >> choice;
        std::cin.ignore(); // Clear newline
        
        try {
            switch (choice) {
                case 0:
                    std::cout << "Exiting..." << std::endl;
                    return 0;
                    
                case 1: {
                    std::cout << "Enter text (try a long string): ";
                    std::string input;
                    std::getline(std::cin, input);
                    bufferOverflowVulnerability(input.c_str());
                    break;
                }
                
                case 2: {
                    std::cout << "Enter format string (try %x %x %x): ";
                    char input[256];
                    std::cin.getline(input, 256);
                    formatStringVulnerability(input);
                    break;
                }
                
                case 3: {
                    std::cout << "Enter user ID (try: 1 OR 1=1): ";
                    std::string userId;
                    std::getline(std::cin, userId);
                    std::string result = sqlInjectionVulnerability(userId);
                    std::cout << "Result: " << result << std::endl;
                    break;
                }
                
                case 4: {
                    std::cout << "Enter host to ping (try: 8.8.8.8; ls): ";
                    std::string host;
                    std::getline(std::cin, host);
                    commandInjectionVulnerability(host);
                    break;
                }
                
                case 5: {
                    std::cout << "Enter filename (try: ../../../../etc/passwd): ";
                    std::string filename;
                    std::getline(std::cin, filename);
                    std::string content = pathTraversalVulnerability(filename);
                    std::cout << "File content:\n" << content << std::endl;
                    break;
                }
                
                case 6: {
                    std::cout << "Demonstrating use-after-free..." << std::endl;
                    useAfterFreeVulnerability();
                    break;
                }
                
                case 7: {
                    std::cout << "Enter size (try: 2147483647): ";
                    int size;
                    std::cin >> size;
                    integerOverflowVulnerability(size);
                    break;
                }
                
                case 8: {
                    std::cout << "Allocate memory? (1=yes, 0=no): ";
                    int allocate;
                    std::cin >> allocate;
                    nullPointerDereferenceVulnerability(allocate == 1);
                    break;
                }
                
                case 9: {
                    std::cout << "Creating memory leaks..." << std::endl;
                    memoryLeakVulnerability();
                    std::cout << "Memory leaked!" << std::endl;
                    break;
                }
                
                case 10: {
                    std::cout << "Enter username: ";
                    std::string username;
                    std::getline(std::cin, username);
                    std::cout << "Enter password: ";
                    std::string password;
                    std::getline(std::cin, password);
                    bool success = hardcodedCredentialsVulnerability(username, password);
                    if (!success) {
                        std::cout << "Login failed!" << std::endl;
                    }
                    break;
                }
                
                case 11: {
                    std::cout << "Generating insecure random token..." << std::endl;
                    int token = insecureRandomnessVulnerability();
                    std::cout << "Token: " << token << std::endl;
                    break;
                }
                
                case 12: {
                    std::cout << "Demonstrating race condition..." << std::endl;
                    raceConditionVulnerability();
                    std::cout << "Counter value: " << globalCounter << std::endl;
                    break;
                }
                
                default:
                    std::cout << "Invalid choice!" << std::endl;
            }
        } catch (const std::exception& e) {
            std::cout << "Exception: " << e.what() << std::endl;
        }
    }
    
    return 0;
}

