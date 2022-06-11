import os
import sys
import json
from csv import DictReader
from itertools import groupby

# from pprint import pprint

preamble = {}
preamble["program"] = sys.argv[3]
preamble["prog_alias"] = sys.argv[3]
preamble["benchmark"] = "133 Benchmark Examples(SyGUS)"

total_cex = 0
total_time = 0.00
pass_count = 0
fail_count = 0

with open(os.path.join(sys.argv[1]), mode="r") as csvfile:
    r = DictReader(csvfile, skipinitialspace=True)
    data = [dict(d) for d in r]

    ce_json = {}
    ce_json["stats"] = {}

    time_json = {}
    time_json["stats"] = {}

    for r1, r2 in groupby(
            data, lambda r:
        (r["Benchmark Example"], r["CE-s Count"], r["Z3 Check Pass"])):
        total_cex += int(f"{r1[1]}")
        ce_json["stats"][f"{r1[0]}"] = {}
        ce_json["stats"][f"{r1[0]}"] = {
            "CEs": int(f"{r1[1]}"),
            "status": True if f"{r1[2]}" == "Passed" else False,
        }
        if f"{r1[2]}" == "Passed":
            pass_count += 1
        if f"{r1[2]}" == "Failed":
            fail_count += 1

    for r1, r2 in groupby(
            data, lambda r:
        (r["Benchmark Example"], r["Solve-Time"], r["Z3 Check Pass"])):
        total_time += float(f"{r1[1]}")
        time_json["stats"][f"{r1[0]}"] = {}
        time_json["stats"][f"{r1[0]}"] = {
            "rtime": float(f"{r1[1]}"),
            "status": True if f"{r1[2]}" == "Passed" else False,
        }

extra_data = {}
extra_data["total_cex"] = total_cex
extra_data["total_time"] = total_time

ce_json["preamble"] = preamble
ce_json["extra_data"] = extra_data
with open(os.path.join("CE_Data", f"ce_data_{sys.argv[2]}.json"),
          mode="w") as efl:
    json.dump(ce_json, efl, indent=4, sort_keys=True)

time_json["preamble"] = preamble
time_json["extra_data"] = extra_data
with open(os.path.join("Time_Data", f"time_data_{sys.argv[2]}.json"),
          mode="w") as efl:
    json.dump(time_json, efl, indent=4, sort_keys=True)

with open("stats.log", mode="a") as wfl:
    wfl.write(f"{sys.argv[3]} ==> \n")
    wfl.write(f"\t == Solved Examples : \t\t\t\t\t\t\t{pass_count}, {fail_count} == \n")
    wfl.write(f"\t\t\ttotal_cex : {total_cex}\n")
    wfl.write(f"\t\t\ttotal_time : {round(total_time, 1)} sec\n")
    wfl.write(f"\t\t\t\t <======================> \t\t\t\n\n")

with open("data_summary.csv", mode='a') as csvWriteDump:
    toolSetting = sys.argv[3].strip().replace(",", ".")
    csvWriteDump.write(f"{toolSetting},")
    csvWriteDump.write(f"{pass_count},")
    csvWriteDump.write(f"{fail_count},")
    csvWriteDump.write(f"{total_cex},")
    csvWriteDump.write(f"{round(total_time, 1)}\n")