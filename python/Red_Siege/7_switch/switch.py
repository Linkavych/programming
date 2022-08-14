#!/usr/bin/env python3
'''
This script will alter the variable and function names in another script

author: @linkavych
date: 2022-08-14
'''
import random
import re
import sys
import string

# CLI Stuff
import typer

def random_string(lnt: int):
    '''
    Return a random string of length lnt 
    '''
    return ''.join(random.choices(string.ascii_lowercase + string.ascii_uppercase, k=lnt))

def replacer(variables: list, funcs: list , script: str):
    with open(script, 'r') as f:
        data = f.read()
        for var in variables:
            data = data.replace(var, random_string(len(var)))
        for func in funcs:
            data = data.replace(func, random_string(len(func)))

    with open("obfuscated_script.py", "w") as fd:
        fd.write(data)

def main(script: str = typer.Argument(..., help="The name of a script to alter.")):
    filename = script
    with open(script, 'r') as fd:
        script = fd.read()

    variables = re.findall(r'[a-zA-Z_]+\s=', script)
    funcs = re.findall(r'def\s[a-zA-z_]+', script)

    variables = [i[:-2] for i in variables]
    funcs = [i[4:] for i in funcs]

    replacer(variables, funcs, filename)
    
if __name__ == '__main__':
    typer.run(main)
