#!/usr/bin/env python3
"""
This script will alter the variable and function names in another script

This should generally function as intended, but you should test the obfuscated
script before running it. Some manual adjustments may be required.

author: @linkavych
date: 2022-08-14
"""
import random
import re
import string

# CLI Stuff
import typer


def MKVFbdsgGf(lnt: int):
    """
    Return a random string of length lnt
    """
    oGtb = string.ascii_letters
    print(oGtb)
    return "".join(random.choices(oGtb, k=lnt))


def rkzgKcUo(oueqpqvtv: list, YRzCP: list, script: str):
    with open(script, "r") as f:
        xCvT = f.read()
        for var in oueqpqvtv:
            if "__name__" == var or "str" == var:
                continue
            else:
                xCvT = xCvT.replace(var, MKVFbdsgGf(len(var)))
        for func in YRzCP:
            if "main" == func:
                continue
            else:
                xCvT = xCvT.replace(func, MKVFbdsgGf(len(func)))

    with open("obfuscated_script.py", "w") as fd:
        fd.write(xCvT)


def main(script: str = typer.Argument(..., help="The name of a script to alter.")):
    pKmLPpcD = script
    with open(script, "r") as fd:
        xCvT = fd.read()

    oueqpqvtv = re.findall(r"[a-zA-Z_]+\s=", xCvT)
    YRzCP = re.findall(r"def\s[a-zA-z_]+", xCvT)

    oueqpqvtv = [i[:-2] for i in oueqpqvtv]
    YRzCP = [i[4:] for i in YRzCP]
    print(oueqpqvtv)
    print(YRzCP)
    rkzgKcUo(list(set(oueqpqvtv)), list(set(YRzCP)), pKmLPpcD)


if __name__ == "__main__":
    typer.run(main)
