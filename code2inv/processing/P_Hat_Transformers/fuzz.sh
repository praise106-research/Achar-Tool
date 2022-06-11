#!/usr/bin/env bash
set -e
set -u
set -o pipefail

export CC=$(which hfuzz-clang)
export CXX=$(which hfuzz-clang++)
export AFL=$(which honggfuzz)

while getopts "b:o:t:e:m:c:" flag; do
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
    m ) 
        MEMORY=$OPTARG
        ;;
    c ) 
        CHECK=$OPTARG
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

# Test Directory
if [[ ! -d $testDir ]]; then
    echo "Test : $testDir not found !!" 1>&2
fi

>models.txt
$AFL -i $testDir -o $outputDir -n 1 --exit_upon_crash --mutations_per_run 200 -P -- $buildDir/$RUNNER

# COMMENT : We can use --exit_upon_crash (exits on first crash) & --linux_perf_bts_edge 