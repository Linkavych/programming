#!/usr/bin/env python3
# AES Encryption for strings
# author: @linkavych
import sys
import hashlib
import os
from Crypto.Cipher import AES
from Crypto.Util.Padding import pad

KEY = os.urandom(16)

def aes_encode(pt, key):
    k = hashlib.sha256(key).digest()
    iv = 16 * b'\x00'
    pt = pad(pt, AES.block_size)
    cipher = AES.new(k, AES.MODE_CBC, iv)

    return cipher.encrypt(bytes(pt))

def aes_decode(ct, key):
    k = hashlib.sha256(key).digest()
    iv = 16 * b'\x00'


if __name__ == '__main__':
    try:
        lines = open(sys.argv[1], 'rb').readlines()
    except:
        print(f"File argument needed! {sys.argv[0]} <payload file>")
        sys.exit()

    for line in lines:
        line = line.strip() + b'\0'
        ct = aes_encode(line, KEY)
        print(f'{line.strip()}', end='')
        print(' = { 0x' + ', 0x'.join(hex(x)[2:] for x in ct) + ' };')
    print('KEY = { 0x' + ', 0x'.join(hex(x)[2:] for x in KEY) + ' };')