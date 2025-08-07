def vigenere_encrypt(plaintext, keyword):
    # Remove spaces and convert to uppercase
    plaintext = plaintext.replace(" ", "").upper()
    keyword = keyword.upper()

    ciphertext = ""
    keyword_length = len(keyword)

    for i, char in enumerate(plaintext):
        if char.isalpha():
            p = ord(char) - ord('A')
            k = ord(keyword[i % keyword_length]) - ord('A')
            c = (p + k) % 26
            ciphertext += chr(c + ord('A'))
        else:
            ciphertext += char  # keep non-letters as-is

    return ciphertext

# Example usage
plaintext = "Life is full of surprises"
keyword = "HEALTH"

ciphertext = vigenere_encrypt(plaintext, keyword)
print("Plaintext: ", plaintext)
print("Keyword:   ", keyword)
print("Ciphertext:", ciphertext)
