#!/bin/bash

# Function to display help information
show_help() {
    echo "Usage: $0 <cpu_cores> <arch> <repo>"
    echo "Options:"
    echo "  --help	Display this help message"
    echo "  --arch	Display available architectures"
    echo "  --repo  Display available repositories"
}

show_architectures() {
    echo "Available architectures:"
    echo "  linux-arm64"
    echo "  linux-x64"
    echo "  macos-x64"
    echo "  windows-x64"
}

show_repos() {
    echo "Available repositories:"
    echo "  dsw - to use remote repository"
    echo "  local - to use local repository"
}


# Check if --help argument is provided
if [[ "$1" == "--help" ]]; then
    show_help
    exit 0
fi

# Check if --arch argument is provided
if [[ "$1" == "--arch" ]]; then
    show_architectures
    exit 0
fi

# Check if --arch argument is provided
if [[ "$1" == "--repo" ]]; then
    show_repos
    exit 0
fi

# Check if all required arguments are provided
if [ $# -ne 3 ]; then
    echo "Usage: $0 <cpu_cores> <arch> <repo>"
    echo "Usage: $0 4 linux-x64 dsw"
    exit 1
fi



#Available architectures before 1.5.2.2 version
 # - Windows
 # - MacOS
 # - Linux
 # - aarch64
 # - aarch32

 #Available architectures after 
 # - linux-arm64
 # - linux-x64
 # - macos-x64
 # - windows-x64

# Assign command-line arguments to variables
CPU_CORES="$1"
ARCHITECTURE="$2"
REPOSITORY="$3"

# Run docker build command and capture the output
docker build \
	--no-cache \
	--build-arg CPU_CORES=${CPU_CORES} \
	--build-arg REPO=${REPOSITORY} \
	-f ./contrib/docker/Dockerfile.dsw-${ARCHITECTURE}-builder \
	-t decenomy/${REPOSITORY}-${ARCHITECTURE}-builder . > build_output.txt

# Check if docker build was successful
if [ $? -ne 0 ]; then
    echo "Error: Docker build failed."
    exit 1
else
	echo "image created successfully"
fi
