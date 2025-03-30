import requests
import hashlib

def roll_number(number):

    num = f"{number:03}"

    md5_hash = hashlib.md5(num.encode()).hexdigest()

    url = f"http://chall25.sigx.net:3209/roll/{md5_hash}/{num}"

    response = requests.get(url)
    return response.text

def find():
    for i in range(1,1000):
        print(f"Trying i: {i:03}")
        response = roll_number(i)
        if "Sorry, you lost!" not in response:
            print("Server response:", response)
            break

find()