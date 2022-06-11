#!/usr/bin/python3

import z3
import sys
from subprocess import run, CalledProcessError
from z3 import *

pwd = os.path.dirname(__file__)
filePath = os.path.join(pwd, os.pardir, f"new.smt2")
parser = os.path.join(pwd, f"parser.py")
inv = sys.argv[1]


def call_ToSmt(inv):
    try:
        output = run(
            f'python3 {parser} "{inv}" > {filePath}',
            shell=True,
            capture_output=True,
            text=True,
        )
    except CalledProcessError as err:
        print(f"Simplify Run Error : {err}")
    # else:
    #     print(f"Simplifier Return : {output.returncode}")
    return output.returncode


def getExpr(inv):
    try:
        call_ToSmt(inv)
        f = z3.parse_smt2_file(filePath)
        simplifyTactic = Then(
            Tactic("simplify"),
            Tactic("propagate-values"),
            Tactic("solve-eqs"),
        )
        for expr in f:
            return simplifyTactic(expr)[0]
    except:
        return None


if __name__ == "__main__":
    ret = getExpr(inv)
    if isinstance(ret, list) and len(ret) > 0:
        print(ret[0])
    else:
        print(ret)
