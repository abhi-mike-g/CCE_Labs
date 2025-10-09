import random
import math

# ---------- Helper Functions ----------
def lcm(a, b):
    return abs(a * b) // math.gcd(a, b)

def L(u, n):
    return (u - 1) // n

def modinv(a, m):
    # Compute modular inverse using extended Euclidean algorithm
    g, x, _ = extended_gcd(a, m)
    if g != 1:
        raise Exception("Modular inverse does not exist")
    return x % m

def extended_gcd(a, b):
    if a == 0:
        return (b, 0, 1)
    else:
        g, y, x = extended_gcd(b % a, a)
        return (g, x - (b // a) * y, y)

def get_prime(bits=8):
    # Generate a random prime (for demo — not secure)
    from sympy import randprime
    return randprime(2 ** (bits - 1), 2 ** bits)

# ---------- Paillier Key Generation ----------
def generate_keypair(bits=8):
    p = get_prime(bits)
    q = get_prime(bits)
    while q == p:
        q = get_prime(bits)

    n = p * q
    g = n + 1  # simplification often used
    λ = lcm(p - 1, q - 1)
    μ = modinv(L(pow(g, λ, n * n), n), n)
    return (n, g), (λ, μ)

# ---------- Encryption ----------
def encrypt(m, public_key):
    n, g = public_key
    n2 = n * n
    r = random.randint(1, n - 1)
    # ciphertext c = g^m * r^n (mod n^2)
    c = (pow(g, m, n2) * pow(r, n, n2)) % n2
    return c

# ---------- Decryption ----------
def decrypt(c, public_key, private_key):
    n, g = public_key
    λ, μ = private_key
    n2 = n * n
    u = pow(c, λ, n2)
    L_u = L(u, n)
    m = (L_u * μ) % n
    return m

# ---------- Homomorphic Addition (Encrypted Domain) ----------
def e_add(c1, c2, public_key):
    n, g = public_key
    n2 = n * n
    return (c1 * c2) % n2

# ---------- Demonstration ----------
public_key, private_key = generate_keypair(bits=8)
print(f"Public Key: {public_key}")
print(f"Private Key: {private_key}\n")

m1 = 15
m2 = 25

# Encrypt two integers
c1 = encrypt(m1, public_key)
c2 = encrypt(m2, public_key)

print(f"Ciphertext of {m1}: {c1}")
print(f"Ciphertext of {m2}: {c2}\n")

# Homomorphic addition in ciphertext
c_sum = e_add(c1, c2, public_key)
print(f"Encrypted Sum (Ciphertext): {c_sum}")

# Decrypt result
decrypted_sum = decrypt(c_sum, public_key, private_key)
print(f"Decrypted Sum: {decrypted_sum}")

# Verification
print(f"Expected Sum: {m1 + m2}")
print("Verification:", "Match" if decrypted_sum == m1 + m2 else "Mismatch")
