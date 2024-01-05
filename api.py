import requests

def get_access_token(client_id, client_secret):
    # Spotify URL for obtaining the access token
    auth_url = 'https://accounts.spotify.com/api/token'

    # Base64 encoded string that contains the client ID and client secret key
    # credentials = base64.b64encode(f"{client_id}:{client_secret}".encode())
    # headers = {'Authorization': f'Basic {credentials.decode()}'}

    # Make a POST request to the Spotify accounts service to get an access token
    auth_response = requests.post(auth_url, {
        'grant_type': 'client_credentials',
        'client_id': client_id,
        'client_secret': client_secret,
    })

    # Convert the response to JSON
    auth_response_data = auth_response.json()

    # Get the access token from the response
    access_token = auth_response_data['access_token']

    return access_token

def search_spotify(query, token):
    # Spotify URL for searching an item
    search_url = 'https://api.spotify.com/v1/search'

    # Define the headers and parameters for the GET request
    headers = {
        'Authorization': f'Bearer {token}'
    }
    params = {
        'q': query,
        'type': 'track',
        'limit': 5  # Limit the results to 5
    }

    # Make the GET request to the Spotify Search API
    response = requests.get(search_url, headers=headers, params=params)

    # Convert the response to JSON
    search_results = response.json()

    # Extracting and returning the first 5 track names and artists
    tracks = search_results['tracks']['items']
    for i, track in enumerate(tracks):
        print(f"{i+1}: {track['name']} by {', '.join([artist['name'] for artist in track['artists']])}")

# Replace with your Spotify API credentials
client_id = 'YOUR_SPOTIFY_CLIENT_ID'
client_secret = 'YOUR_SPOTIFY_CLIENT_SECRET'

# Get the access token
token = get_access_token(client_id, client_secret)

# Query and get results (replace 'QUERY_STRING' with your search term)
search_query = 'QUERY_STRING'  # Replace with your search query
search_spotify(search_query, token)