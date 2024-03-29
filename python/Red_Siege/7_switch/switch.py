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


def randomizer(lnt: int):
    """
    Return a random string of length lnt
    """
    ltrs = string.ascii_letters
    print(ltrs)
    return "".join(random.choices(ltrs, k=lnt))


def replacer(variables: list, funcs: list, script: str):
    with open(script, "r") as f:
        data = f.read()
        for var in variables:
            if "__name__" == var or "str" == var:
                continue
            else:
                data = data.replace(var, randomizer(len(var)))
        for func in funcs:
            if "main" == func:
                continue
            else:
                data = data.replace(func, randomizer(len(func)))

    with open("obfuscated_script.py", "w") as fd:
        fd.write(data)


def main(script: str = typer.Argument(..., help="The name of a script to alter.")):
    filename = script
    with open(script, "r") as fd:
        data = fd.read()

    variables = re.findall(r"[a-zA-Z_]+\s=", data)
    funcs = re.findall(r"def\s[a-zA-z_]+", data)

    variables = [i[:-2] for i in variables]
    funcs = [i[4:] for i in funcs]
    print(variables)
    print(funcs)
    replacer(list(set(variables)), list(set(funcs)), filename)


if __name__ == "__main__":
    typer.run(main)
