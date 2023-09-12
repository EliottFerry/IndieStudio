#!/bin/bash

function usage(){
    printf "Usage of the script :\n"
    printf "\tno parameter : Printing this message. [./compile.sh]\n"
    printf "\t-h : Printing this message. [./compile.sh -h]\n"
    printf "\t-all : Creating 'build' directory, and doing all the command to compile the program. [./compile.sh -all]\n"
    printf "\t-build : Only creating the build directory, and doing the cmake command in it. [./compile.sh -build]\n"
    printf "\t-run : Only doing the 'make' command in the 'build' folder, and going back to the main directory. [./compile.sh -run]\n"
    printf "\t-v : You can add this on top of other command, to run the program with valgrind. [./compile.sh -v -run]\n"
    printf "\t-verbose : You can add this on top of other command, to compile the program with verbose rule. [./compile.sh -verbose -run]\n"
}

function Create(){
    if [ ! -d "build" ];
    then
        mkdir build
        cd build/ && cmake .. && cd ../
        printf "The program returned : "
        echo $?
        printf "\n"
        printf "Done.\n"
    else
        rm -rf build/
        mkdir build
        cd build/ && cmake .. && cd ..
        printf "The program returned : "
        echo $?
        printf "\n"
        printf "Done.\n"
    fi
}

function Run(){
    if [ ! -d "build" ];
    then
        printf "Your build file does not exist.\n"
    else
        cd build/ && make $VERBOSE -j && cd ../ && $VALGRIND ./bomberman
        printf "The program returned : "
        echo $?
        printf "\n"
        printf "Done.\n"
    fi
}

function all(){
    if [ ! -d "build" ];
    then
        Create
        Run
    else
        rm -rf build/
        Create
        Run
    fi
}

VALGRIND=""
VERBOSE=""

if [ $# -eq 0 ]
then
    usage
else
    for COMMAND in $@
    do
        if [ $COMMAND == "-v" ]
        then
            VALGRIND="valgrind"
        elif [ $COMMAND == "-verbose" ]
        then
            VERBOSE="VERBOSE=1"
        elif [ $COMMAND == "-build" ]
        then
            Create
        elif [ $COMMAND == "-run" ]
        then
            Run
        elif [ $COMMAND == "-all" ]
        then
            all
        else
            usage
        fi
    done
fi
