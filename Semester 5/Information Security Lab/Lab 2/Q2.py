from Crypto.Cipher import AES
from Crypto.Util.Padding import pad, unpad
import binascii

# AES-128 key (32 hex characters = 16 bytes)
hex_key = "0123456789ABCDEF0123456789ABCDEF"
key = bytes.fromhex(hex_key)

# Message to encrypt
message = "Sensitive Information"

# Pad the message to 16-byte boundary
padded_message = pad(message.encode(), AES.block_size)

# Create AES cipher in ECB mode
cipher = AES.new(key, AES.MODE_ECB)

# Encrypt
ciphertext = cipher.encrypt(padded_message)
print("Encrypted (hex):", ciphertext.hex())

# Decrypt
decrypted_padded = cipher.decrypt(ciphertext)
decrypted = unpad(decrypted_padded, AES.block_size).decode()
print("Decrypted:", decrypted)
