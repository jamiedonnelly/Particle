# latest ubuntu image 
FROM ubuntu:latest 

# Update the package list and install basic utilities and C++ dev tools
RUN apt-get update && apt-get install -y \
    build-essential \      # Basic compilation utilities (gcc, g++, make)
    git \                  # Git for version control
    vim \                  # Vim editor
    && apt-get clean \     # Clean up cached files to reduce layer size
    && rm -rf /var/lib/apt/lists/* /tmp/* /var/tmp/*