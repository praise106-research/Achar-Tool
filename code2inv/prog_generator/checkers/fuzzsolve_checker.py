# Run fuzz solver as subprocess and
# then use it to test the invariants.

# AFL/fuzzsolver module.
from code2inv.prog_generator.checkers.c_inv_checker import inv_solver as c_inv_solver
from code2inv.prog_generator.checkers.c_inv_checker import inv_checker as c_inv_checker
from code2inv.common.constants import AFL_CALLS
from subprocess import run, CalledProcessError
from code2inv.common.cmd_args import cmd_args
from code2inv.prog_generator.chc_tools.chctools.solver_utils import *
from code2inv.prog_generator.chc_tools.chctools.horndb import *
from tqdm import tqdm

import datetime
import threading
import io
import os
import time

set_build = False
pwd = os.path.dirname(__file__)

if cmd_args.example:
    example = cmd_args.example
else:
    example = "10"

if cmd_args.example:
    timeout = cmd_args.afl_timeout
else:
    timeout = 20

dump_results = os.path.join(pwd, os.pardir, f"results/log_inv_{example}.txt")
filepath = os.path.join(pwd, os.pardir, f"fuzz/include/{example}.h")
fuzzbase = os.path.join(pwd, os.pardir, f"fuzz")
outputFile = os.path.join(pwd, os.pardir, "models.txt")
collection_semantic = [None, None, None, None]

# premodelsfile = os.path.join(pwd, os.pardir, "premodels.txt")
# loopmodelsfile = os.path.join(pwd, os.pardir, "loopmodels.txt")
# postmodelsfile = os.path.join(pwd, os.pardir, "postmodels.txt")

# checkList = ["precheck", "loopcheck", "postcheck"]
# modelFilesList = [premodelsfile, loopmodelsfile, postmodelsfile]
# fuzzThreadsReturns = [None, None, None]
# returncodes = [None, None, None]


def inv_checker(vc_file: str, inv: str, assignments):
    # tqdm.write(f"Checking {inv}")
    ret_vals = c_inv_checker(vc_file, inv, assignments)
    # tqdm.write(f'{false}')
    return ret_vals


def process_model_string(model: str):
    # COMMENT : iterate over all crashes inputs and extract test failures
    vals = []
    decls = []
    model_val = dict()

    if model == "":
        return None

    cex_type = model.strip().split(":")[0].strip()
    m_list = model.strip().replace(":", ",").split(",")
    for index, elems in enumerate(m_list):
        if (index % 2) == 0:
            vals.append(elems.strip())
        else:
            decls.append(elems.strip())
    vals.pop(0)
    for key, values in zip(decls, vals):
        model_val[f"{key}"] = values
    return [cex_type, model_val]


def call_fuzzsolver(time):
    # TODO : Now we have to make three parallel calls for pre, loop and post as per new sampling technique.
    try:
        # print(f"Running AFL on Example {example}.c")
        # COMMENT : Start fresh fuzzing and clean previous model written.
        open(outputFile, mode="w").close()
        output = run(
            f"timeout {time} {fuzzbase}/fuzz.sh -b {fuzzbase}/bin -t {fuzzbase}/tests \
                -o {fuzzbase}/output -e {example}",
            shell=True,
            capture_output=True,
            text=True,
        )
    except CalledProcessError as err:
        print(f"Fuzzer Error : {err}")
    # else:
    #     print(f"Fuzzer Return : {output.returncode}")
    return output.returncode


def init_fuzzbase():
    try:
        # print(f"Initialized AFL run on Example {example}.c")
        output = run(
            f"{fuzzbase}/start.sh -b {fuzzbase}/bin -t {fuzzbase}/tests \
                -o {fuzzbase}/output -e {example}",
            shell=True,
            capture_output=True,
            text=True,
        )
    except CalledProcessError as err:
        print(f"Build Error : {err}")
    # else:
    #     print(f"Build Return : {output.returncode}")
    return output.returncode


def dump_template(file, inv_code):
    with open(file, mode="w") as fileptr:
        fileptr.write(f"#define PHI {inv_code} // generated by code2inv\n")


def process_crashes(fileName):
    # COMMENT : iterate over all crashes inputs and extract test failures
    results = None
    # collection_semantic = [None, None, None]
    with open(fileName, mode="r") as fileptr:
        models = fileptr.readlines()
        if isinstance(models, list) and len(models) > 0:
            for lines in models:
                for index, x in enumerate(
                    ["Pre :", "LoopStart : ", "LoopEnd : ", "Post :"]):
                    if x in lines:
                        collection_semantic[index] = lines.strip()
                    # else:
                    #     collection_semantic[index] = None
            else:
                return None


def mergeModels():
    premodel = [None]
    loopmodel = [None]
    postmodel = [None]
    temp = []

    if all(x is None for x in collection_semantic):
        return [None, None, None]

    for x in collection_semantic:
        if x is not None:
            cex_type, res = process_model_string(x)

            if cex_type == "LoopStart" or cex_type == "LoopEnd":
                temp.append(res)
                if len(temp) == 2:
                    (a, b) = temp[0], temp[1]
                    loopmodel[0] = (a, b)
                    temp = []

            if cex_type == "Pre":
                premodel[0] = res

            if cex_type == "Post":
                postmodel[0] = res

    return [premodel[0], loopmodel[0], postmodel[0]]


def inv_solver(vc_file: str, inv: str):
    # COMMENT : Gets called in each env.step() iteration.
    # COMMENT : None of these functions must fail here.
    # tqdm.write(f"fuzz-inv solver called : {inv}")

    tqdm.write(f"{datetime.datetime.now()} [Fuzz Checker] {inv}")

    for i in range(len(collection_semantic)):
        collection_semantic[i] = None

    open(outputFile, mode="w").close()

    dump_template(filepath, inv)

    init_fuzzbase()
    call_fuzzsolver(timeout)

    time.sleep(0.1)

    process_crashes(outputFile)
    res = mergeModels()

    if not os.path.isdir("models"):
        os.mkdir("models")

    # COMMENT : Print Fuzz Model
    with open(
            os.path.join(
                "models",
                f"{cmd_args.spec_type}_model_{cmd_args.example}_{cmd_args.afl_timeout}_{cmd_args.num_epochs}.log",
            ),
            mode="a",
    ) as file:
        file.write(f"{res}\n")

    # tqdm.write(f"{res}")
    return res
