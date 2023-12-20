#! /bin/bash
case "$1" in
    "build")
        mkdir -p build
        cd build
        cmake ..
        ;;
    "clean")
        rm -rf build
        ;;
    "run")
        cd build
        make clean; make; ./src/Conway
        ;;
    *)
        echo "Usage: $0 {clean|run|build}"
        ;;
esac

