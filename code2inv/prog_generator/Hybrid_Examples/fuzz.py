import io
import os
import time
import sys
import threading
from subprocess import run, CalledProcessError

pwd = os.path.dirname(__file__)
example = sys.argv[1]
timeout = sys.argv[2]

filepath = os.path.join(pwd, f"include/{example}.h")
fuzzbase = os.path.join(pwd)
outputFile = os.path.join(pwd, "models.txt")
collection_semantic = [None, None, None, None]


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
        output = run(
            f"timeout {time} ./fuzz.sh -b ./bin -o ./output -t ./tests -e {example}",
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
    # TODO : Now we have to make three parallel calls for pre, loop and post as per new sampling technique.
    try:
        # print(f"Running AFL on Example {example}.c")
        # COMMENT : Start fresh fuzzing and clean previous model written.
        output = run(
            f"./start.sh -b ./bin/ -o ./output/ -t ./tests/ -e {example}",
            shell=True,
            capture_output=True,
            text=True,
        )
    except CalledProcessError as err:
        print(f"Build Error : {err}")
    # else:
    #     print(f"Build Return : {output.returncode}")
    return output.returncode


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


if __name__ == "__main__":

    init_fuzzbase()
    call_fuzzsolver(timeout)

    process_crashes(outputFile)
    res = mergeModels()

    print(f"{res}")
