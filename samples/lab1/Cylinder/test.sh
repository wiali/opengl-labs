#!/bin/bash

CYLINDER=bin/cylinder

TESTS[0]="--help"                               # print help information
TESTS[1]="--height 100 --radius 50"             # long argument names
TESTS[2]="-h 100 -r 50"                         # abbreviated argument names
TESTS[3]="--height 0x64 -r 0x32"                # hexadecimal input; combination long and abbreviated argument names
TESTS[4]="--height 3.14159 --radius 2.71828"    # floating point input
TESTS[5]="--height --radius 0"                  # INVALID input: no height given
TESTS[6]="--height -30 --radius 30"             # INVALID input: negative measurement
TESTS[7]=""                                     # launch GUI

if [ -x $CYLINDER ];
then
    for test in "${TESTS[@]}"
    do
        echo -e "\n\033[1m[TEST] $CYLINDER $test\033[0m"
        $CYLINDER $test
        echo ""
    done
else
    echo "Either $CYLINDER hasn't been created yet or is not writable, run \"make\""
fi
