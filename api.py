import json

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

# Example usage:
json_file_path = 'output.json'

loaded_data = load_json(json_file_path)

if loaded_data is not None:
    print("Loaded JSON content:")
    print(json.dumps(loaded_data, indent=2))
    