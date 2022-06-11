FROM ubuntu:focal

ENV TZ=Asia/Kolkata
RUN ln -snf /usr/share/zoneinfo/$TZ /etc/localtime && echo $TZ > /etc/timezone

RUN apt-get update && apt-get install -y \
    python3 time python3-pip g++ gcc make cmake cmake-data git wget unzip \
    nano figlet lolcat nano \
    software-properties-common python-is-python3 libbfd-dev libunwind8-dev \
    && rm -rf /var/lib/apt/lists/*

ARG CACHEBUST=1

RUN pip3 install datetime z3-solver scipy

RUN git clone https://github.com/google/honggfuzz.git --depth=1
RUN cd honggfuzz/ ; make ; make install ; rm -rf .git

RUN git clone https://github.com/lahiri-phdworks/Achar-Tool.git --depth=1 achar
RUN cd achar; pip3 install -e .
# RUN cd achar/clang-fe; make clean ; make -j 4
RUN cd achar/code2inv/prog_generator; mkdir -p results candidates cache models 
RUN rm -rf achar/docker
RUN rm -rf achar/benchmarks/Multiply/*.png
RUN rm -rf .git
WORKDIR /achar

RUN cd $HOME ; wget https://download.pytorch.org/libtorch/nightly/cpu/libtorch-shared-with-deps-latest.zip ; unzip libtorch-shared-with-deps-latest.zip
RUN apt-get update && apt-get install -y clang-10 clang++-10
WORKDIR /achar
