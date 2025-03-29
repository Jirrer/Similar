import requests
import json
from GetSongs import getSongs

def get_song_analysis(song_name):
    try:
        print("test")
        # Send a POST request to the Node.js server
        url = "http://localhost:3000/run-python"
        payload = {
            "pythonFileName": "FindSimilarSongs.py",  # Specify the Python file to run
            "data": [song_name]  # Pass the song name as data
        }
        headers = {"Content-Type": "application/json"}

        response = requests.post(url, data=json.dumps(payload), headers=headers)

        # Check if the request was successful
        if response.status_code != 200:
            return f"Error: HTTP {response.status_code} - {response.text}"

        # Parse the JSON response
        result = response.json()
        return result.get("output", "No output returned from server")
    except Exception as e:
        return f"Error: {e}"

def compareSongs(currSong, songs):
    # Get analysis for the current song
    songData = get_song_analysis('Lying from You')
    print(songData)


   
    return [1,2,3,4,5,6,7,8,9,10,11] 

compareSongs(3,getSongs())