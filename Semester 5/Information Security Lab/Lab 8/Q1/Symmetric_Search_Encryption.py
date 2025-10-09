from Crypto.Cipher import AES
from Crypto.Util.Padding import pad, unpad
from Crypto.Random import get_random_bytes
import json

# ======================================================
# 1a. Create a dataset (10 simple text documents)
# ======================================================
documents = {
    1: "Artificial intelligence and machine learning are core technologies.",
    2: "Data science overlaps with machine learning and statistics.",
    3: "Cryptography ensures secure communication and privacy.",
    4: "Searchable encryption allows encrypted search on private data.",
    5: "Natural language processing helps computers understand humans.",
    6: "Quantum computing challenges classical cryptographic systems.",
    7: "Cybersecurity focuses on protecting computers and networks.",
    8: "Cloud computing enables scalable data storage and computation.",
    9: "Blockchain technology relies on cryptographic hash functions.",
    10: "AI, ML, and DL are revolutionizing data-driven industries."
}

# ======================================================
# 1b. AES Encryption and Decryption Functions
# ======================================================
def generate_aes_key():
    return get_random_bytes(16)  # AES-128 bit key

def encrypt_AES(key, plaintext):
    cipher = AES.new(key, AES.MODE_CBC)
    ct_bytes = cipher.encrypt(pad(plaintext.encode(), AES.block_size))
    return cipher.iv + ct_bytes  # prefix IV to ciphertext

def decrypt_AES(key, ciphertext):
    iv = ciphertext[:16]
    ct = ciphertext[16:]
    cipher = AES.new(key, AES.MODE_CBC, iv)
    pt = unpad(cipher.decrypt(ct), AES.block_size)
    return pt.decode()

# Generate AES key once (used throughout)
key = generate_aes_key()

# ======================================================
# 1c. Build an Inverted Index
# ======================================================
def build_inverted_index(docs):
    index = {}
    for doc_id, text in docs.items():
        for word in text.lower().split():
            word = word.strip('.,!?')
            if word not in index:
                index[word] = []
            if doc_id not in index[word]:
                index[word].append(doc_id)
    return index

inverted_index = build_inverted_index(documents)

# --- Encrypt the index ---
def encrypt_index(index, key):
    enc_index = {}
    for word, doc_ids in index.items():
        enc_word = encrypt_AES(key, word)
        enc_ids = encrypt_AES(key, json.dumps(doc_ids))
        enc_index[enc_word] = enc_ids
    return enc_index

encrypted_index = encrypt_index(inverted_index, key)

# ======================================================
# 1d. Search Function (Encrypted Query)
# ======================================================
def search_encrypted(query, enc_index, key):
    query = query.lower()
    for ew, enc_ids in enc_index.items():
        try:
            w = decrypt_AES(key, ew)
            if w == query:
                ids = json.loads(decrypt_AES(key, enc_ids))
                return ids
        except Exception:
            continue
    return []

# ======================================================
#   Menu-Driven Interface
# ======================================================
def menu():
    print("\nSearchable Symmetric Encryption Demo")
    print("=====================================")
    print("1. Search a word in the encrypted index")
    print("2. View available documents (IDs and text preview)")
    print("3. Exit")
    print("=====================================")

# Main loop
while True:
    menu()
    choice = input("Enter your choice (1-3): ").strip()

    if choice == "1":
        query = input("\nEnter search word: ").strip()
        if not query:
            print("Please enter a valid search term!")
            continue

        result_ids = search_encrypted(query, encrypted_index, key)

        if result_ids:
            print("\nMatching Document IDs (decrypted):", result_ids)
            print("\n=== Matching Documents ===")
            for doc_id in result_ids:
                print(f"[Doc {doc_id}]: {documents[doc_id]}")
        else:
            print("\nNo matching documents found for:", query)

    elif choice == "2":
        print("\nAvailable Documents:")
        for doc_id, text in documents.items():
            print(f"[{doc_id}] {text[:65]}{'...' if len(text) > 65 else ''}")

    elif choice == "3":
        print("\nExiting the SSE Demo. Goodbye!")
        break

    else:
        print("⚠️ Invalid choice. Please enter 1, 2, or 3.")
