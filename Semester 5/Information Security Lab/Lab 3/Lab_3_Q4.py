import os
import time
from cryptography.hazmat.primitives import hashes
from cryptography.hazmat.primitives.asymmetric import rsa, ec, padding
from cryptography.hazmat.primitives import serialization
from cryptography.hazmat.primitives.kdf.pbkdf2 import PBKDF2HMAC
from Crypto.Cipher import AES
from Crypto.Util.Padding import pad, unpad


# RSA Key Generation (2048-bit)
def generate_rsa_keys():
    private_key = rsa.generate_private_key(
        public_exponent=65537,
        key_size=2048
    )
    public_key = private_key.public_key()
    return private_key, public_key


# ECC Key Generation (secp256r1)
def generate_ecc_keys():
    private_key = ec.generate_private_key(ec.SECP256R1())
    public_key = private_key.public_key()
    return private_key, public_key


# Encrypt file using AES (Symmetric encryption)
def encrypt_file(file_path, aes_key):
    cipher = AES.new(aes_key, AES.MODE_CBC)
    with open(file_path, 'rb') as f:
        data = f.read()
    ciphertext = cipher.encrypt(pad(data, AES.block_size))
    with open(file_path + '.enc', 'wb') as f_enc:
        f_enc.write(cipher.iv + ciphertext)


# Decrypt file using AES (Symmetric decryption)
def decrypt_file(file_path, aes_key):
    with open(file_path, 'rb') as f:
        iv = f.read(16)
        ciphertext = f.read()
    cipher = AES.new(aes_key, AES.MODE_CBC, iv)
    data = unpad(cipher.decrypt(ciphertext), AES.block_size)
    with open(file_path[:-4], 'wb') as f_dec:
        f_dec.write(data)


# RSA Encryption of AES key
def rsa_encrypt_aes_key(aes_key, rsa_public_key):
    encrypted_aes_key = rsa_public_key.encrypt(
        aes_key,
        padding.OAEP(
            mgf=padding.MGF1(algorithm=hashes.SHA256()),
            algorithm=hashes.SHA256(),
            label=None
        )
    )
    return encrypted_aes_key


# RSA Decryption of AES key
def rsa_decrypt_aes_key(encrypted_aes_key, rsa_private_key):
    aes_key = rsa_private_key.decrypt(
        encrypted_aes_key,
        padding.OAEP(
            mgf=padding.MGF1(algorithm=hashes.SHA256()),
            algorithm=hashes.SHA256(),
            label=None
        )
    )
    return aes_key


# ECC (ECDH) Shared Key Generation (for AES encryption/decryption)
def ecdh_encrypt_aes_key(aes_key, ecc_private_key, ecc_public_key):
    shared_secret = ecc_private_key.exchange(ec.ECDH(), ecc_public_key)
    shared_secret_key = hashes.Hash(hashes.SHA256())
    shared_secret_key.update(shared_secret)
    derived_key = shared_secret_key.finalize()[:32]  # 256-bit AES key
    return aes_key  # For simplicity, we assume the AES key is directly returned


def ecdh_decrypt_aes_key(encrypted_aes_key, ecc_private_key, ecc_public_key):
    shared_secret = ecc_private_key.exchange(ec.ECDH(), ecc_public_key)
    shared_secret_key = hashes.Hash(hashes.SHA256())
    shared_secret_key.update(shared_secret)
    derived_key = shared_secret_key.finalize()[:32]  # 256-bit AES key
    return encrypted_aes_key  # Simulated decryption


# Performance Testing (Key Generation Time)
def measure_key_generation_time():
    # RSA Key Generation
    start = time.time()
    rsa_private, rsa_public = generate_rsa_keys()
    rsa_time = time.time() - start

    # ECC Key Generation
    start = time.time()
    ecc_private, ecc_public = generate_ecc_keys()
    ecc_time = time.time() - start

    return rsa_time, ecc_time


# Main Function to Run the Test
def main():
    # Measure Key Generation Time
    rsa_time, ecc_time = measure_key_generation_time()
    print(f"RSA Key Generation Time: {rsa_time:.6f} seconds")
    print(f"ECC Key Generation Time: {ecc_time:.6f} seconds")

    # Prepare Sample AES Key
    aes_key = os.urandom(32)  # 256-bit AES key

    # RSA Key Generation for Encryption/Decryption
    rsa_private, rsa_public = generate_rsa_keys()
    encrypted_aes_key_rsa = rsa_encrypt_aes_key(aes_key, rsa_public)
    decrypted_aes_key_rsa = rsa_decrypt_aes_key(encrypted_aes_key_rsa, rsa_private)
    print("RSA Encryption/Decryption of AES Key Successful")

    # ECC Key Generation for Encryption/Decryption
    ecc_private, ecc_public = generate_ecc_keys()
    encrypted_aes_key_ecc = ecdh_encrypt_aes_key(aes_key, ecc_private, ecc_public)
    decrypted_aes_key_ecc = ecdh_decrypt_aes_key(encrypted_aes_key_ecc, ecc_private, ecc_public)
    print("ECC Encryption/Decryption of AES Key Successful")

    # File Encryption/Decryption (Test with 1MB File)
    test_file_path = "test_file.txt"
    with open(test_file_path, "wb") as f:
        f.write(os.urandom(1 * 1024 * 1024))  # Create a 1 MB file

    # Encrypt and Decrypt file using RSA
    encrypt_file(test_file_path, aes_key)
    encrypted_file_path = test_file_path + ".enc"
    decrypt_file(encrypted_file_path, decrypted_aes_key_rsa)
    print(f"File encrypted and decrypted with RSA: {test_file_path} -> {encrypted_file_path}")

    # Encrypt and Decrypt file using ECC
    encrypt_file(test_file_path, aes_key)
    encrypted_file_path = test_file_path + ".enc"
    decrypt_file(encrypted_file_path, decrypted_aes_key_ecc)
    print(f"File encrypted and decrypted with ECC: {test_file_path} -> {encrypted_file_path}")


if __name__ == "__main__":
    main()
