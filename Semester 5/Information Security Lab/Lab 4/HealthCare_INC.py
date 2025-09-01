import os
import json
import logging
import threading
from flask import Flask, request, jsonify
from cryptography.hazmat.primitives import serialization, hashes
from cryptography.hazmat.backends import default_backend
from apscheduler.schedulers.background import BackgroundScheduler
from datetime import datetime, timedelta
from sympy import isprime
from random import getrandbits
from base64 import b64encode, b64decode

# ----------------- Logging ----------------- #
logging.basicConfig(filename="kms_audit.log", level=logging.INFO,
                    format='%(asctime)s - %(levelname)s - %(message)s')

# ----------------- Secure Storage ----------------- #
KEY_STORAGE = "secure_keys"
if not os.path.exists(KEY_STORAGE):
    os.makedirs(KEY_STORAGE)

# ----------------- Rabin Key Functions ----------------- #
def generate_prime(bits):
    while True:
        p = getrandbits(bits)
        if p % 4 == 3 and isprime(p):
            return p

def generate_rabin_keypair(bits=1024):
    p = generate_prime(bits // 2)
    q = generate_prime(bits // 2)
    n = p * q
    return {'public_key': n, 'private_key': {'p': p, 'q': q}}

def save_keys(entity_id, keys):
    with open(f"{KEY_STORAGE}/{entity_id}.json", "w") as f:
        json.dump(keys, f)
    logging.info(f"Key pair saved for {entity_id}")

def load_keys(entity_id):
    try:
        with open(f"{KEY_STORAGE}/{entity_id}.json", "r") as f:
            return json.load(f)
    except FileNotFoundError:
        return None

def revoke_keys(entity_id):
    path = f"{KEY_STORAGE}/{entity_id}.json"
    if os.path.exists(path):
        os.remove(path)
        logging.warning(f"Keys revoked for {entity_id}")
        return True
    return False

def renew_keys(entity_id, bits=1024):
    new_keys = generate_rabin_keypair(bits)
    save_keys(entity_id, new_keys)
    logging.info(f"Keys renewed for {entity_id}")
    return new_keys

# ----------------- Flask App ----------------- #
app = Flask(__name__)
revoked_entities = set()

@app.route("/request_key", methods=["POST"])
def request_key():
    data = request.get_json()
    entity_id = data.get("entity_id")
    bits = int(data.get("bits", 1024))

    if entity_id in revoked_entities:
        return jsonify({"error": "Entity key revoked"}), 403

    existing = load_keys(entity_id)
    if existing:
        logging.info(f"Key already exists for {entity_id}")
        return jsonify({"message": "Key already exists", "public_key": existing['public_key']})

    keys = generate_rabin_keypair(bits)
    save_keys(entity_id, keys)
    logging.info(f"Key generated for {entity_id}")
    return jsonify({"public_key": keys['public_key']})

@app.route("/revoke_key", methods=["POST"])
def revoke_key():
    data = request.get_json()
    entity_id = data.get("entity_id")
    success = revoke_keys(entity_id)
    revoked_entities.add(entity_id)
    return jsonify({"status": "revoked" if success else "not found"})

@app.route("/renew_keys", methods=["POST"])
def manual_renew():
    data = request.get_json()
    entity_id = data.get("entity_id")
    keys = renew_keys(entity_id)
    return jsonify({"status": "renewed", "public_key": keys['public_key']})

@app.route("/get_public_key", methods=["GET"])
def get_public_key():
    entity_id = request.args.get("entity_id")
    keys = load_keys(entity_id)
    if keys:
        return jsonify({"public_key": keys['public_key']})
    return jsonify({"error": "Not found"}), 404

# ----------------- Key Renewal Scheduler ----------------- #
def auto_renew_keys():
    for file in os.listdir(KEY_STORAGE):
        if file.endswith(".json"):
            entity_id = file.replace(".json", "")
            renew_keys(entity_id)

scheduler = BackgroundScheduler()
scheduler.add_job(auto_renew_keys, 'interval', days=365)  # Every 12 months
scheduler.start()

# ----------------- Main ----------------- #
def run_app():
    app.run(debug=False, port=5000)

if __name__ == "__main__":
    threading.Thread(target=run_app).start()
