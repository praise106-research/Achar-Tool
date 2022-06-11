#!/usr/bin/bash

echo "Please annotate the program as per the template below."
echo "Mention all the keywords as shown in the template."
echo
echo
echo "
    int main() {
        // variable declarations
        int x;
        int y;
        // ...
        // pre-conditions
        // scanf(%d, &x);
        // scanf(%d, &y);
        (x = 0); // opaque (necessary if only mark line a opaque operation).
        // precheck
        // loopcond : x <= y
        // loopstart
        while (x <= y)
        // loop body
        {
            // ...
            x = x + 1;
            y = y - 1;
            // ...
        }
        // loopend
        // postcheck
        // post-condition
        assert((x > y));
    }
"
echo

if [[ -z $1 ]];
then
    echo "Give the Example Number/Name without extenstion."
    exit -1
fi

if [[ -z $2 ]];
then
    echo "Give the Example Type [OPT : fuzz, opaque, hybrid, colossus]"
    exit -1
fi

if [[ "$2" == "hybrid" ]];
then
    variables=$(grep -Po "int \K[a-zA-Z0-9_]*;" ../../../benchmarks/Hybrid_Examples/c/hybrid_${1}.c)
    vars=`echo $variables`
    python3 template.py "${vars}" hybrid_${1} ../../../benchmarks/Hybrid_Examples/c > ../../../code2inv/prog_generator/Hybrid_Examples/src/hybrid_${1}.c
    exit 0
fi

if [[ "$2" == "opaque" ]];
then
    variables=$(grep -Po "int \K[a-zA-Z0-9_]*;" ../../../benchmarks/Opaque_Examples/c/rq2_${1}.c)
    vars=`echo $variables`
    python3 template.py "${vars}" example_${1} ../../../benchmarks/Opaque_Examples/c > ../../../code2inv/prog_generator/Opaque_Examples/src/example_${1}.c
    exit 0
fi

if [[ "$2" == "fuzz" ]];
then
    variables=$(grep -Po "int \K[a-zA-Z0-9_]*;" ../../../benchmarks/C_instances/c/${1}.c)
    vars=`echo $variables`
    python3 template.py "${vars}" ${1} ../../../benchmarks/C_instances/c > ../../../code2inv/prog_generator/fuzz/src/${1}.c
    exit 0
fi

if [[ "$2" == "colossus" ]];
then
    variables=$(grep -Po "int \K[a-zA-Z0-9_]*;" ../../../benchmarks/C_instances/c/${1}.c)
    vars=`echo $variables`
    python3 colossus.py "${vars}" ${1} ../../../benchmarks/C_instances/c > ../../../code2inv/prog_generator/colossus/src/loop_${1}.c
    exit 0
fi