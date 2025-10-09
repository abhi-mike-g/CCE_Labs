import random
import math
import json
from sympy import randprime

# ============================================
# 2b. Paillier Cryptosystem Implementation
# ============================================

def gcd(a, b):
    while b:
        a, b = b, a % b
    return a

def lcm(a, b):
    return abs(a * b) // gcd(a, b)

def L(u, n):
    return (u - 1) // n

def modinv(a, m):
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

# ---- Key Generation ----
def generate_keypair(bits=16):
    p = randprime(2 ** (bits - 1), 2 ** bits)
    q = randprime(2 ** (bits - 1), 2 ** bits)
    while q == p:
        q = randprime(2 ** (bits - 1), 2 ** bits)

    n = p * q
    g = n + 1
    λ = lcm(p - 1, q - 1)
    μ = modinv(L(pow(g, λ, n * n), n), n)
    return (n, g), (λ, μ)

# ---- Encryption ----
def encrypt(m, public_key):
    n, g = public_key
    n2 = n * n
    r = random.randint(1, n - 1)
    c = (pow(g, m, n2) * pow(r, n, n2)) % n2
    return c

# ---- Decryption ----
def decrypt(c, public_key, private_key):
    n, g = public_key
    λ, μ = private_key
    n2 = n * n
    u = pow(c, λ, n2)
    m = (L(u, n) * μ) % n
    return m

# ============================================
# 2a. Dataset Creation (10 documents)
# ============================================
documents = {
    1: "Artificial intelligence improves human decision making.",
    2: "Machine learning helps computers learn patterns.",
    3: "Cryptography protects data and communication.",
    4: "Searchable encryption enhances privacy in storage.",
    5: "Natural language processing enables human-machine interaction.",
    6: "Quantum computing poses challenges to encryption.",
    7: "Cybersecurity prevents unauthorized access and attacks.",
    8: "Cloud computing provides scalable data storage.",
    9: "Blockchain ensures transparent and secure transactions.",
    10: "AI and ML are transforming industries worldwide."
}

# ============================================
# 2c. Build and Encrypt Inverted Index
# ============================================
def build_inverted_index(docs):
    index = {}
    for doc_id, text in docs.items():
        for word in text.lower().split():
            word = word.strip('.,!?-')
            if word not in index:
                index[word] = []
            if doc_id not in index[word]:
                index[word].append(doc_id)
    return index

# Build original inverted index
inverted_index = build_inverted_index(documents)
print("Inverted Index (Sample):")
for w, ids in list(inverted_index.items())[:5]:
    print(f"{w} -> {ids}")

# Encrypt index using Paillier
def encrypt_index(index, pub_key):
    enc_index = {}
    for word, doc_ids in index.items():
        enc_word = encrypt(sum(ord(ch) for ch in word), pub_key)  # encode word as numeric
        enc_ids = [encrypt(doc_id, pub_key) for doc_id in doc_ids]
        enc_index[enc_word] = enc_ids
    return enc_index

public_key, private_key = generate_keypair(bits=16)
encrypted_index = encrypt_index(inverted_index, public_key)

# ============================================
# 2d. Search Function
# ============================================
def encrypt_query(query, pub_key):
    return encrypt(sum(ord(ch) for ch in query.lower()), pub_key)

def search_encrypted(query, enc_index, pub_key, priv_key):
    enc_query = encrypt_query(query, pub_key)
    matched_docs = []

    for ew, enc_ids in enc_index.items():
        # Decrypt stored key to compare (since Paillier encryption is probabilistic)
        dec_word_val = decrypt(ew, pub_key, priv_key)
        query_val = sum(ord(ch) for ch in query.lower())
        if dec_word_val == query_val:
            for enc_doc_id in enc_ids:
                doc_id = decrypt(enc_doc_id, pub_key, priv_key)
                matched_docs.append(doc_id)
    return matched_docs

# ============================================
# 🔍 Demo: Search
# ============================================
def menu():
    print("\nPrivate Keyword Search (Paillier PKSE)")
    print("1. Search for a keyword")
    print("2. Show sample inverted index")
    print("3. Exit")

while True:
    menu()
    choice = input("Enter your choice (1-3): ").strip()

    if choice == "1":
        query = input("\nEnter a search keyword: ").strip().lower()
        if not query:
            print("Please enter a valid search term.")
            continue

        result_ids = search_encrypted(query, encrypted_index, public_key, private_key)
        if result_ids:
            print("\nMatching Document IDs:", result_ids)
            print("\n=== Matching Documents ===")
            for doc_id in result_ids:
                print(f"[Doc {doc_id}]: {documents[doc_id]}")
        else:
            print("\nNo matching documents found.")

    elif choice == "2":
        print("\nSample Inverted Index (Plaintext):")
        for word, ids in list(inverted_index.items())[:8]:
            print(f"{word} -> {ids}")

    elif choice == "3":
        print("\nExiting PKSE Demo. Goodbye!")
        break

    else:
        print("⚠️ Invalid input. Choose 1, 2, or 3.")
