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

mkdir -p opaque_transforms linklibs template

for files in {1..133}; do 
    variables=$(grep -Po "int \K[a-zA-Z0-9_]*;" c/$files.c)
    vars=`echo $variables`
    python3 template.py "${vars}" $files c > linklibs/link_$files.c; 
    python3 template_only.py "${vars}" $files c > template/$files.c;
    python3 opaque_transform.py "${vars}" $files c > opaque_transforms/$files.c;
done

find . -regex '.*\.\(cpp\|hpp\|cu\|c\|h\)' -exec clang-format -style=file -i {} \;

cd linklibs
for files in {1..133}; do 
    gcc -std=c++17 -I../include -c -ftest-coverage -fprofile-arcs -Wall -O0 link_$files.c -o link_$files.o
done
cd ..

cd template
for files in {1..133}; do 
    gcc -std=c++17 -I../include -c -ftest-coverage -fprofile-arcs -Wall -O0 $files.c -o $files.o
done
cd ..

mkdir -p bin
for files in {1..133}; do 
    hfuzz-clang -std=c++17 -I../include -Wall -O0 template/$files.o linklibs/link_$files.o -o bin/main_$files -lgcov
    ./bin/main_$files
done
