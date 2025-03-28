from GetSongs import getSongs

# algo that determines if a song is similar
# Rank by how similar
# Take input of how many the user wants

checkIndex = 0 

def getPossibleSongs():
    songs = getSongs()




    return [2]

def checkSimilar():
    global checkIndex
    checkIndex += 1

    return getPossibleSongs()[checkIndex - 1]
    


def findSimilars(songID, currPlaylist):
    seen = set(currPlaylist)

    songsChecked = 0
    while songsChecked < 1000:
        songsChecked += 1
        
        try:
            newSong = checkSimilar()

            if newSong not in seen:
                return newSong
        except IndexError:
            print("Less than 1,000 songs in database.")
            return