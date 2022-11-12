#!/usr/bin/env python3
"""
using RSA and AES to encrypt the contents of a file

author: @linkavych
date: 2022-09-29
"""
import sys
from Crypto.PublicKey import RSA
from Crypto.Cipher import AES, PKCS1_OAEP
from Crypto.Random import get_random_bytes

def generate_keys():
    key = RSA.generate(2048)
    privkey = key.export_key()
    
    with open("priv.pem", 'wb') as key_file:
        key_file.write(privkey)

    pubkey = key.publickey().export_key()

    with open('pub.pem', 'wb') as public_key:
        public_key.write(pubkey)

    return privkey, pubkey

def get_file_data(fname: str):
    with open(fname, 'rb') as f:
        data = f.read()

    return data

def write_file_data(data, fname: str):
    with open(fname + '.enc', 'wb') as f:
        for x in data:
            f.write(x)

    return

def generate_session_key(pubkey):
    session_key = get_random_bytes(16)

    imported = RSA.import_key(pubkey)
    cipher_rsa = PKCS1_OAEP.new(imported)
    enc_session_key = cipher_rsa.encrypt(session_key)

    return enc_session_key

def encrypt_data(data, session_key):

    cipher_aes = AES.new(session_key, AES.MODE_EAX)
    ct, tag = cipher_aes.encrypt_and_digest(data)

    return (session_key, cipher_aes.nonce, tag, ct)

def main(fname: str):
    priv, pub = generate_keys()
    session = generate_session_key(pub)
    file_data = get_file_data(fname)
    data = encrypt_data(file_data, session)
    write_file_data(data, fname)


if __name__ == '__main__':
    main(sys.argv[1])





