import sys
import spotipy
from spotipy.oauth2 import SpotifyClientCredentials
from dotenv import load_dotenv
import os

load_dotenv()

client_id = os.getenv("SPOTIFY_CLIENT_ID")
client_secret = os.getenv("SPOTIFY_CLIENT_SECRET")

auth_manager = SpotifyClientCredentials(client_id=client_id, client_secret=client_secret)
sp = spotipy.Spotify(auth_manager=auth_manager)


def getAppleCode(title):
    return "Null"

def parseSongs(playlist):
    tracks = playlist['items']
    songs = ""
    
    for song in tracks:
        track = song['track']
        title = track['name']
        artist = track['artists'][0]['name']
        spotifyCode = track['id']  
        appleCode = getAppleCode(title)

        songs += (title + "~" + artist + "~" + spotifyCode + "~" + appleCode + "|")

    return songs
    

def getPlayListID(url):
    found = False
    output = ""

    for x in reversed(url):
        if not found:
            if x == '?':
                found = True
                continue
        else:
            if x == "/":
                break
            else:
                output = x + output

    return output


if __name__ == "__main__": 
    data = str(sys.argv[1])
    playlistID = getPlayListID(data)

    playlist = sp.playlist_tracks(playlistID)

    print(parseSongs(playlist))
