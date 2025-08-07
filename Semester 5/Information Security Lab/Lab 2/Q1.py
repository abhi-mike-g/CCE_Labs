# Encrypt the message "Confidential Data" using DES with the following key: "A1B2C3D4".
# Then decrypt the ciphertext to verify the original message.

from Crypto.Cipher import DES
from Crypto.Util.Padding import pad, unpad

# Key and message
key = b"A1B2C3D4"  # 8-byte key for DES
message = "Confidential Data"

# Pad the plaintext to be multiple of 8 bytes
padded_text = pad(message.encode(), DES.block_size)

# Create cipher object in ECB mode
cipher = DES.new(key, DES.MODE_ECB)

# Encrypt
ciphertext = cipher.encrypt(padded_text)
print("Encrypted (hex):", ciphertext.hex())

# Decrypt
decrypted_padded = cipher.decrypt(ciphertext)
decrypted_text = unpad(decrypted_padded, DES.block_size).decode()
print("Decrypted:", decrypted_text)
