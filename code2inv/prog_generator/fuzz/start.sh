#!/usr/bin/env bash
set -e
set -u
set -o pipefail

export CC=$(which hfuzz-clang)
export CXX=$(which hfuzz-clang++)
export AFL=$(which honggfuzz)

while getopts "b:o:t:e:" flag; do
  case "$flag" in
    b ) 
        buildDir=$OPTARG
        ;;
    o ) 
        outputDir=$OPTARG
        ;;
    t ) 
        testDir=$OPTARG
        ;;
    e ) 
        RUNNER=$OPTARG
        ;;
    \? ) 
        usagePrompt
        exit 1
        ;;
    : )
        echo "Invalid Option: -$OPTARG requires an argument" 1>&2
        exit 1
        ;;
  esac
done
shift $((OPTIND -1))    

export RUNNER=$RUNNER

rm -rf bin/* 
rm -rf output/

if [ $OPTIND -eq 1 ]; 
    then 
        usagePrompt
        exit 1 
fi

# Build Directory
mkdir -p "$buildDir" 

# Start Build
cd "$buildDir"
CC=$CC CXX=$CXX cmake ../
make -j 12
cd ../

# Some random seeds
mkdir -p tests
dd if=/dev/random of=tests/input01.txt bs=32 count=1
dd if=/dev/random of=tests/input02.txt bs=32 count=1
dd if=/dev/random of=tests/input03.txt bs=32 count=1
head -c 32 /dev/zero > tests/input04.txt
dd if=/dev/random of=tests/input05.txt bs=32 count=1
head -c 32 /dev/zero > tests/input06.txt

# Output Directory
mkdir -p "$outputDir" 