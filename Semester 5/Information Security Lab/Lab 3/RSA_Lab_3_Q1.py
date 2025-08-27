def encrypt_rsa(message, n, e):
    return [pow(ord(char), e, n) for char in message]

def decrypt_rsa(ciphertext, n, d):
    return ''.join([chr(pow(c, d, n)) for c in ciphertext])

# Keys
n = 3233
e = 17
d = 2753

# Message
message = "Asymmetric Encryption"

# Encrypt
ciphertext = encrypt_rsa(message, n, e)
print("Ciphertext:", ciphertext)

# Decrypt
decrypted = decrypt_rsa(ciphertext, n, d)
print("Decrypted:", decrypted)
