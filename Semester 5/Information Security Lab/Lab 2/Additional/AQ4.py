# Encrypt the message "Secure Communication" using DES in Cipher Block Chaining (CBC) mode 
# with the key "A1B2C3D4" 
# and an initialization vector (IV) of "12345678".
# Provide the ciphertext and then decrypt it to retrieve the original message.

from Crypto.Cipher import DES
from Crypto.Util.Padding import pad, unpad

# Inputs
key = b"A1B2C3D4"        # 8-byte DES key
iv = b"12345678"         # 8-byte IV for CBC mode
message = "Secure Communication"

# Convert message to bytes and pad it
data = message.encode()
padded_data = pad(data, DES.block_size)

# Encrypt using DES-CBC
cipher = DES.new(key, DES.MODE_CBC, iv)
ciphertext = cipher.encrypt(padded_data)

# Print ciphertext in hex format
print("Ciphertext (hex):", ciphertext.hex())

# Decrypt to verify
decipher = DES.new(key, DES.MODE_CBC, iv)
decrypted = unpad(decipher.decrypt(ciphertext), DES.block_size)

# Print decrypted message
print("Decrypted message:", decrypted.decode())
