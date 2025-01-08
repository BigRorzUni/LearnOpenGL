#!/bin/bash

# Define the build directory
BUILD_DIR="build"

# Define the executable name
EXECUTABLE="Renderer"

run() {
    cd "$BUILD_DIR" || exit
    make
    cd - || exit
    
    ./"$BUILD_DIR"/"$EXECUTABLE"
}

# Function to create build directory and run cmake and make
build() {
    mkdir -p "$BUILD_DIR"
    cd "$BUILD_DIR" || exit
    cmake ..
    make
    cd - || exit
}

# Function to clean the build directory
clean() {
    rm -rf "$BUILD_DIR"
}

# Parse command line arguments
case "$1" in
    build)
        build
        ;;
    run)
        run
        ;;
    clean)
        clean
        ;;
    *)
        if [ -z "$1" ]; then
            build
            run
        else
            echo "Usage: $0 {build|run|clean}"
            echo "No argument will build and run the executable"
            exit 1
        fi
        ;;
esac