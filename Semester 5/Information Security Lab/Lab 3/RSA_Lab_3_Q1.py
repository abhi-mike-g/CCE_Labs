def encrypt_message(message, e, n):
    """Encrypts the message using RSA encryption formula."""
    cipher_text = []
    for char in message:
        M = ord(char)  # Convert character to ASCII
        C = pow(M, e, n)  # Encrypt the character
        cipher_text.append(C)
    return cipher_text


def decrypt_message(cipher_text, d, n):
    """Decrypts the ciphertext using RSA decryption formula."""
    decrypted_message = ""
    for C in cipher_text:
        M = pow(C, d, n)  # Decrypt the character
        decrypted_message += chr(M)  # Convert back to character
    return decrypted_message


def main():
    # Get input from the user

    print("RSA Encryption/Decryption Demo")
    message = input("Enter the message to encrypt: ")

    # Public Key (n, e) and Private Key (n, d)
    n = int(input("Enter the modulus n: "))
    e = int(input("Enter the public exponent e: "))
    d = int(input("Enter the private exponent d: "))

    # Encrypt the message
    encrypted_message = encrypt_message(message, e, n)
    print(f"\nEncrypted message: {encrypted_message}")

    # Decrypt the message
    decrypted_message = decrypt_message(encrypted_message, d, n)
    print(f"\nDecrypted message: {decrypted_message}")


if __name__ == "__main__":
    main()
