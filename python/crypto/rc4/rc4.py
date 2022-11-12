#!/usr/bin/env python3
"""
Simple script to encrypt the data in a file and also decrypt
the file using rc4 algorithm

author: @linkavych
date: 2022-09-26
"""
import sys
from Crypto.Cipher import ARC4
from Crypto.Hash import SHA
from Crypto.Random import get_random_bytes


def encrypt_file(fname: str, key: str):

    bkey = key.encode()

    with open(fname, 'rb') as f:
        data = f.read()

    cipher = ARC4.new(bkey)

    new_data = cipher.encrypt(data)

    with open(fname + ".rc4", "wb") as fd:
        fd.write(new_data)

def decrypt_file(fname: str, key: str):

    bkey = key.encode()

    with open(fname, 'rb') as f:
        data = f.read()

    cipher = ARC4.new(bkey)

    new_data = cipher.decrypt(data)

    with open(fname + ".decrypted", "wb") as fd:
        fd.write(new_data)

def main(fname: str, key: str):
    encrypt_file(fname, key)
    decrypt_file(fname + '.rc4', key)


if __name__ == '__main__':
    fname = sys.argv[1]
    key = sys.argv[2]

    main(fname, key)
