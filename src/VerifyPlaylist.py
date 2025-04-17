import os
import re
import sys
import spotipy
from spotipy.oauth2 import SpotifyClientCredentials
from dotenv import load_dotenv

load_dotenv()


client_id = os.getenv("SPOTIFY_CLIENT_ID")
client_secret = os.getenv("SPOTIFY_CLIENT_SECRET")

auth_manager = SpotifyClientCredentials(client_id=client_id, client_secret=client_secret)
sp = spotipy.Spotify(auth_manager=auth_manager)

def verifyPlaylist(code):
    try:
        playlist = sp.playlist(code)
        return True
    except spotipy.exceptions.SpotifyException:
        return False

def extractCode(playlist):
    match = re.match(r'https://open\.spotify\.com/playlist/([a-zA-Z0-9]{22})', playlist)
    return match.group(1) if match else sys.exit(3)


if __name__ == "__main__": 
    data = str(sys.argv[1])
    paylistCode = extractCode(data)
    
    if verifyPlaylist(paylistCode):
        sys.exit(0)
    else:
        sys.exit(3)