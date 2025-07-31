# Encrypt the message "I am learning information security" using each of the following ciphers. Ignore the space between words. Decrypt the message to get the original plaintext:
# a) Additive cipher with key = 20
# b) Multiplicative cipher with key = 15
# c) Affine cipher with key = (15, 20)

def modinv(a, m):
    for x in range(1, m):
        if (a * x) % m == 1:
            return x
    return None

def caesar_cipher(text, key, mode='encrypt'):
    shift = key if mode == 'encrypt' else -key
    result = ''
    for c in text:
        if c.isalpha():
            num = ord(c) - 97
            shifted_num = (num + shift) % 26
            if shifted_num < 0:
                shifted_num += 26
            result += chr(shifted_num + 97)
    return result

def multiplicative_cipher(text, key, mode='encrypt'):
    inv = modinv(key, 26)
    if mode == 'decrypt' and inv is None:
        raise ValueError(f"Key {key} has no modular inverse mod 26. Choose a coprime key.")

    result = ''
    multiplier = key if mode == 'encrypt' else inv
    for c in text:
        if c.isalpha():
            num = ord(c) - 97
            result += chr((num * multiplier) % 26 + 97)
    return result

def affine_cipher(text, a_key, b_key, mode='encrypt'):
    a_inv = modinv(a_key, 26)
    result = ''
    for c in text:
        if c.isalpha():
            num = ord(c) - 97
            if mode == 'encrypt':
                result += chr((a_key * num + b_key) % 26 + 97)
            else:
                result += chr((a_inv * (num - b_key)) % 26 + 97)
    return result


plaintext = "iamlearninginformationsecurity"
plaintext = ''.join(plaintext.split())

multiplicative_key, additive_key, affine_a_key, affine_b_key = 15, 20, 15, 20

additive_ciphertext = caesar_cipher(plaintext, additive_key)
multiplicative_ciphertext = multiplicative_cipher(plaintext, multiplicative_key)
affine_ciphertext = affine_cipher(plaintext, affine_a_key, affine_b_key)

decrypted_additive = caesar_cipher(additive_ciphertext, additive_key, mode='decrypt')
decrypted_multiplicative = multiplicative_cipher(multiplicative_ciphertext, multiplicative_key, mode='decrypt')
decrypted_affine = affine_cipher(affine_ciphertext, affine_a_key, affine_b_key, mode='decrypt')

print(f"Additive Cipher Text: {additive_ciphertext}")
print(f"Decrypted Additive Cipher Text: {decrypted_additive}")

print("\n")

print(f"Multiplicative Cipher Text: {multiplicative_ciphertext}")
print(f"Decrypted Multiplicative Cipher Text: {decrypted_multiplicative}")

print("\n")

print(f"Affine Cipher Text: {affine_ciphertext}")
print(f"Decrypted Affine Cipher Text: {decrypted_affine}")
