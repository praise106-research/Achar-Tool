#!/usr/bin/env bash

echo "================================"
echo " Setting up ACHAR in $HOME dir"
echo " Requires sudo access.        "
echo "================================"

mv patch_1.patch $HOME
cd $HOME

# Basic Setup requirements
sudo apt-get update && sudo apt-get install -y \
    python3 time python3-pip g++ gcc make cmake cmake-data git \
    wget unzip figlet lolcat clang-10 clang++-10 z3 \
    software-properties-common python-is-python3

# PIP packages required.
pip3 install datetime z3-solver scipy tqdm matplotlib seaborn

cd $HOME
echo " Installing HonggFuzz "

# HonggFuzz Dependencies
sudo apt-get install libbfd-dev libunwind8-dev

# Clone HonggFuzz
git clone https://github.com/google/honggfuzz.git
cd honggfuzz/

# Build it from source.
make -j2 
sudo make install 

cd $HOME

echo " Setting up libtorch "
# Get the libtorch shared zip and unzip it.
wget https://download.pytorch.org/libtorch/nightly/cpu/libtorch-shared-with-deps-latest.zip
unzip libtorch-shared-with-deps-latest.zip

echo " Setting up ACHAR "

# Clone Code2Inv Repository
git clone https://github.com/PL-ML/code2inv
cd code2inv

# Apply patch and install the rest
# of the dependencies.
git apply ../patch_1.patch
pip3 install -e .

echo "  All set to use ACHAR Tool !"
echo "  ACHAR Tool Dir -> cd $HOME/code2inv"
echo 
echo "  To run an example say 11, use :"
echo "      ./runbench.sh 11 fuzz_spec"
echo "  See the README shared for more details."