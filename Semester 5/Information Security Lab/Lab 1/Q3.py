def create_playfair_matrix(key):
    alphabet = "ABCDEFGHIKLMNOPQRSTUVWXYZ"
    # Remove duplicates and create a matrix
    key = "".join(dict.fromkeys(key.upper()))  # Remove duplicates
    matrix = key + ''.join([char for char in alphabet if char not in key])
    matrix = [matrix[i:i + 5] for i in range(0, len(matrix), 5)]  # 5x5 matrix
    return matrix

def preprocess_message(message):
    message = message.upper().replace(" ", "")  # Remove spaces
    message = message.replace("J", "I")  # Replace 'J' with 'I'
    pairs = []
    i = 0
    while i < len(message):
        if i + 1 < len(message) and message[i] == message[i + 1]:
            pairs.append(message[i] + 'X')  # If same letter, add 'X'
            i += 1
        else:
            pairs.append(message[i:i + 2])  # Otherwise, take next two characters
            i += 2
    # If there's an odd number of characters, append 'X' at the end
    if len(pairs[-1]) == 1:
        pairs[-1] += 'X'
    return pairs

def find_position(matrix, letter):
    for row in range(5):
        for col in range(5):
            if matrix[row][col] == letter:
                return row, col

def playfair_encrypt_decrypt(message, key, mode='encrypt'):
    matrix = create_playfair_matrix(key)
    pairs = preprocess_message(message)

    result = []

    for pair in pairs:
        r1, c1 = find_position(matrix, pair[0])
        r2, c2 = find_position(matrix, pair[1])

        if r1 == r2:  # Same row
            shift = 1 if mode == 'encrypt' else -1
            c1 = (c1 + shift) % 5
            c2 = (c2 + shift) % 5
        elif c1 == c2:  # Same column
            shift = 1 if mode == 'encrypt' else -1
            r1 = (r1 + shift) % 5
            r2 = (r2 + shift) % 5
        else:  # Rectangle case (different row and column)
            c1, c2 = c2, c1

        result.append(matrix[r1][c1] + matrix[r2][c2])

    return "".join(result)

# Example usage
message = "The key is hidden under the door pad"
key = "GUIDANCE"

# Encrypt the message
encrypted_message = playfair_encrypt_decrypt(message, key, mode='encrypt')
print("Encrypted Message: ", encrypted_message)

print("\n")

# Decrypt the message
decrypted_message = playfair_encrypt_decrypt(encrypted_message, key, mode='decrypt')
print("Decrypted Message: ", decrypted_message)
