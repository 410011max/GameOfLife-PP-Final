#! /bin/bash
case "$1" in
    "build")
        mkdir -p build
        cd build
        cmake ..
        make
        ;;
    "clean")
        rm -rf build
        ;;
    "run")
        cd build
        ./src/Conway
        ;;
    *)
        echo "Usage: $0 {clean|run|build}"
        ;;
esac

