# John is reading a mystery book involving cryptography. In one part of the book, 
# the author gives a ciphertext "CIW" and two paragraphs later the author tells the reader that this is a shift cipher and the plaintext is "yes". 
# In the next chapter, the hero found a tablet in a cave with "XVIEWYWI" engraved on it. 
# John immediately found the actual meaning of the ciphertext. Identify the type of attack and plaintext.

def caesar_decrypt(ciphertext, shift):
    return ''.join(chr((ord(c.lower()) - ord('a') - shift) % 26 + ord('a')) for c in ciphertext if c.isalpha())

def main():
    sample_ct = "CIW"
    sample_pt = "yes"
    shift = (ord(sample_ct[0]) - ord(sample_pt[0])) % 26

    print("Detected Caesar shift:", shift)

    tablet_ct = "XVIEWYWI"
    plaintext = caesar_decrypt(tablet_ct, shift)
    print("Decrypted tablet text:", plaintext)

if __name__ == "__main__":
    main()
