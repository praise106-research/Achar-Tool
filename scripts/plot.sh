#!/bin/bash

mkdir -p Time CEs

echo ==== Time Plots ==== 

# One VS All
python3 ./plots/mkplot/mkplot.py  -l --legend prog_alias --font=palatino \
--font-sz=20 -t 1000 --ymin=0 --ymax=1100 --xmin=0 --xmax=110 --xlabel="\# Instances Solved" \
--ylabel="Time Taken (sec)" -b pdf --save-to Time/time_all_vs_one_instances.pdf Time_Data/All-VS-One/*.json

# K-induction
python3 ./plots/mkplot/mkplot.py  -l --legend prog_alias \
--font=palatino --font-sz=20 -t 600 --ymin=0 --ymax=610 --xmin=0 --xmax=110 --xlabel="\# Instances Solved" \
--ylabel="Time Taken (sec)" -b pdf --save-to Time/time_k_induction_instances.pdf Time_Data/K-Induction/*.json

# RQ1 Experiment
python3 ./plots/mkplot/mkplot.py  -l --legend prog_alias \
--font=palatino --font-sz=20 -t 600 --ymin=0 --ymax=610 --xmin=0 --xmax=110 --xlabel="\# Instances Solved" \
--ylabel="Time Taken (sec)" -b pdf --save-to Time/time_rq1.pdf Time_Data/RQ1_Exp/*.json

# Hybrid Study
python3 ./plots/mkplot/mkplot.py  -l --legend prog_alias \
--font=palatino --font-sz=20 -t 450 --ymin=0 --ymax=500 --xmin=0 --xmax=110 --xlabel="\# Instances Solved" \
--ylabel="Time Taken (sec)" -b pdf --save-to Time/time_hybrid.pdf Time_Data/Hybrid/*.json

# Vanilla
python3 ./plots/mkplot/mkplot.py  -l --legend prog_alias \
--font=palatino --font-sz=20 -t 550 --ymin=0 --ymax=600 --xmin=0 --xmax=110 --xlabel="\# Instances Solved" \
--ylabel="Time Taken (sec)" -b pdf --save-to Time/time_vanilla.pdf Time_Data/Code2Inv/*.json

echo ==== CEs Plots ==== 

# One VS All
python3 ./plots/mkplot/mkplot.py  -l --legend prog_alias \
--font=palatino --font-sz=20 --key=CEs -t 60 --ymin=0 --ymax=65 --xmin=0 --xmax=110 --xlabel="\# Instances Solved" \
--ylabel="\# Counter Examples" -b pdf --save-to CEs/ces_all_vs_one_instances.pdf CE_Data/All-VS-One/*.json

# K-induction
python3 ./plots/mkplot/mkplot.py  -l --legend prog_alias \
--font=palatino --font-sz=20 --key=CEs -t 50 --ymin=0 --ymax=55 --xmin=0 --xmax=110 --xlabel="\# Instances Solved" \
--ylabel="\# Counter Examples" -b pdf --save-to CEs/ces_k_induction_instances.pdf CE_Data/K-Induction/*.json

# RQ1 Experiment
python3 ./plots/mkplot/mkplot.py  -l --legend prog_alias \
--font=palatino --font-sz=20 --key=CEs -t 40 --ymin=0 --ymax=45 --xmin=0 --xmax=110 --xlabel="\# Instances Solved" \
--ylabel="\# Counter Examples" -b pdf --save-to CEs/ces_rq1.pdf CE_Data/RQ1_Exp/*.json

# Hybrid Study
python3 ./plots/mkplot/mkplot.py  -l --legend prog_alias \
--font=palatino --font-sz=20 --key=CEs -t 40 --ymin=0 --ymax=45 --xmin=0 --xmax=110 --xlabel="\# Instances Solved" \
--ylabel="\# Counter Examples" -b pdf --save-to CEs/ces_hybrid.pdf CE_Data/Hybrid/*.json

# Vanilla Experiment
python3 ./plots/mkplot/mkplot.py  -l --legend prog_alias \
--font=palatino --font-sz=20 --key=CEs -t 45 --ymin=0 --ymax=50 --xmin=0 --xmax=110 --xlabel="\# Instances Solved" \
--ylabel="\# Counter Examples" -b pdf --save-to CEs/ces_vanilla.pdf CE_Data/Code2Inv/*.json

mkdir -p ./plots/CEs
mkdir -p ./plots/Time

mv CEs/* ./plots/CEs
mv Time/* ./plots/Time

rm -rf Time CEs