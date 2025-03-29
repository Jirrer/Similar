import mysql.connector


def songsInDB():
    connection = mysql.connector.connect(
        host='localhost',
        user='root',
        password='7284',
        database='similar_db'
    )

    cursor = connection.cursor()
    cursor.execute("SELECT id, name FROM songs")
    output = cursor.fetchall()
    connection.close()
    cursor.close()

    return output


def formatSongs(songs):
    output = ""

    for row in songs:
        strRow = str(row)
        strRow = strRow[:len(strRow)] + "|"
        output += strRow

    return output

def getSongs():
    songs = {}


    text = formatSongs(songsInDB())
    for song in text.split("|"):
        strId = song[1:2]

        if strId:
            songs[int(strId)] = song[5:len(song) - 2]

    return songs