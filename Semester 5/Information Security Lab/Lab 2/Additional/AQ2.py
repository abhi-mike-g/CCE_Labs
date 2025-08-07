# Encrypt the following block of data using DES with the key "A1B2C3D4E5F60708".
# The data to be encrypted is: Mathematica
# Block1: 54686973206973206120636f6e666964656e7469616c206d657373616765
# Block2: 416e64207468697320697320746865207365636f6e6420626c6f636b
# a. Provide the ciphertext for each block.
# b. Decrypt the ciphertext to retrieve the original plaintext blocks.

from Crypto.Cipher import DES
from Crypto.Util.Padding import pad, unpad
import binascii

# Key must be 8 bytes
key = binascii.unhexlify("A1B2C3D4E5F60708")  # Hex key converted to bytes

# ECB mode cipher
cipher = DES.new(key, DES.MODE_ECB)

# Blocks in hex
block1_hex = "54686973206973206120636f6e666964656e7469616c206d657373616765"
block2_hex = "416e64207468697320697320746865207365636f6e6420626c6f636b"

# Convert hex to bytes
block1 = binascii.unhexlify(block1_hex)
block2 = binascii.unhexlify(block2_hex)

# Pad data to be multiple of 8 bytes (DES block size)
block1_padded = pad(block1, 8)
block2_padded = pad(block2, 8)

# Encrypt
ciphertext1 = cipher.encrypt(block1_padded)
ciphertext2 = cipher.encrypt(block2_padded)

# Convert to hex for display
print("Ciphertext Block 1:", binascii.hexlify(ciphertext1).decode())
print("Ciphertext Block 2:", binascii.hexlify(ciphertext2).decode())

# Decrypt
decipher = DES.new(key, DES.MODE_ECB)
plaintext1 = unpad(decipher.decrypt(ciphertext1), 8)
plaintext2 = unpad(decipher.decrypt(ciphertext2), 8)

print("Decrypted Block 1:", plaintext1.decode())
print("Decrypted Block 2:", plaintext2.decode())
