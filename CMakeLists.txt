cmake_minimum_required(VERSION 3.10)
project(WorkshopAppDemoGoof CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Main executable
add_executable(goof-server server.cpp)

# For demonstration purposes, we're using older versions of libraries
# that may have known vulnerabilities (for SCA scanning)

# Example: Using OpenSSL (you would typically find vulnerable versions)
find_package(OpenSSL)
if(OPENSSL_FOUND)
    target_include_directories(goof-server PRIVATE ${OPENSSL_INCLUDE_DIR})
    target_link_libraries(goof-server ${OPENSSL_LIBRARIES})
endif()

# Example: Using libcurl (you would typically specify older vulnerable versions)
find_package(CURL)
if(CURL_FOUND)
    target_include_directories(goof-server PRIVATE ${CURL_INCLUDE_DIRS})
    target_link_libraries(goof-server ${CURL_LIBRARIES})
endif()

# Compile with flags that demonstrate security issues
# Note: In production, you would want -Wall -Wextra -Werror
target_compile_options(goof-server PRIVATE
    -Wno-deprecated-declarations
    -Wno-format-security
    -Wno-unused-variable
)

# Installation
install(TARGETS goof-server DESTINATION bin)

# Add a custom target to create the files directory
add_custom_command(TARGET goof-server POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E make_directory
    ${CMAKE_CURRENT_BINARY_DIR}/files
)

