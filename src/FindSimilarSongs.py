from FindSimilars import findSimilars
import random
import sys


def findSongs(songs, num):
    try:
        newPlaylist = []

        newSongCount = 0
        while (newSongCount < num):
            selectedSong = songs[random.randint(0,len(songs) - 1)]
            newPlaylist.append(findSimilars(selectedSong, songs))
            
            newSongCount += 1

        return newPlaylist
    
    except (ValueError):
        print("Error, empty playlist")


if __name__ == "__main__":
    input_data = sys.argv[1:]
    currPlaylist  = [int(x) for x in input_data]

    print(findSongs(currPlaylist, 15))