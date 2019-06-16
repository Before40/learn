#!/bin/bash

workdir=$(pwd)
if [ ! -d build ];then
   mkdir build
fi

if [ -d build ];then
    cd build
    cmake -DCMAKE_TOOLCHAIN_FILE=../clang.cmake .. && make    
else
   echo "not existed build directory."
   exit 0
fi
