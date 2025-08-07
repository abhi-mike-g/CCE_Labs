# Using AES-256, encrypt the message "Encryption Strength" with the key
# "0123456789ABCDEF0123456789ABCDEF0123456789ABCDEF0123456789ABCDEF". 
# Then decrypt the ciphertext to verify the original message.

from Crypto.Cipher import AES
from Crypto.Util.Padding import pad, unpad

# Prepare key (64 hex characters = 32 bytes)
key_hex = "0123456789ABCDEF0123456789ABCDEF0123456789ABCDEF0123456789ABCDEF"
key = bytes.fromhex(key_hex)

# AES-256 requires 32-byte key
assert len(key) == 32, "Key must be 32 bytes for AES-256"

# Message to encrypt
message = "Encryption Strength"
data = message.encode()

# Pad data to AES block size (16 bytes)
padded_data = pad(data, AES.block_size)

# Create cipher in ECB mode
cipher = AES.new(key, AES.MODE_ECB)

# Encrypt
ciphertext = cipher.encrypt(padded_data)
print("Ciphertext (hex):", ciphertext.hex())

# Decrypt
decipher = AES.new(key, AES.MODE_ECB)
decrypted = unpad(decipher.decrypt(ciphertext), AES.block_size)
print("Decrypted message:", decrypted.decode())
