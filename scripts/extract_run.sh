#!/bin/bash

>stats.log
echo "Tool Setting, #Solved, #Failed, #Cex, Time(secs)" | tee data_summary.csv

echo
echo FUZZER_ALL_10_8_64 | lolcat
echo

mkdir -p CSVs CE_Data Time_Data
mkdir -p CE_Data/All-VS-One Time_Data/All-VS-One
mkdir -p CE_Data/Hybrid Time_Data/Hybrid
mkdir -p CE_Data/K-Induction Time_Data/K-Induction
mkdir -p CE_Data/RQ1_Exp Time_Data/RQ1_Exp
mkdir -p Time_Data/Code2Inv CE_Data/Code2Inv

./generate_data_all.sh 10 8 64 cache ACHAR_ALL_10_8_64 "Achar (All, 10s)"

mv CE_Data/ce_data_ACHAR_ALL_10_8_64.json CE_Data/All-VS-One/ce_data_ACHAR_ALL_10_8_64.json
mv Time_Data/time_data_ACHAR_ALL_10_8_64.json Time_Data/All-VS-One/time_data_ACHAR_ALL_10_8_64.json

echo
echo "Achar (All, 10s)" | lolcat
echo FUZZER_ALL_20_8_64 | lolcat
echo

./generate_data_all.sh 20 8 64 cache ACHAR_ALL_20_8_64 "Achar (All, 20s)"

mv CE_Data/ce_data_ACHAR_ALL_20_8_64.json CE_Data/All-VS-One/ce_data_ACHAR_ALL_20_8_64.json
mv Time_Data/time_data_ACHAR_ALL_20_8_64.json Time_Data/All-VS-One/time_data_ACHAR_ALL_20_8_64.json

echo
echo "Achar (All, 20s)" | lolcat
echo HYBRID_LOOP_10_8_64 | lolcat
echo

mkdir -p CE_Data/Hybrid Time_Data/Hybrid
./generate_data.sh hybrid_loop_10 8 64 cache HYBRID_LOOP_10_8_64 "Achar (Hybrid, Loop)"

mv CE_Data/ce_data_HYBRID_LOOP_10_8_64.json CE_Data/Hybrid/ce_data_HYBRID_LOOP_10_8_64.json
mv Time_Data/time_data_HYBRID_LOOP_10_8_64.json Time_Data/Hybrid/time_data_HYBRID_LOOP_10_8_64.json

echo
echo "Achar (Hybrid, Loop)" | lolcat
echo HYBRID_PRE_10_8_64 | lolcat
echo

./generate_data.sh hybrid_pre_10 8 64 cache HYBRID_PRE_10_8_64 "Achar (Hybrid, Pre)"

mv CE_Data/ce_data_HYBRID_PRE_10_8_64.json CE_Data/Hybrid/ce_data_HYBRID_PRE_10_8_64.json
mv Time_Data/time_data_HYBRID_PRE_10_8_64.json Time_Data/Hybrid/time_data_HYBRID_PRE_10_8_64.json

echo
echo "Achar (Hybrid, Pre)" | lolcat
echo FUZZER_10_8_1 | lolcat
echo

mkdir -p CE_Data/K-Induction Time_Data/K-Induction
./generate_data.sh 10 8 1 cache ACHAR_K_10_8_1 "Achar (K=1)"

mv CE_Data/ce_data_ACHAR_K_10_8_1.json CE_Data/K-Induction/ce_data_ACHAR_K_10_8_1.json
mv Time_Data/time_data_ACHAR_K_10_8_1.json Time_Data/K-Induction/time_data_ACHAR_K_10_8_1.json

echo
echo "Achar (K=1)" | lolcat
echo FUZZER_10_8_2 | lolcat
echo

./generate_data.sh 10 8 2 cache ACHAR_K_10_8_2 "Achar (K=2)"

mv CE_Data/ce_data_ACHAR_K_10_8_2.json CE_Data/K-Induction/ce_data_ACHAR_K_10_8_2.json
mv Time_Data/time_data_ACHAR_K_10_8_2.json Time_Data/K-Induction/time_data_ACHAR_K_10_8_2.json

echo
echo "Achar (K=2)" | lolcat
echo FUZZER_10_8_16 | lolcat
echo

./generate_data.sh 10 8 16 cache ACHAR_K_10_8_16 "Achar (K=16)"

mv CE_Data/ce_data_ACHAR_K_10_8_16.json CE_Data/K-Induction/ce_data_ACHAR_K_10_8_16.json
mv Time_Data/time_data_ACHAR_K_10_8_16.json Time_Data/K-Induction/time_data_ACHAR_K_10_8_16.json

echo
echo "Achar (K=16)" | lolcat
echo FUZZER_10_8_32 | lolcat
echo

./generate_data.sh 10 8 32 cache ACHAR_K_10_8_32 "Achar (K=32)"

mv CE_Data/ce_data_ACHAR_K_10_8_32.json CE_Data/K-Induction/ce_data_ACHAR_K_10_8_32.json
mv Time_Data/time_data_ACHAR_K_10_8_32.json Time_Data/K-Induction/time_data_ACHAR_K_10_8_32.json

echo
echo "Achar (K=32)" | lolcat
echo FUZZER_10_8_64 | lolcat
echo

./generate_data.sh 10 8 64 cache ACHAR_K_10_8_64 "Achar (K=64)"

mv CE_Data/ce_data_ACHAR_K_10_8_64.json CE_Data/K-Induction/ce_data_ACHAR_K_10_8_64.json
mv Time_Data/time_data_ACHAR_K_10_8_64.json Time_Data/K-Induction/time_data_ACHAR_K_10_8_64.json

echo
echo "Achar (K=64)" | lolcat
echo FUZZER_10_8_128 | lolcat
echo

./generate_data.sh 10 8 128 cache ACHAR_K_10_8_128 "Achar (K=128)"

mv CE_Data/ce_data_ACHAR_K_10_8_128.json CE_Data/K-Induction/ce_data_ACHAR_K_10_8_128.json
mv Time_Data/time_data_ACHAR_K_10_8_128.json Time_Data/K-Induction/time_data_ACHAR_K_10_8_128.json

echo
echo "Achar (K=128)" | lolcat
echo FUZZER_10_8_64 | lolcat
echo

mkdir -p CE_Data/RQ1_Exp Time_Data/RQ1_Exp
./generate_data.sh 10 8 64 cache ACHAR_K_10_8_64 "Achar (Single, 10s)"

cp CE_Data/ce_data_ACHAR_K_10_8_64.json CE_Data/All-VS-One/ce_data_ACHAR_K_10_8_64.json
mv CE_Data/ce_data_ACHAR_K_10_8_64.json CE_Data/RQ1_Exp/ce_data_ACHAR_K_10_8_64.json

cp Time_Data/time_data_ACHAR_K_10_8_64.json Time_Data/All-VS-One/time_data_ACHAR_K_10_8_64.json
mv Time_Data/time_data_ACHAR_K_10_8_64.json Time_Data/RQ1_Exp/time_data_ACHAR_K_10_8_64.json

echo
echo "Achar (Single, 10s)" | lolcat
echo FUZZER_10_8_64 | lolcat
echo

./generate_data.sh 10 8 64 cache ACHAR_K_10_8_64 "Achar"

mv CE_Data/ce_data_ACHAR_K_10_8_64.json CE_Data/Hybrid/ce_data_ACHAR_K_10_8_64.json
mv Time_Data/time_data_ACHAR_K_10_8_64.json Time_Data/Hybrid/time_data_ACHAR_K_10_8_64.json

echo
echo "Achar" | lolcat
echo FUZZER_20_8_64 | lolcat
echo

./generate_data.sh 20 8 64 cache ACHAR_SINGLE_20_8_64 "Achar (Single, 20s)"

mv CE_Data/ce_data_ACHAR_SINGLE_20_8_64.json CE_Data/All-VS-One/ce_data_ACHAR_SINGLE_20_8_64.json
mv Time_Data/time_data_ACHAR_SINGLE_20_8_64.json Time_Data/All-VS-One/time_data_ACHAR_SINGLE_20_8_64.json

echo
echo "Achar (Single, 20s)" | lolcat
echo Z3_ALL_VARIANT | lolcat
echo

mkdir -p Time_Data/Code2Inv CE_Data/Code2Inv
./generate_data.sh z3 all 8 cache CODE2INV_ALL "Code2Inv"

cp CE_Data/ce_data_CODE2INV_ALL.json CE_Data/Hybrid/ce_data_CODE2INV_ALL.json
cp CE_Data/ce_data_CODE2INV_ALL.json CE_Data/Code2Inv/ce_data_CODE2INV_ALL.json
mv CE_Data/ce_data_CODE2INV_ALL.json CE_Data/RQ1_Exp/ce_data_CODE2INV_ALL.json

cp Time_Data/time_data_CODE2INV_ALL.json Time_Data/Hybrid/time_data_CODE2INV_ALL.json
cp Time_Data/time_data_CODE2INV_ALL.json Time_Data/Code2Inv/time_data_CODE2INV_ALL.json
mv Time_Data/time_data_CODE2INV_ALL.json Time_Data/RQ1_Exp/time_data_CODE2INV_ALL.json

echo
echo "Code2Inv" | lolcat
echo Z3_SINGLE_VARIANT | lolcat
echo

mkdir -p Time_Data/Code2Inv CE_Data/Code2Inv
./generate_data.sh z3 single 8 cache CODE2INV_SINGLE "Code2Inv (Single)"

mv CE_Data/ce_data_CODE2INV_SINGLE.json CE_Data/Code2Inv/ce_data_CODE2INV_SINGLE.json
mv Time_Data/time_data_CODE2INV_SINGLE.json Time_Data/Code2Inv/time_data_CODE2INV_SINGLE.json

echo "Code2Inv (Single)" | lolcat
echo

./plot.sh
mv stats.log data_summary.txt
