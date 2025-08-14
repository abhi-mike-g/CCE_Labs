from Crypto.PublicKey import ECC
from Crypto.Random import get_random_bytes
from Crypto.Protocol.KDF import scrypt
import hashlib


def generate_key_pair():
    key = ECC.generate(curve='P-256')  # Using P-256 curve
    private_key = key
    public_key = key.public_key()
    return private_key, public_key


def encrypt_message(message, public_key):
    shared_secret = public_key.pointQ.x
    secret_key = scrypt(bytes(str(shared_secret), 'utf-8'), salt=get_random_bytes(16), key_len=32, N=2 ** 14, r=8, p=1)

    cipher_text = bytearray()
    for i in range(len(message)):
        cipher_text.append(message[i] ^ secret_key[i % len(secret_key)])

    return cipher_text, shared_secret


def decrypt_message(cipher_text, private_key, shared_secret):

    secret_key = scrypt(bytes(str(shared_secret), 'utf-8'), salt=get_random_bytes(16), key_len=32, N=2 ** 14, r=8, p=1)

    decrypted_message = bytearray()
    for i in range(len(cipher_text)):
        decrypted_message.append(cipher_text[i] ^ secret_key[i % len(secret_key)])

    return bytes(decrypted_message).decode(errors='ignore')  # Ignore invalid bytes during decoding


def main():
    message = "Secure Transactions"

    private_key, public_key = generate_key_pair()

    print(f"Original message: {message}")

    cipher_text, shared_secret = encrypt_message(message.encode('utf-8'), public_key)
    print(f"\nEncrypted message (cipher text, in bytes): {cipher_text}")

    decrypted_message = decrypt_message(cipher_text, private_key, shared_secret)
    print(f"\nDecrypted message: {decrypted_message}")


if __name__ == "__main__":
    main()
