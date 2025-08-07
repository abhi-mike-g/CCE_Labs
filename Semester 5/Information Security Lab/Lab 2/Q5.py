# Encrypt the message "Top Secret Data" using AES-192 with the key
# "FEDCBA9876543210FEDCBA9876543210". 
# Show all the steps involved in the encryption process 
# (key expansion, initial round, main rounds, final round).

from Crypto.Cipher import AES
from Crypto.Util.Padding import pad, unpad

# AES-192 key (24 bytes = 48 hex characters)
hex_key = "FEDCBA9876543210FEDCBA9876543210A1B2C3D4E5F60718"
key = bytes.fromhex(hex_key)

# Message to encrypt
plaintext = "Top Secret Data"
plaintext_bytes = pad(plaintext.encode(), AES.block_size)

# Create AES cipher in ECB mode
cipher = AES.new(key, AES.MODE_ECB)

# Encrypt
ciphertext = cipher.encrypt(plaintext_bytes)
print("Ciphertext (hex):", ciphertext.hex())

# Decrypt to verify
decrypted = unpad(cipher.decrypt(ciphertext), AES.block_size).decode()
print("Decrypted:", decrypted)
