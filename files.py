import json
import os
from dotenv import load_dotenv



def get_env_variable(key):
    # Try to load the .env file from the current directory
    load_dotenv()

    # Get the environment variable
    value = os.getenv(key)

    # If the variable is not found, ask the user to input it
    if value is None:
        value = input(f"Enter the value for {key}: ")
        # Optionally, you can also save this back to the .env file
        save_to_env(key, value)

    return value


def load_json(file_path):
    try:
        with open(file_path, 'r') as file:
            data = json.load(file)
            return data
    except FileNotFoundError:
        print(f"File not found: {file_path}")
        return None
    except json.JSONDecodeError:
        print(f"Error decoding JSON from file: {file_path}")
        return None

def save_to_env(key, value):
    with open('.env', 'a') as env_file:
        env_file.write(f"{key}={value}\n")

json_file_path = 'output.json'

loaded_data = load_json(json_file_path)

if loaded_data is not None:
    print("Loaded JSON content:")
    print(json.dumps(loaded_data, indent=2))


key_name = 'MY_ENV_VARIABLE'
env_value = get_env_variable(key_name)
print(f"The value of {key_name} is: {env_value}")