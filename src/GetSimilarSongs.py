import google.generativeai as genai
import sys
import spotipy
from spotipy.oauth2 import SpotifyClientCredentials
from dotenv import load_dotenv
import os

load_dotenv()

def getAppleCode(song):
    return "NULL"


def getSpotifyCode(song):
    client_id = os.getenv("SPOTIFY_CLIENT_ID")
    client_secret = os.getenv("SPOTIFY_CLIENT_SECRET")

    auth_manager = SpotifyClientCredentials(client_id=client_id, client_secret=client_secret)
    sp = spotipy.Spotify(auth_manager=auth_manager)

    info = sp.search(q = song, type= 'track', limit = 1)

    if info['tracks']['items']:
        track = info['tracks']['items'][0]
        songID = track['id']

        return songID

    return "Null"


def valididateSongInfo(info):
    songs = info.split("|")
    finalInfo = ""

    for x in songs:
        song = x.split("~")

        if len(song) == 2:
            title = song[0]
            artist = song[1]
            spotifyCode = getSpotifyCode(title)
            appleCode = getAppleCode(title)

            finalInfo += (title + '~' + artist + '~' + spotifyCode + '~' + appleCode + "|")

    return finalInfo


def getSongs(num, info):
    genai.configure(api_key = os.getenv('GEMINI_API_KEY'))

    model = genai.GenerativeModel('gemini-2.0-flash')

    prompt = f'''
    Give me {num} similar songs to the following list of songs: {info}. I want you to format in this way: TITLE~Artist|
    make sure it is exactly {num} new songs
    do not give explanation or song count, simply return each song formated as shown
    do not say here are the songs, just print the songs
    '''
    response = model.generate_content(prompt)

    songInfo = "|" + str(response.text)

    if (valididateSongInfo(songInfo)):
        return valididateSongInfo(songInfo)
    else:
        return "Error retreiving song data"


if __name__ == "__main__":
    data = sys.argv[1]
    numberOfSongs = ""
    songInfo = ""

    for x in range(len(data)):
        if data[x] == '|':
            songInfo = data[x + 1:]
            break
        else:
            numberOfSongs += data[x]
        
    print(getSongs(numberOfSongs, songInfo))