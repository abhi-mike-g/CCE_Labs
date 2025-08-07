# Use a brute-force attack to decipher the following message enciphered by Alice using an additive cipher. 
# Suppose that Alice always uses a key that is close to her birthday, which is on the 13th of the month:
# NCJAEZRCLAS/LYODEPRLYZRCLASJLCPEHZDTOPDZOLN&BY

def additive_decrypt(ciphertext, shift):
    plaintext = ''
    for c in ciphertext:
        if c.isalpha():
            base = ord('A') if c.isupper() else ord('a')
            plaintext += chr((ord(c) - base - shift) % 26 + base)
        else:
            plaintext += c
    return plaintext

cipher = "NCJAEZRCLAS/LYODEPRLYZRCLASJLCPEHZDTOPDZOLN&BY"

for key in range(26):
    print(f"Shift {key:2}: {additive_decrypt(cipher, key)}")
