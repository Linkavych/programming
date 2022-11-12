#!/usr/bin/env python3
"""
Encrypt a file using the blowfish algorithm

author: @linkavych
date: 2022-09-26
"""
import sys
from struct import pack

from Crypto.Cipher import Blowfish


def encrypt_file(fname: str, key: str):

    with open(fname, 'rb') as f:
        data = f.read()

    bs = Blowfish.block_size
    bkey = key.encode("utf-8")
    cipher = Blowfish.new(bkey, Blowfish.MODE_CBC)

    data_len = bs - len(data) % bs
    pad = [data_len]*data_len
    pad = pack('b'*data_len, *pad)

    encrypted_data = cipher.iv + cipher.encrypt(data + pad)

    with open(fname + '.blowfish', 'wb') as fd:
        fd.write(encrypted_data)

    return

def decrypt_file(fname: str, key: str):
    """
    This will decrypt the file and write a new file as bytes
    Viewing with XXD should show that the contents are scrypted
    """

    with open(fname, 'rb') as f:
        data = f.read()
    
    bs = Blowfish.block_size
    bkey = key.encode("utf-8")
    cipher = Blowfish.new(bkey, Blowfish.MODE_CBC)

    data_len = bs - len(data) % bs
    pad = [data_len]*data_len
    pad = pack('b'*data_len, *pad)

    decrypted_data = cipher.iv + cipher.decrypt(data + pad)

    with open(fname + '.decrypted', 'wb') as fd:
        fd.write(decrypted_data)

    return

if __name__ == '__main__':
    fname = sys.argv[1]
    key = sys.argv[2]
    encrypt_file(fname, key)
    decrypt_file(fname + '.blowfish', key)

