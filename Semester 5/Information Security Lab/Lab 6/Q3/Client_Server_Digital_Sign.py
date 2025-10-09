# Start Server
# python client_server_demo.py server


# In another terminal, run client:
# python client_server_demo.py client

# client_server_demo.py
"""
Client-Server demo:

 - Run as 'server': python client_server_demo.py server
 - Run as 'client': python client_server_demo.py client

The protocol:
 1. Server listens on localhost:6000 and advertises DH params (p,g).
 2. Client connects, generates DH A and sends to server.
 3. Server responds with its DH B.
 4. Both derive shared AES key from DH (SHA256 of shared secret).
 5. Client creates a Schnorr signature of the plaintext (Schnorr key generated locally),
    then encrypts plaintext with AES-GCM and sends packet:
        { "cipher_hex": ..., "nonce_hex": ..., "tag_hex": ..., "sig_e": ..., "sig_s": ..., "schnorr_y": ... }
 6. Server decrypts and verifies Schnorr signature using provided schnorr_y public key.
 7. Server responds with processing result.

This is a simple educational demo; it's NOT production-grade security.
"""

import socket
import json
import struct
import sys
import threading
from Crypto.Util import number
from Crypto.Hash import SHA256
from Crypto.Cipher import AES
from Crypto.Random import get_random_bytes
import time

# -------------------- Utilities --------------------

def send_msg(sock, data_bytes):
    # prefix with 4-byte length
    sock.sendall(struct.pack("!I", len(data_bytes)) + data_bytes)

def recv_msg(sock):
    # read 4-byte length prefix
    header = b""
    while len(header) < 4:
        chunk = sock.recv(4 - len(header))
        if not chunk:
            return None
        header += chunk
    msg_len = struct.unpack("!I", header)[0]
    data = b""
    while len(data) < msg_len:
        chunk = sock.recv(msg_len - len(data))
        if not chunk:
            return None
        data += chunk
    return data

def hash_to_int_sha256(msg_bytes, modulo=None):
    h = SHA256.new(msg_bytes).digest()
    v = number.bytes_to_long(h)
    if modulo:
        v = v % modulo
        if v == 0:
            v = 1
    return v

# -------------------- DH & AES helpers --------------------

def generate_safe_prime(bits=512):
    while True:
        q = number.getPrime(bits - 1)
        p = 2 * q + 1
        if number.isPrime(p):
            return p, q

def find_generator(p, q):
    exp = (p - 1) // q
    while True:
        h = number.getRandomRange(2, p - 1)
        g = pow(h, exp, p)
        if g != 1:
            return g

def dh_generate_keypair(p, g):
    priv = number.getRandomRange(2, p - 2)
    pub = pow(g, priv, p)
    return priv, pub

def derive_key(shared_int):
    # AES-256 key from SHA256(shared)
    shared_bytes = number.long_to_bytes(shared_int)
    return SHA256.new(shared_bytes).digest()

def aes_gcm_encrypt(key, plaintext, aad=b""):
    cipher = AES.new(key, AES.MODE_GCM)
    if aad:
        cipher.update(aad)
    ct, tag = cipher.encrypt_and_digest(plaintext)
    return cipher.nonce, ct, tag

def aes_gcm_decrypt(key, nonce, ct, tag, aad=b""):
    cipher = AES.new(key, AES.MODE_GCM, nonce=nonce)
    if aad:
        cipher.update(aad)
    try:
        pt = cipher.decrypt_and_verify(ct, tag)
        return pt
    except ValueError:
        return None

# -------------------- Schnorr --------------------

def schnorr_generate_keys(p, q, g):
    x = number.getRandomRange(1, q - 1)
    y = pow(g, x, p)
    return {"p": p, "q": q, "g": g, "x": x, "y": y}

def schnorr_sign(msg_bytes, priv):
    p = priv["p"]; q = priv["q"]; g = priv["g"]; x = priv["x"]
    k = number.getRandomRange(1, q - 1)
    r = pow(g, k, p)
    r_bytes = number.long_to_bytes(r)
    e = number.bytes_to_long(SHA256.new(msg_bytes + r_bytes).digest()) % q
    s = (k + x * e) % q
    return (int(e), int(s))

def schnorr_verify(msg_bytes, signature, pub):
    p = pub["p"]; q = pub["q"]; g = pub["g"]; y = pub["y"]
    e, s = signature
    # compute r' = g^s * y^{-e} mod p
    ye_inv = pow(y, (-e) % q, p)
    r_prime = (pow(g, s, p) * ye_inv) % p
    r_bytes = number.long_to_bytes(r_prime)
    echeck = number.bytes_to_long(SHA256.new(msg_bytes + r_bytes).digest()) % q
    return echeck == e

# -------------------- Server --------------------

def server_main(host="127.0.0.1", port=6000, bits=512):
    print("Server starting. Generating DH/Schnorr params...")
    p, q = generate_safe_prime(bits=bits)
    g = find_generator(p, q)
    print(f"Server parameters generated: p bits {p.bit_length()}, q bits {q.bit_length()}")

    # Start listening
    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    s.bind((host, port))
    s.listen(1)
    print(f"Listening on {host}:{port} ... (awaiting one client)")

    def handle_client(conn, addr):
        print("Client connected:", addr)
        # Step 1: receive client's DH public A (JSON)
        raw = recv_msg(conn)
        if raw is None:
            print("Client disconnected early.")
            conn.close()
            return
        data = json.loads(raw.decode())
        if "A_hex" not in data or "p_hex" not in data:
            print("Malformed initial message.")
            conn.close()
            return
        # Accept optionally p,g from client if provided; else use server's params.
        client_p = int(data.get("p_hex"), 16)
        client_g = int(data.get("g_hex"), 16)
        A = int(data["A_hex"], 16)
        # For demo, we will trust client's p/g if provided and use them
        p_used = client_p
        g_used = client_g
        print("Received A from client (hex prefix):", hex(A)[:80])
        # Generate server DH keypair and send B
        b_priv, B = dh_generate_keypair(p_used, g_used)
        reply = {"B_hex": hex(B), "p_hex": hex(p_used), "g_hex": hex(g_used)}
        send_msg(conn, json.dumps(reply).encode())
        print("Sent B to client (hex prefix):", hex(B)[:80])

        # Derive shared key
        shared = pow(A, b_priv, p_used)
        aes_key = derive_key(shared)
        print("Derived AES key (hex prefix):", aes_key.hex()[:64])

        # Now receive encrypted packet from client
        raw2 = recv_msg(conn)
        if raw2 is None:
            print("Client disconnected before sending payload.")
            conn.close()
            return
        pkt = json.loads(raw2.decode())
        # parse fields
        try:
            nonce = bytes.fromhex(pkt["nonce_hex"])
            ct = bytes.fromhex(pkt["cipher_hex"])
            tag = bytes.fromhex(pkt["tag_hex"])
            sig_e = int(pkt["sig_e"])
            sig_s = int(pkt["sig_s"])
            schnorr_y_hex = pkt["schnorr_y_hex"]
            schnorr_y = int(schnorr_y_hex, 16)
        except Exception as e:
            print("Malformed payload:", e)
            conn.close()
            return

        # decrypt
        plaintext = aes_gcm_decrypt(aes_key, nonce, ct, tag)
        if plaintext is None:
            print("Decryption/auth failure.")
            res = {"status": "decrypt_fail"}
            send_msg(conn, json.dumps(res).encode())
            conn.close()
            return
        print("Decrypted plaintext:", plaintext.decode())

        # Verify Schnorr signature using provided public y and known p,g,q
        pub = {"p": p_used, "q": q, "g": g_used, "y": schnorr_y}
        ok = schnorr_verify(plaintext, (sig_e, sig_s), pub)
        print("Schnorr signature valid?:", ok)

        # Log to file
        log = {
            "timestamp": time.time(),
            "plaintext": plaintext.decode(),
            "signature_valid": bool(ok),
            "client_pub_y": schnorr_y_hex
        }
        with open("merchant_log.json", "a") as f:
            f.write(json.dumps(log) + "\n")

        # Reply to client
        res = {"status": "processed", "signature_valid": bool(ok)}
        send_msg(conn, json.dumps(res).encode())
        conn.close()
        print("Connection closed.")

    # server loop (one client for demo)
    try:
        conn, addr = s.accept()
        handle_client(conn, addr)
    except KeyboardInterrupt:
        print("Server interrupted.")
    finally:
        s.close()

# -------------------- Client --------------------

def client_main(host="127.0.0.1", port=6000, bits=512):
    print("Client starting. Generating DH/Schnorr keys...")
    # Generate same DH params locally (in real usage these would be fixed/standard or provided by server)
    p, q = generate_safe_prime(bits=bits)
    g = find_generator(p, q)
    # For demo, send our p/g to server so both use same params
    a_priv, A = dh_generate_keypair(p, g)

    # Schnorr key for client
    schnorr = schnorr_generate_keys(p, q, g)
    print("Schnorr public y (hex prefix):", hex(schnorr["y"])[:80])

    # connect
    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    s.connect((host, port))
    print("Connected to server.")

    # Step 1: send A and p/g to server
    init = {"A_hex": hex(A), "p_hex": hex(p), "g_hex": hex(g)}
    send_msg(s, json.dumps(init).encode())
    # receive server B
    raw = recv_msg(s)
    if raw is None:
        print("Server disconnected.")
        return
    resp = json.loads(raw.decode())
    B = int(resp["B_hex"], 16)
    p_used = int(resp["p_hex"], 16)
    g_used = int(resp["g_hex"], 16)
    print("Received B from server (hex prefix):", hex(B)[:80])

    # derive shared key
    shared = pow(B, a_priv, p_used)
    aes_key = derive_key(shared)
    print("Derived AES key (hex prefix):", aes_key.hex()[:64])

    # Prepare plaintext and Schnorr signature
    plaintext = b"Send 55000 to Bob using Mastercard 3048-3303-3039-3783"
    sig_e, sig_s = schnorr_sign(plaintext, schnorr)
    print("Schnorr signature (e,s):", (sig_e, sig_s))

    # Encrypt with AES-GCM and send packet to server
    nonce, ct, tag = aes_gcm_encrypt(aes_key, plaintext)
    pkt = {
        "nonce_hex": nonce.hex(),
        "cipher_hex": ct.hex(),
        "tag_hex": tag.hex(),
        "sig_e": str(sig_e),
        "sig_s": str(sig_s),
        "schnorr_y_hex": hex(schnorr["y"])
    }
    send_msg(s, json.dumps(pkt).encode())

    # wait for response
    raw2 = recv_msg(s)
    if raw2:
        r = json.loads(raw2.decode())
        print("Server response:", r)
    s.close()

# -------------------- Entry point --------------------

if __name__ == "__main__":
    if len(sys.argv) < 2:
        print("Usage: python client_server_demo.py [server|client]")
        sys.exit(1)
    mode = sys.argv[1].lower()
    if mode == "server":
        server_main(bits=512)   # increase bits for real use
    elif mode == "client":
        client_main(bits=512)
    else:
        print("Unknown mode. Use 'server' or 'client'.")
