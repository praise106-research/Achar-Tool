# Experimental Script
# This wont work on standalone examples

import os
import sys
import json
import re

from code2inv.processing.simplifier import getExpr
from code2inv.prog_generator.checkers.c_inv_checker import inv_solver

pwd = os.path.dirname(__file__)
benchmark = os.path.join(pwd, os.pardir, "benchmarks", "C_instances", "c_smt2")

if __name__ == "__main__":

    resDict = dict()
    instanceObj = dict()
    best_root = []
    fileName = sys.argv[1]
    resultFile = fileName.strip().split("/")[-1]
    inv = ""

    example = resultFile.strip().split("_")[2]

    if "c_nl_spec" in fileName:
        invType = "c_nl_spec"
    elif "c_nl_all_spec" in fileName:
        invType = "c_nl_all_spec"
    elif "c_spec" in fileName:
        invType = "c_spec"
    elif "fuzz_spec" in fileName:
        invType = "fuzz_spec"
    elif "hybrid_spec_all" in fileName:
        invType = "hybrid_spec_all"
    elif "hybrid_spec" in fileName:
        invType = "hybrid_spec"
    elif "hybrid_pre_spec" in fileName:
        benchmark = os.path.join(pwd, os.pardir, "benchmarks", "hybrid_pre",
                                 "c_smt2")
        invType = "hybrid_pre_spec"
    elif "hybrid_loop_spec" in fileName:
        benchmark = os.path.join(pwd, os.pardir, "benchmarks", "hybrid_loop",
                                 "c_smt2")
        invType = "hybrid_loop_spec"
    elif "colossus_spec" in fileName:
        invType = "colossus_spec"
    elif "fuzz_nl_spec" in fileName:
        invType = "fuzz_nl_spec"
    else:
        pass

    if "inv_result" in fileName:
        converged = "Yes"
    elif "log_inv" in fileName:
        converged = "No"
    else:
        pass

    vc_file = os.path.join(benchmark, f"{example}.c.smt")

    with open(fileName, mode="r") as fileptr:
        lines = fileptr.readlines()

    z3_cexs = lines[-1]
    z3_report_time = re.findall("z3_report time: [0-9]*[.][0-9]*", z3_cexs)
    actual_z3 = re.findall("'actual_z3': [0-9]*", z3_cexs)
    stats = actual_z3[0].split(":")[1]

    if len(z3_report_time) > 0:
        timetaken = z3_report_time[0].split(":")[1]
    else:
        timetaken = 0.0

    if len(lines) > 0:
        for l in lines:
            if "best_root" in l:
                best_root.append(l.strip())

        if len(best_root) > 0 and "best_root" in best_root[-1]:
            inv = best_root[-1].strip().split(":")[1].strip()
        else:
            inv = lines[0].strip()

    res = inv_solver(vc_file, str(inv))

    if res == [None, None, None]:
        check = "Passed"
        resDict["status"] = True
    else:
        check = "Failed"
        resDict["status"] = False

    simpleExpr = getExpr(str(inv))
    if isinstance(simpleExpr, list):
        simpleStr = ".".join(x for x in simpleExpr)
    else:
        simpleStr = str(simpleExpr)

    print(
        f'{example}, {invType}, {str(inv)}, {str(check)}, {str(converged)}, "{simpleStr}", {stats}, {timetaken}'
    )
