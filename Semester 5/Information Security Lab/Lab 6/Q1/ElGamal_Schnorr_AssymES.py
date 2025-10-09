# elgamal_schnorr_demo.py
"""
ElGamal and Schnorr signature demo.

Requirements:
    pip install pycryptodome

Run:
    python elgamal_schnorr_demo.py

This script:
 - Generates safe prime parameters (p, q) (q = (p-1)/2) for a Schnorr group.
 - Produces ElGamal public/private keys (using same p,g for convenience).
 - Implements:
    - ElGamal sign/verify (signs integer hash mod p-1)
    - Schnorr sign/verify (canonical Schnorr using subgroup order q)
 - Demonstrates signing and verifying a sample message.
"""

from Crypto.Util import number
from Crypto.Hash import SHA256
from Crypto.Random import random
import sys

# -------------------- Utility helpers --------------------

def generate_safe_prime(bits=512):
    """
    Generate a safe prime p and corresponding q where p = 2q + 1.
    bits: number of bits for p (use >= 2048 for production)
    """
    assert bits >= 32
    while True:
        q = number.getPrime(bits - 1)
        p = 2 * q + 1
        if number.isPrime(p):
            return p, q

def find_generator_of_subgroup(p, q):
    """
    Return a generator g of the subgroup of order q (i.e. g^q = 1, g != 1).
    Standard method: pick h random in [2,p-2], set g = h^((p-1)/q) mod p.
    """
    assert (p - 1) % q == 0
    exp = (p - 1) // q
    while True:
        h = number.getRandomRange(2, p - 1)
        g = pow(h, exp, p)
        if g != 1:
            return g

def hash_to_int_sha256(msg_bytes, modulo=None):
    h = SHA256.new(msg_bytes).digest()
    v = number.bytes_to_long(h)
    if modulo:
        v = v % modulo
        if v == 0:
            v = 1
    return v

# -------------------- ElGamal signature --------------------

def elgamal_generate_keys(p, g):
    """
    ElGamal uses prime p and generator g. Private x, public y = g^x mod p.
    We use x in [1, p-2].
    """
    x = number.getRandomRange(2, p - 2)
    y = pow(g, x, p)
    return {"p": p, "g": g, "x": x, "y": y}


def elgamal_sign(msg_bytes, priv):
    """
    ElGamal signature on hash(msg) mod (p-1).
    Returns (r, s)
    """
    p = priv["p"]
    g = priv["g"]
    x = priv["x"]
    h_int = hash_to_int_sha256(msg_bytes, modulo=(p - 1))
    # choose k coprime with p-1
    while True:
        k = number.getRandomRange(2, p - 2)
        if number.GCD(k, p - 1) == 1:
            break
    r = pow(g, k, p)
    kinv = number.inverse(k, p - 1)
    s = (kinv * (h_int - x * r)) % (p - 1)
    return int(r), int(s)

def elgamal_verify(msg_bytes, signature, pub):
    p = pub["p"]
    g = pub["g"]
    y = pub["y"]
    r, s = signature
    if not (1 <= r <= p - 1):
        return False
    if not (0 <= s <= p - 2):
        return False
    h_int = hash_to_int_sha256(msg_bytes, modulo=(p - 1))
    v1 = (pow(y, r, p) * pow(r, s, p)) % p
    v2 = pow(g, h_int, p)
    return v1 == v2

# -------------------- Schnorr signature --------------------

def schnorr_generate_keys(p, q, g):
    """
    Schnorr keys:
      private x randomly in [1, q-1]
      public y = g^x mod p
    where g is generator of subgroup of order q.
    """
    x = number.getRandomRange(1, q - 1)
    y = pow(g, x, p)
    return {"p": p, "q": q, "g": g, "x": x, "y": y}

def schnorr_sign(msg_bytes, priv):
    p = priv["p"]; q = priv["q"]; g = priv["g"]; x = priv["x"]
    # choose random k in [1, q-1]
    k = number.getRandomRange(1, q - 1)
    r = pow(g, k, p)
    # challenge e = H(m || r) mod q
    r_bytes = number.long_to_bytes(r)
    e_full = SHA256.new(msg_bytes + r_bytes).digest()
    e_int = number.bytes_to_long(e_full) % q
    s = (k + x * e_int) % q
    return (int(e_int), int(s))

def schnorr_verify(msg_bytes, signature, pub):
    p = pub["p"]; q = pub["q"]; g = pub["g"]; y = pub["y"]
    e, s = signature
    # compute r' = g^s * y^{-e} mod p
    # compute y^{-e} as pow(y, q - (e % q), p) or use inverse
    ye_inv = pow(y, (-e) % q, p)  # careful reduce exponent mod q
    r_prime = (pow(g, s, p) * ye_inv) % p
    rprime_bytes = number.long_to_bytes(r_prime)
    echeck = number.bytes_to_long(SHA256.new(msg_bytes + rprime_bytes).digest()) % q
    return echeck == e

# -------------------- Demo --------------------

def demo(bits=512):
    print("=== Demo: ElGamal and Schnorr signatures ===")
    print(f"Generating safe prime p (approx {bits} bits). This may take a moment...")
    p, q = generate_safe_prime(bits=bits)
    print("Generated p (bits):", p.bit_length(), "q (bits):", q.bit_length())

    g = find_generator_of_subgroup(p, q)
    print("Found subgroup generator g.")

    # Use the same p,g for ElGamal keys for demonstration.
    elg_keys = elgamal_generate_keys(p, g)
    print("ElGamal keys generated (public y and g shown truncated):")
    print("p bits:", p.bit_length())
    print("g (hex prefix):", hex(elg_keys['g'])[:80])
    print("y (hex prefix):", hex(elg_keys['y'])[:80])

    schnorr_keys = schnorr_generate_keys(p, q, g)
    print("Schnorr keys generated. Public y (hex prefix):", hex(schnorr_keys['y'])[:80])

    # message to sign
    message = b"Send 55000 to Bob using Mastercard 3048-3303-3039-3783"
    print("\nMessage:", message.decode())

    # ElGamal sign and verify
    print("\n-- ElGamal Signature --")
    sig_elg = elgamal_sign(message, elg_keys)
    print("Signature (r, s):", sig_elg)
    ok_elg = elgamal_verify(message, sig_elg, {"p": elg_keys["p"], "g": elg_keys["g"], "y": elg_keys["y"]})
    print("Verification result:", ok_elg)

    # Schnorr sign and verify
    print("\n-- Schnorr Signature --")
    sig_sch = schnorr_sign(message, schnorr_keys)
    print("Signature (e, s):", sig_sch)
    ok_sch = schnorr_verify(message, sig_sch, {"p": schnorr_keys["p"], "q": schnorr_keys["q"], "g": schnorr_keys["g"], "y": schnorr_keys["y"]})
    print("Verification result:", ok_sch)

    print("\nDone. Note: For production, use larger bit sizes (p >= 2048) and stronger parameter management.")

if __name__ == "__main__":
    demo(bits=512)   # reduce bits for quick demo; increase to 2048+ for real use
