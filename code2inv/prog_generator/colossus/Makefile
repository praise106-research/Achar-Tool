LLVM_SRC=/data/llvm-3.4.2.src
LLVM_BUILD=${LLVM_SRC}/build
LLVM_BIN=${LLVM_BUILD}/Release+Debug+Asserts/bin
LLVM_LIB=${LLVM_BUILD}/Release+Debug+Asserts/lib
Z3_BUILD=/data/z3-old/z3-z3-4.4.1/build/
KLEE_UCLIBC=/data/colossus-uclibc/
 
COLOSSUS=/data/klee-colassus
COLOSSUS_BIN=${COLOSSUS}/build/Release+Debug+Asserts/bin
KLEE_INCLUDES_DIR=${COLOSSUS}/include
CONTROL_FUNCTIONS=${COLOSSUS}/controlFunctionsFuncolic
OTHER_FUNCTIONS=${COLOSSUS}/otherFunctions
CLANG_BIN=${LLVM_BIN}
OTHER_INCLUDES_DIR=/data/Documents/Research/code2inv/code2inv/prog_generator/colossus/include
LIBC=uclibc

TEST=${EXAMPLE}

compile:
	${CLANG_BIN}/clang -c -emit-llvm -I ${KLEE_INCLUDES_DIR} -I ${OTHER_INCLUDES_DIR} -g -O0 -fPIC -fno-rtti src/${TEST}.c -o ${TEST}.bc

all: compile
	rm -rf base_colossus
	timeout --preserve-status -k 100 100 ${COLOSSUS_BIN}/klee --libc=${LIBC} \
	--control-functions=${CONTROL_FUNCTIONS} \
	--always-generate-code=false --debug-funcolic=1 \
	--debug-executor=1 --make-external-call-symbolic=false \
	--use-bp=true --fuzz-timeout=300 --other-functions=${OTHER_FUNCTIONS} \
	--inline-other-functions=true \
	--inline-control-functions=true \
	--posix-runtime \
	--max-instruction-time=30 --write-kqueries --output-dir=base_colossus \
	--max-time=3600. ${TEST}.bc 

clean:
	rm -f *.bc *.out core
	chmod 777 * */*
