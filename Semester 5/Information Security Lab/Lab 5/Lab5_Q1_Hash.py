def custom_hash(input_string):
    hash_val = 5381
    for ch in input_string:
        hash_val = (hash_val * 33) + ord(ch)

        # Bitwise mixing: XOR with shifted bits (example: XOR with right-shifted 16 bits)
        hash_val = hash_val ^ (hash_val >> 16)

        # Keep within 32 bits
        hash_val = hash_val & 0xFFFFFFFF
    return hash_val

# Example usage
input_str = "Hello, World!"
print(f"Hash for '{input_str}': {custom_hash(input_str)}")
