# Simple Makefile for Workshop App Demo - Goof (C++ Edition)
# For quick building without CMake

CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wno-format-security -Wno-deprecated-declarations
LDFLAGS = 
TARGET = goof-server
SRC = server.cpp

# Default target
all: $(TARGET)

# Build the executable
$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRC) $(LDFLAGS)

# Clean build artifacts
clean:
	rm -f $(TARGET) *.o

# Run the application
run: $(TARGET)
	./$(TARGET)

# Create files directory for path traversal demo
setup:
	mkdir -p files
	echo "This is a sample file" > files/sample.txt
	echo "Another test file" > files/test.txt

# Run with address sanitizer (for debugging)
asan: CXXFLAGS += -fsanitize=address -g
asan: clean $(TARGET)

# Run with undefined behavior sanitizer
ubsan: CXXFLAGS += -fsanitize=undefined -g
ubsan: clean $(TARGET)

# Run with memory sanitizer
msan: CXX = clang++
msan: CXXFLAGS += -fsanitize=memory -g
msan: clean $(TARGET)

# Run with thread sanitizer (for race condition detection)
tsan: CXXFLAGS += -fsanitize=thread -g
tsan: clean $(TARGET)

# Install target
install: $(TARGET)
	install -m 755 $(TARGET) /usr/local/bin/

# Uninstall target
uninstall:
	rm -f /usr/local/bin/$(TARGET)

.PHONY: all clean run setup asan ubsan msan tsan install uninstall

