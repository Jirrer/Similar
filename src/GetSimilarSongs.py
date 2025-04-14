import google.generativeai as genai
import sys


def valididateSongInfo(song):
    return True


def getSongs(num, info):
    genai.configure(api_key="AIzaSyBakuPnIa9RO3cCQoZVvoJh846zjhCuVVE") # make env

    model = genai.GenerativeModel('gemini-2.0-flash')

    prompt = f'''
    Give me {num} similar songs to the following list of songs: {info}. I want you to format in this way: TITLE~Artist~NULL~NULL|
    make sure it is exactly {num} new songs
    do not give explanation or song count, simply return each song formated as shown
    do not say here are the songs, just print the songs
    '''
    response = model.generate_content(prompt)

    songInfo = "|" + str(response.text)

    if (valididateSongInfo(songInfo)):
        return songInfo
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