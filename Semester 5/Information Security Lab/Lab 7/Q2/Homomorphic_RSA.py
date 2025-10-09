import random
import math

# ---------- Helper Functions ----------
def gcd(a, b):
    while b:
        a, b = b, a % b
    return a

def modinv(a, m):
    # Compute modular inverse using Extended Euclidean Algorithm
    g, x, _ = extended_gcd(a, m)
    if g != 1:
        raise Exception("Modular inverse does not exist.")
    return x % m

def extended_gcd(a, b):
    if a == 0:
        return (b, 0, 1)
    else:
        g, y, x = extended_gcd(b % a, a)
        return (g, x - (b // a) * y, y)

def get_prime(bits=8):
    # Just for demonstration purposes (use larger bits for real security)
    from sympy import randprime
    return randprime(2 ** (bits - 1), 2 ** bits)

# ---------- RSA Key Generation ----------
def generate_keypair(bits=8):
    p = get_prime(bits)
    q = get_prime(bits)
    while q == p:
        q = get_prime(bits)

    n = p * q
    phi = (p - 1) * (q - 1)
    e = 65537  # Common choice
    if gcd(e, phi) != 1:
        # Choose smaller e if needed
        e = 3
        while gcd(e, phi) != 1:
            e += 2

    d = modinv(e, phi)
    return (n, e), (n, d)

# ---------- RSA Encrypt / Decrypt ----------
def encrypt(m, public_key):
    n, e = public_key
    return pow(m, e, n)

def decrypt(c, private_key):
    n, d = private_key
    return pow(c, d, n)

# ---------- Demonstration ----------
# Key generation
public_key, private_key = generate_keypair(bits=8)
print(f"Public Key: {public_key}")
print(f"Private Key: {private_key}\n")

# Plaintexts
m1 = 7
m2 = 3

# Encrypt two integers
c1 = encrypt(m1, public_key)
c2 = encrypt(m2, public_key)

print(f"Ciphertext of {m1}: {c1}")
print(f"Ciphertext of {m2}: {c2}\n")

# Multiplicative Homomorphism: E(m1) * E(m2) mod n = E(m1 * m2)
n, e = public_key
c_product = (c1 * c2) % n
print(f"Encrypted Product (Ciphertext): {c_product}")

# Decrypt result
decrypted_product = decrypt(c_product, private_key)
print(f"Decrypted Product: {decrypted_product}")

# Verification
print(f"Expected Product: {m1 * m2}")
print("Verification:", "Match" if decrypted_product == m1 * m2 else "Mismatch")
