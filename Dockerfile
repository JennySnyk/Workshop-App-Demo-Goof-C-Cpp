# Deliberately using an OLD and VULNERABLE base image for demonstration
# DO NOT USE IN PRODUCTION
FROM ubuntu:18.04

# Vulnerable: Running as root
USER root

# Install build dependencies and vulnerable packages
RUN apt-get update && apt-get install -y \
    g++ \
    cmake \
    make \
    libssl-dev \
    libcurl4-openssl-dev \
    && rm -rf /var/lib/apt/lists/*

# Vulnerable: Setting a weak password
RUN useradd -m appuser && echo "appuser:password123" | chpasswd

# Copy application files
WORKDIR /app
COPY . /app

# Build the application
RUN mkdir -p build && cd build && \
    cmake .. && \
    make

# Vulnerable: Exposing unnecessary ports
EXPOSE 8080 22 3306

# Vulnerable: Running as root instead of non-privileged user
# Should be: USER appuser

# Vulnerable: No healthcheck defined
# HEALTHCHECK --interval=30s --timeout=3s CMD curl -f http://localhost:8080/ || exit 1

# Run the application
CMD ["./build/goof-server"]

