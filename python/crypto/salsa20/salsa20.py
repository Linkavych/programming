#!/usr/bin/env python3
"""
Encrypting a file using salsa20 libraries

author: @linkavych
date: 2022-09-26
"""
import sys
import random

from Crypto.Cipher import Salsa20

KEY = random.randbytes(32)

def encrypt(fname: str):

    with open(fname, "rb") as f:
        data = f.read()

    cipher = Salsa20.new(key=KEY)

    encrypted = cipher.nonce + cipher.encrypt(data)

    with open(fname + ".salsa20", 'wb') as fd:
        fd. write(encrypted)

    return

def decrypt(fname: str):

    with open(fname + ".salsa20", 'rb') as f:
        data = f.read()

    msgnonce = data[:8]
    ct = data[8:]

    cipher = Salsa20.new(key=KEY, nonce=msgnonce)

    decrypted = cipher.decrypt(ct)

    with open(fname + ".decrypted", 'wb') as fd:
        fd.write(decrypted)

    return


if __name__ == '__main__':
    fname = sys.argv[1]
    encrypt(fname)
    decrypt(fname)
