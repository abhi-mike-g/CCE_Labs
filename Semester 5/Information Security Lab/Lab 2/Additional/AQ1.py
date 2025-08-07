import time
from Crypto.Cipher import DES, DES3, AES
from Crypto.Util.Padding import pad, unpad
from Crypto.Random import get_random_bytes
import matplotlib.pyplot as plt

# Message and keys
messages = {
    "Message 1": "Confidential Data",
    "Message 2": "Sensitive Information",
    "Message 3": "Performance Testing of Encryption Algorithms",
    "Message 4": "Classified Text",
    "Message 5": "Top Secret Data"
}

# Keys (all must be in bytes and of proper length)
keys = {
    "DES": b"A1B2C3D4",  # 8 bytes
    "AES-128": bytes.fromhex("0123456789ABCDEF0123456789ABCDEF"),  # 16 bytes
    "AES-192": bytes.fromhex("FEDCBA9876543210FEDCBA9876543210FEDCBA9876543210"),  # 24 bytes
    "AES-256": bytes.fromhex("0123456789ABCDEF0123456789ABCDEF0123456789ABCDEF0123456789ABCDEF"),  # 32 bytes
    "3DES": b"1234567890ABCDEF1234567890ABCDEF1234567890ABCDEF"[:24]  # 24 bytes
}

# Modes to evaluate
modes = {
    "ECB": AES.MODE_ECB,
    "CBC": AES.MODE_CBC,
    "CFB": AES.MODE_CFB,
    "OFB": AES.MODE_OFB,
    "CTR": AES.MODE_CTR
}

# Record execution times
execution_times = {mode: {} for mode in modes}

# Helper function to measure encryption time
def measure_time(cipher_class, key, mode, msg, is_ctr=False):
    data = pad(msg.encode(), cipher_class.block_size)
    iv = get_random_bytes(cipher_class.block_size)
    if is_ctr:
        from Crypto.Util import Counter
        ctr = Counter.new(128)
        cipher = cipher_class.new(key, modes["CTR"], counter=ctr)
    elif mode == AES.MODE_ECB:
        cipher = cipher_class.new(key, mode)
    else:
        cipher = cipher_class.new(key, mode, iv=iv)
    start = time.time()
    ciphertext = cipher.encrypt(data)
    end = time.time()
    return end - start

# Perform encryption and record times
for mode_name, mode_value in modes.items():
    for msg_label, msg in messages.items():
        if mode_name == "CTR":
            time_taken = measure_time(AES, keys["AES-256"], mode_value, msg, is_ctr=True)
        elif mode_name == "ECB":
            time_taken = measure_time(AES, keys["AES-256"], mode_value, msg)
        else:
            time_taken = measure_time(AES, keys["AES-256"], mode_value, msg)
        execution_times[mode_name][msg_label] = time_taken

# Plotting
plt.figure(figsize=(12, 6))
for mode_name in modes:
    plt.plot(list(messages.keys()), [execution_times[mode_name][msg] for msg in messages], label=mode_name)

plt.title("AES-256 Encryption Time by Mode for Different Messages")
plt.xlabel("Message")
plt.ylabel("Encryption Time (seconds)")
plt.legend()
plt.grid(True)
plt.xticks(rotation=45)
plt.tight_layout()
plt.show()
