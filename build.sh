#!/bin/bash

cd lab1/
# проверить есть ли build

folder="$(pwd)/build/"

if [ -e "$folder" ]
then
        echo "build have alredy existed"
else
        mkdir build
fi

cd build
cmake ..
make
./lab1
