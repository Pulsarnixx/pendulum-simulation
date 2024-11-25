#!/bin/bash

#Check arguments number
if [ $# -ne 1 ]; then
    echo "Please provide 1 argument!"
    exit 1
fi

#Check option
OPTION=$1
BUIlD_FOLDER="build"

if [ ${OPTION} == "config" ]; then

    if [ ! -d ${BUIlD_FOLDER} ]; then
        mkdir ${BUIlD_FOLDER}
    fi

    cd ${BUIlD_FOLDER}
    cmake ..
    cd ..

elif [ ${OPTION} == "build" ]; then

    cd ${BUIlD_FOLDER}
    cmake --build . -j
    cd ..

elif [ ${OPTION} == "clean" ]; then

    if [ -d ${BUIlD_FOLDER} ]; then
        rm -r build
        rm -r bin
    else
        echo "Build folder doesn't exist"
    fi

elif [ ${OPTION} == "fresh" ]; then

    if [ -d ${BUIlD_FOLDER} ]; then
        rm -r build
        rm -r bin
    fi

    mkdir ${BUIlD_FOLDER}
    cd ${BUIlD_FOLDER}
    cmake ..
    cmake --build . -j
    cd ..

elif [ ${OPTION} == "run" ]; then

    if [ -d ${BUIlD_FOLDER} ]; then
        rm -r build
        rm -r bin
    fi

    mkdir ${BUIlD_FOLDER}
    cd ${BUIlD_FOLDER}
    cmake ..
    cmake --build . -j
    cd ..

    ./bin/App/Simulation

else 
    echo "Wrong option!"
    exit 1
fi

exit 0 