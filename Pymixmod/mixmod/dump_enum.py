#!/usr/bin/env python
import os.path
import sys

from mixmod import gm


def dump_enum(k, gen_dir):
    enum_ = gm.__dict__[k]
    gen_file = os.path.join(gen_dir, k + ".txt")
    with open(gen_file, "w") as fd:
        for e in enum_:
            fd.write(" - " + e.name + "\n")


if __name__ == "__main__":
    if len(sys.argv) == 3:
        enums = sys.argv[2].split(",")
    else:
        enums = ["DataType", "CriterionName", "StrategyInitName", "AlgoName", "ModelName", "Family"]
    for enum_arg in enums:
        dump_enum(enum_arg, sys.argv[1])
