#!/usr/bin/bash

cat program_inputs/mod_inputs_$1.txt | sort | uniq -u > program_inputs/uniq_$1.txt
while IFS= read -r line; do
	echo $line
	./bin/main_$1.out $line
done < "program_inputs/uniq_$1.txt"
