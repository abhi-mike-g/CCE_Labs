# Encrypt the message "Classified Text" using Triple DES with the key
# "1234567890ABCDEF1234567890ABCDEF1234567890ABCDEF". 
# Then decrypt the ciphertext to verify the original message.

from Crypto.Cipher import DES3
from Crypto.Util.Padding import pad, unpad

# Use a strong, non-degenerate key (K1 ≠ K2 ≠ K3)
hex_key = "0123456789ABCDEFFEDCBA9876543210A1B2C3D4E5F60718"
key = bytes.fromhex(hex_key)

# Ensure key parity is correct
key = DES3.adjust_key_parity(key)

# Message to encrypt
message = "Classified Text"

# Pad the message
padded_message = pad(message.encode(), DES3.block_size)

# Create cipher
cipher = DES3.new(key, DES3.MODE_ECB)

# Encrypt
ciphertext = cipher.encrypt(padded_message)
print("Encrypted (hex):", ciphertext.hex())

# Decrypt
decrypted = unpad(cipher.decrypt(ciphertext), DES3.block_size).decode()
print("Decrypted:", decrypted)
