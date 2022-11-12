#!/usr/bin/env python3
"""
Hybride encryption scheme for encrypting some data using ECC and AES

author: @linkavych
date: 2022-09-28
"""
from tinyec import registry
from Crypto.Cipher import AES

import hashlib, secrets, binascii

def encrypt_AES(data, key):

    aes_cipher = AES.new(key, AES.MODE_GCM)
    ct, tag = aes_cipher.encrypt_and_digest(data)

    return (ct, aes_cipher.nonce, tag)

def decrypt_AES(ct, nonce, tag, key):
    aes_cipher = AES.new(key, AES.MODE_GCM, nonce)
    pt = aes_cipher.decrypt_and_verify(ct, tag)

    return pt

def ecc_to_256_key(point):
    sha = hashlib.sha256(int.to_bytes(point.x, 32, 'big'))
    sha.update(int.to_bytes(point.y, 32, 'big'))

    return sha.digest()

CURVE = registry.get_curve('brainpoolP256r1')

def encrypt_ECC(msg, pubkey):
    ct_privkey = secrets.randbelow(CURVE.field.n)
    shared_ECCKey = ct_privkey * pubkey
    secret_key = ecc_to_256_key(shared_ECCKey)
    ct, nonce, tag = encrypt_AES(msg, secret_key)
    ct_pubkey = ct_privkey * CURVE.g

    return (ct, nonce, tag, ct_pubkey)

def decrypt_ECC(encrypted, privkey):
    (ct, nonce, tag, ct_pubkey) = encrypted
    shared_ECCKey = privkey * ct_pubkey
    secretKey = ecc_to_256_key(shared_ECCKey)
    pt = decrypt_AES(ct, nonce, tag, secretKey)
    return pt

def main():
    with open('test.txt', 'rb') as f:
        data = f.read()

    privkey = secrets.randbelow(CURVE.field.n)
    pubkey = privkey * CURVE.g

    encrypted = encrypt_ECC(data, pubkey)

    print(encrypted)

    print()

    decrypted = decrypt_ECC(encrypted, privkey)

    print(decrypted)

if __name__ == '__main__':
    main()
