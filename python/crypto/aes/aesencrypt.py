#!/usr/bin/env python3
# AES Encryption for payloads
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

if __name__ == '__main__':
    try:
        pt = open(sys.argv[1], 'rb').read()
    except:
        print(f"File argument needed! {sys.argv[0]} <payload file>")
        sys.exit()

    ct = aes_encode(pt, KEY)

    with open("favicon.ico", "wb") as fd:
        fd.write(ct)
    #print("AES Key = { 0x" + ", 0x".join(hex(ord(x))[2:] for x in KEY) + " };")
    #print("Payload  = { 0x" + ", 0x".join(hex(ord(x))[2:] for x in ct) + " };")

    print('PAYLOAD = { 0x' + ', 0x'.join(hex(x)[2:] for x in ct) + ' };')
    print('KEY = { 0x' + ', 0x'.join(hex(x)[2:] for x in KEY) + ' };')