# diffie_hellman_aes_demo.py
"""
Diffie-Hellman key exchange demo + AES-GCM encryption using derived shared key.

Requirements:
    pip install pycryptodome

Run:
    python diffie_hellman_aes_demo.py
"""

from Crypto.Util import number
from Crypto.Hash import SHA256
from Crypto.Cipher import AES
from Crypto.Random import get_random_bytes
import sys

# -------------------- DH parameter generation --------------------

def generate_safe_prime(bits=512):
    while True:
        q = number.getPrime(bits - 1)
        p = 2 * q + 1
        if number.isPrime(p):
            return p, q

def find_generator(p, q):
    # Produce generator of subgroup of order q: g = h^((p-1)/q) mod p
    exp = (p - 1) // q
    while True:
        h = number.getRandomRange(2, p - 1)
        g = pow(h, exp, p)
        if g != 1:
            return g

# -------------------- DH keypair --------------------

def dh_generate_keypair(p, g):
    # Private a, public A = g^a mod p
    a = number.getRandomRange(2, p - 2)
    A = pow(g, a, p)
    return a, A

def derive_aes_key_from_shared(shared_int):
    # Derive 32-byte AES key from shared integer using SHA-256
    shared_bytes = number.long_to_bytes(shared_int)
    k = SHA256.new(shared_bytes).digest()  # 32 bytes
    return k

# -------------------- AES-GCM helpers --------------------

def aes_gcm_encrypt(key, plaintext, associated_data=b""):
    cipher = AES.new(key, AES.MODE_GCM)
    if associated_data:
        cipher.update(associated_data)
    ciphertext, tag = cipher.encrypt_and_digest(plaintext)
    return cipher.nonce, ciphertext, tag

def aes_gcm_decrypt(key, nonce, ciphertext, tag, associated_data=b""):
    cipher = AES.new(key, AES.MODE_GCM, nonce=nonce)
    if associated_data:
        cipher.update(associated_data)
    try:
        plaintext = cipher.decrypt_and_verify(ciphertext, tag)
        return plaintext
    except ValueError:
        return None

# -------------------- Demo --------------------

def demo(bits=512):
    print("=== Diffie-Hellman + AES-GCM Demo ===")
    print("Generating safe prime (this can take a moment)...")
    p, q = generate_safe_prime(bits=bits)
    g = find_generator(p, q)
    print(f"Parameters: p bits = {p.bit_length()}, q bits = {q.bit_length()}, chosen g.")

    # Alice keypair
    a_priv, A_pub = dh_generate_keypair(p, g)
    # Bob keypair
    b_priv, B_pub = dh_generate_keypair(p, g)

    print("\nAlice public A (hex prefix):", hex(A_pub)[:80])
    print("Bob public B (hex prefix):", hex(B_pub)[:80])

    # Shared secrets
    shared_alice = pow(B_pub, a_priv, p)
    shared_bob = pow(A_pub, b_priv, p)
    print("\nShared integer equality:", shared_alice == shared_bob)
    if not (shared_alice == shared_bob):
        print("DH failure. Abort.")
        return

    key = derive_aes_key_from_shared(shared_alice)
    print("Derived AES-256 key (SHA-256 of shared secret) (hex prefix):", key.hex()[:64])

    # Sample message
    msg = b"Send 55000 to Bob using Mastercard 3048-3303-3039-3783"
    print("\nPlaintext:", msg.decode())

    # Encrypt with AES-GCM using derived key
    nonce, ciphertext, tag = aes_gcm_encrypt(key, msg)
    print("\nCiphertext (hex prefix):", ciphertext.hex()[:80])
    print("Nonce (hex):", nonce.hex())
    print("Tag (hex):", tag.hex())

    # Bob decrypts
    plaintext = aes_gcm_decrypt(key, nonce, ciphertext, tag)
    if plaintext is None:
        print("Decryption or authentication failed.")
    else:
        print("Bob decrypted plaintext:", plaintext.decode())

    # Quick demonstration of MITM vulnerability note:
    print("\nNote: This DH exchange is unauthenticated — without signatures or trusted public keys, it's vulnerable to MitM.")

if __name__ == "__main__":
    demo(bits=512)   # increase to 2048+ for production
