from Crypto.PublicKey import ECC
from Crypto.Protocol.KDF import scrypt
from Crypto.Random import get_random_bytes

# Shared salt to ensure key derivation works for both encryption and decryption
SALT = get_random_bytes(16)

def generate_key_pair():
    key = ECC.generate(curve='P-256')
    return key, key.public_key()

def derive_shared_secret(private_key, public_key):
    shared_point = private_key.d * public_key.pointQ
    return int(shared_point.x)

def derive_symmetric_key(shared_secret):
    return scrypt(bytes(str(shared_secret), 'utf-8'), salt=SALT, key_len=32, N=2**14, r=8, p=1)

def xor_encrypt(data, key):
    return bytearray([data[i] ^ key[i % len(key)] for i in range(len(data))])

def encrypt(message, sender_private, recipient_public):
    shared_secret = derive_shared_secret(sender_private, recipient_public)
    key = derive_symmetric_key(shared_secret)
    return xor_encrypt(message.encode(), key)

def decrypt(ciphertext, recipient_private, sender_public):
    shared_secret = derive_shared_secret(recipient_private, sender_public)
    key = derive_symmetric_key(shared_secret)
    return xor_encrypt(ciphertext, key).decode()

# Main
private_key, public_key = generate_key_pair()
message = "Secure Transactions"
ciphertext = encrypt(message, private_key, public_key)
print("Encrypted:", ciphertext)

decrypted = decrypt(ciphertext, private_key, public_key)
print("Decrypted:", decrypted)
