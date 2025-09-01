import time
from Crypto.Cipher import AES
from Crypto.Random import get_random_bytes
from Crypto.Util.Padding import pad, unpad
from cryptography.hazmat.primitives.asymmetric import rsa, padding as rsa_padding, dh
from cryptography.hazmat.primitives.kdf.hkdf import HKDF
from cryptography.hazmat.primitives import serialization, hashes
from cryptography.hazmat.backends import default_backend
# ---------- Key Management ----------
class KeyManager:
    def __init__(self):
        self.keys = {}
        self.revoked_keys = set()
        self.shared_dh_params = dh.generate_parameters(generator=2, key_size=2048,
                                                       backend=default_backend())  # Shared DH parameters

    def register_system(self, name):
        rsa_private = rsa.generate_private_key(public_exponent=65537, key_size=2048)
        rsa_public = rsa_private.public_key()

        # Use shared DH parameters for all systems
        dh_private = self.shared_dh_params.generate_private_key()
        dh_public = dh_private.public_key()

        self.keys[name] = {
            "rsa_private": rsa_private,
            "rsa_public": rsa_public,
            "dh_private": dh_private,
            "dh_public": dh_public
        }

    def revoke(self, name):
        self.revoked_keys.add(name)

    def get_keys(self, name):
        if name in self.revoked_keys:
            raise Exception(f"Access to revoked key: {name}")
        return self.keys[name]
# ---------- Encryption Utilities ----------
def aes_encrypt(message: bytes, key: bytes) -> bytes:
    iv = get_random_bytes(16)
    cipher = AES.new(key, AES.MODE_CBC, iv)
    encrypted = cipher.encrypt(pad(message, AES.block_size))
    return iv + encrypted
def aes_decrypt(encrypted_data: bytes, key: bytes) -> bytes:
    iv = encrypted_data[:16]
    cipher = AES.new(key, AES.MODE_CBC, iv)
    decrypted = unpad(cipher.decrypt(encrypted_data[16:]), AES.block_size)
    return decrypted
def derive_shared_key(private_key, peer_public_key):
    shared_secret = private_key.exchange(peer_public_key)
    derived_key = HKDF(
        algorithm=hashes.SHA256(),
        length=32,
        salt=None,
        info=b'securecorp',
        backend=default_backend()
    ).derive(shared_secret)
    return derived_key
# ---------- Communication System ----------
class SecureSubsystem:
    def __init__(self, name, key_manager):
        self.name = name
        self.km = key_manager
        self.km.register_system(name)
    def send_secure_message(self, recipient_name, message):
        sender_keys = self.km.get_keys(self.name)
        recipient_keys = self.km.get_keys(recipient_name)
        # 1. Key exchange
        shared_key = derive_shared_key(
            sender_keys["dh_private"],
            recipient_keys["dh_public"]
        )
        # 2. AES encrypt the message
        encrypted_message = aes_encrypt(message.encode(), shared_key)
        # 3. Sign the encrypted message
        signature = sender_keys["rsa_private"].sign(
            encrypted_message,
            rsa_padding.PSS(mgf=rsa_padding.MGF1(hashes.SHA256()), salt_length=rsa_padding.PSS.MAX_LENGTH),
            hashes.SHA256()
        )
        return {
            "sender": self.name,
            "recipient": recipient_name,
            "encrypted_message": encrypted_message,
            "signature": signature,
            "sender_public_key": sender_keys["rsa_public"].public_bytes(
                encoding=serialization.Encoding.PEM,
                format=serialization.PublicFormat.SubjectPublicKeyInfo
            )
        }
    def receive_secure_message(self, data):
        recipient_keys = self.km.get_keys(self.name)
        # Load sender public key
        sender_pub_key = serialization.load_pem_public_key(data["sender_public_key"], backend=default_backend())
        # Verify signature
        try:
            sender_pub_key.verify(
                data["signature"],
                data["encrypted_message"],
                rsa_padding.PSS(mgf=rsa_padding.MGF1(hashes.SHA256()), salt_length=rsa_padding.PSS.MAX_LENGTH),
                hashes.SHA256()
            )
        except Exception:
            raise Exception("Signature verification failed!")
        # Derive shared key
        sender_keys = self.km.get_keys(data["sender"])
        shared_key = derive_shared_key(
            recipient_keys["dh_private"],
            sender_keys["dh_public"]
        )
        # Decrypt the message
        decrypted = aes_decrypt(data["encrypted_message"], shared_key)
        return decrypted.decode()
# ---------- Performance Measurement ----------
def measure_performance():
    km = KeyManager()
    system_a = SecureSubsystem("Finance", km)
    system_b = SecureSubsystem("HR", km)
    message = "This is a confidential HR payroll document."
    start = time.time()
    secure_data = system_a.send_secure_message("HR", message)
    send_time = time.time() - start
    start = time.time()
    received = system_b.receive_secure_message(secure_data)
    receive_time = time.time() - start
    print("\n🔐 Secure Message Transmission Complete")
    print(f"Sent Message: {message}")
    print(f"Received Message: {received}")
    print(f"Send Time: {send_time:.4f}s | Receive Time: {receive_time:.4f}s")
# ---------- Run Demo ----------
if __name__ == "__main__":
    measure_performance()
