#! /bin/bash
case "$1" in
    "build")
        mkdir -p build; cd build; cmake ..
        ;;
    "clean")
        rm -rf build
        ;;
    "run")
        cd build; make clean; make; ./src/Conway
        ;;
    *)
        mkdir -p build; cd build; cmake ..; make clean; make; ./src/Conway
        ;;
esac