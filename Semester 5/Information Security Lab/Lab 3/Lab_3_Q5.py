import time
from cryptography.hazmat.primitives.asymmetric import dh
from cryptography.hazmat.backends import default_backend
from cryptography.hazmat.primitives import serialization, hashes
from cryptography.hazmat.primitives.kdf.hkdf import HKDF

# Generate Diffie-Hellman parameters (shared between peers)
def generate_dh_parameters():
    parameters = dh.generate_parameters(generator=2, key_size=2048, backend=default_backend())
    return parameters

# Generate private and public keys for a peer
def generate_peer_keys(parameters):
    start_time = time.time()
    private_key = parameters.generate_private_key()
    public_key = private_key.public_key()
    duration = time.time() - start_time
    return private_key, public_key, duration

# Derive a shared secret key using peer's private key and other peer's public key
def compute_shared_key(private_key, peer_public_key):
    start_time = time.time()
    shared_key = private_key.exchange(peer_public_key)

    # Derive a symmetric key using HKDF
    derived_key = HKDF(
        algorithm=hashes.SHA256(),
        length=32,
        salt=None,
        info=b'handshake data',
        backend=default_backend()
    ).derive(shared_key)
    duration = time.time() - start_time
    return derived_key, duration

def main():
    print("🔐 Diffie-Hellman Key Exchange Demonstration\n")
    # Generate common DH parameters
    print("⏳ Generating DH parameters (shared between peers)...")
    parameters = generate_dh_parameters()
    # Generate keys for Peer A
    print("\n📍 Generating keys for Peer A...")
    private_key_A, public_key_A, time_A = generate_peer_keys(parameters)
    print(f"✅ Peer A key generation time: {time_A:.4f} seconds")
    # Generate keys for Peer B
    print("\n📍 Generating keys for Peer B...")
    private_key_B, public_key_B, time_B = generate_peer_keys(parameters)
    print(f"✅ Peer B key generation time: {time_B:.4f} seconds")
    # Compute shared secret on both sides
    print("\n🔄 Computing shared secret keys...")
    shared_key_A, time_shared_A = compute_shared_key(private_key_A, public_key_B)
    shared_key_B, time_shared_B = compute_shared_key(private_key_B, public_key_A)
    print(f"🔑 Shared key derivation time (Peer A): {time_shared_A:.4f} seconds")
    print(f"🔑 Shared key derivation time (Peer B): {time_shared_B:.4f} seconds")
    # Verify both peers derived the same key
    if shared_key_A == shared_key_B:
        print("\n✅ Shared key successfully established between peers!")
    else:
        print("\n❌ Shared key mismatch – error in exchange!")
    print(f"\n🔒 Shared Secret (hex): {shared_key_A.hex()}")
if __name__ == "__main__":
    main()

