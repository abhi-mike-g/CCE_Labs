# Encrypt the message "Cryptography Lab Exercise" using AES in Counter (CTR) mode 
# with the key "0123456789ABCDEF0123456789ABCDEF" and a nonce of "0000000000000000".
# Provide the ciphertext and then decrypt it to retrieve the original message.

from Crypto.Cipher import AES
from Crypto.Util import Counter

# Key and nonce
key = bytes.fromhex("0123456789ABCDEF0123456789ABCDEF")
nonce = bytes.fromhex("0000000000000000")  # 8 bytes = 64 bits

# Message
message = "Cryptography Lab Exercise"
data = message.encode()

# Set up the counter (AES block size is 16 bytes, so 64-bit nonce + 64-bit counter)
ctr = Counter.new(64, prefix=nonce, initial_value=0)

# Encrypt
cipher = AES.new(key, AES.MODE_CTR, counter=ctr)
ciphertext = cipher.encrypt(data)
print("Ciphertext (hex):", ciphertext.hex())

# Decrypt
ctr_dec = Counter.new(64, prefix=nonce, initial_value=0)
decipher = AES.new(key, AES.MODE_CTR, counter=ctr_dec)
decrypted = decipher.decrypt(ciphertext)
print("Decrypted message:", decrypted.decode())
