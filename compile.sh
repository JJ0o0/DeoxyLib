#!/bin/bash

config=$1
final_config="Debug"

clear
if [ "$config" == "Debug" ] || [ "$config" == "d" ]; then
    echo "Compiling in Debug mode"
elif [ "$config" == "Release" ] || [ "$config" == "r" ]; then
    echo "Compiling in Release mode"
    final_config="Release"
else
    echo "No compile mode specified"
    echo "Compiling in Debug mode"
fi

cmake --build build --config $final_config