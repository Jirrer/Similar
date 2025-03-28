from FindSimilars import findSimilars
import random
import sys


def findSongs(songs, num):
    newPlaylist = songs

    newSongCount = 0
    while (newSongCount < num):
        selectedSong = songs[random.randint(0,len(songs) - 1)]
        newPlaylist.append(findSimilars(selectedSong, songs))
        
        newSongCount += 1

    return newPlaylist

if __name__ == "__main__":
    input_data = sys.argv[1:]

    
    print(input_data)