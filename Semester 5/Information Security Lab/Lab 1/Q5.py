# John is reading a mystery book involving cryptography. In one part of the book, 
# the author gives a ciphertext "CIW" and two paragraphs later the author tells the reader that this is a shift cipher and the plaintext is "yes". 
# In the next chapter, the hero found a tablet in a cave with "XVIEWYWI" engraved on it. 
# John immediately found the actual meaning of the ciphertext. Identify the type of attack and plaintext.

print("Known Cipher: CIW")
print("Known Cipher: yes")

def letter_to_index(letter):
    return ord(letter.upper()) - ord('A')

def index_to_letter(index):
    return chr((index % 26) + ord('A'))

def find_shift(ciphertext, plaintext):
    shifts = []
    for c, p in zip(ciphertext, plaintext):
        shift = (letter_to_index(c) - letter_to_index(p)) % 26
        shifts.append(shift)
    return max(set(shifts), key=shifts.count)

def decrypt_caesar(ciphertext, shift):
    plaintext = ''
    for char in ciphertext:
        if char.isalpha():
            index = (letter_to_index(char) - shift) % 26
            plaintext += index_to_letter(index)
        else:
            plaintext += char
    return plaintext

known_cipher = "CIW"
known_plain = "yes"

shift = find_shift(known_cipher, known_plain)
print(f"Discovered Caesar shift: {shift}")

cipher_to_decrypt = "XVIEWYWI"
print(f"Message: {cipher_to_decrypt}")
decrypted_text = decrypt_caesar(cipher_to_decrypt, shift)
print(f"Decrypted text: {decrypted_text}")

