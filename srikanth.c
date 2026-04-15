from flask import Flask, request, jsonify

app = Flask(__name__)

@app.route('/')
def home():
    return "Server is running!"

@app.route('/data', methods=['GET'])
def get_data():
    return jsonify({"message": "Hello from server!"})

@app.route('/send', methods=['POST'])
def receive_data():
    data = request.json
    return jsonify({
        "status": "Received",
        "your_data": data
    })

if __name__ == '__main__':
    app.run(host='0.0.0.0', port=5000)







import requests

# Server URL (replace with your server IP if remote)
base_url = "http://127.0.0.1:5000"

# GET request
response = requests.get(f"{base_url}/data")
print("GET Response:", response.json())

# POST request
data = {"name": "Alice", "age": 25}
response = requests.post(f"{base_url}/send", json=data)
print("POST Response:", response.json())
