# Encrypt the message "the house is being sold tonight" using each of the following ciphers. Ignore the space between words. Decrypt the message to get the original plaintext:
# a) Vigenere cipher with key: "dollars"
# b) Autokey cipher with key = 7


def vigenere_cipher(plaintext, key, mode='encrypt'):
    alphabet = "abcdefghijklmnopqrstuvwxyz"
    key = key.lower()
    plaintext = plaintext.lower()
    ciphertext = []

    key_repeated = (key * (len(plaintext) // len(key) + 1))[:len(plaintext)]

    shift = 1 if mode == 'encrypt' else -1

    for i in range(len(plaintext)):
        if plaintext[i].isalpha():
            p = alphabet.index(plaintext[i])
            k = alphabet.index(key_repeated[i])
            c = (p + shift * k) % 26
            ciphertext.append(alphabet[c])
        else:
            ciphertext.append(plaintext[i])

    return ''.join(ciphertext)


def autokey_cipher(plaintext, key, mode='encrypt'):
    alphabet = "abcdefghijklmnopqrstuvwxyz"
    plaintext = plaintext.lower()
    ciphertext = []
    key_letter = chr(ord('a') + (int(key) % 26))
    key_repeated = [key_letter]
    shift = 1 if mode == 'encrypt' else -1
    for i in range(len(plaintext)):
        if plaintext[i].isalpha():
            p = ord(plaintext[i]) - ord('a')
            k = ord(key_repeated[i % len(key_repeated)]) - ord('a')
            c = (p + shift * k) % 26
            ciphertext.append(chr(c + ord('a')))
            if mode == 'encrypt':
                key_repeated.append(ciphertext[-1])  # Append the ciphertext character for encryption
            else:
                key_repeated.append(plaintext[i])  # Append the plaintext character for decryption
        else:
            ciphertext.append(plaintext[i])
    return ''.join(ciphertext)


message = "thehouseisbeingsoldtonight"
vigenere_key = "dollars"
autokey_key = 7

vigenere_encrypted = vigenere_cipher(message, vigenere_key, mode='encrypt')
vigenere_decrypted = vigenere_cipher(vigenere_encrypted, vigenere_key, mode='decrypt')

autokey_encrypted = autokey_cipher(message, autokey_key, mode='encrypt')
autokey_decrypted = autokey_cipher(autokey_encrypted, autokey_key, mode='decrypt')

print("Vigenère Encrypted: ", vigenere_encrypted)
print("Vigenère Decrypted: ", vigenere_decrypted)

print("\n")

print("Autokey Encrypted: ", autokey_encrypted)
print("Autokey Decrypted: ", autokey_decrypted)
