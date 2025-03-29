import mysql.connector
from CompareSongs import compareSongs

checkIndex = 0 

def getSongGenre(songID):
    connection = mysql.connector.connect(
        host='localhost',
        user='root',
        password='7284',
        database='similar_db'
    )

    try:

        cursor = connection.cursor()
        query = "SELECT genre FROM songs WHERE id = %s AND genre IS NOT NULL AND genre != '';"
        cursor.execute(query, (songID,))

        result = cursor.fetchone()

        if result:
            songGenre = result[0]  # Get the genre from the result
            return songGenre
        else:
            return None

    finally:
        cursor.close()
        connection.close()

def songsByGenre(genres):
    if not genres or not isinstance(genres, str):
        raise ValueError("The 'genres' parameter must be a non-empty string.")
    
    matchingSongs = []

    connection = mysql.connector.connect(
        host='localhost',
        user='root',
        password='7284',
        database='similar_db'
    )

    cursor = connection.cursor()
    query  = "SELECT id FROM songs WHERE genre LIKE %s;;"

    for x in genres.split(','):
        cursor.execute(query, (f"%{x}%",))
        result = cursor.fetchall()

        matchingSongs.append(result)


    cursor.close()
    connection.close()

    seen = set()
    for x in matchingSongs:
        for i in x:
            if i not in seen:
                seen.add(i[0])

    return seen


def getPossibleSongs(songID):
    possibleSongs = songsByGenre(getSongGenre(songID))

    return compareSongs(songID, possibleSongs) # 1,0000 possible songs

def checkSimilar(songID):
    global checkIndex
    checkIndex += 1

    return getPossibleSongs(songID)[checkIndex - 1]
    

def findSimilars(songID, currPlaylist):
    seen = set(currPlaylist)

    songsChecked = 1
    while songsChecked < 1000:
        songsChecked += 1
        
        try:
            newSong = checkSimilar(songID)

            if newSong not in seen:
                return newSong
        except IndexError:
            return
