#include "Playlist.h"
#include "Song.h"
#include <iostream>
#include <unordered_set>
#include <string>
#include <queue>
#include <cstdlib>
#include <memory>
#include <array>

using namespace std;

int findSongs(queue<Song> songs, Playlist& currPlaylist, Playlist& newPlaylist) {
    int addedSongs = 0;


    while (!songs.empty()) {
            Song selectedSong = songs.front();

            if (!currPlaylist.songInPlaylist(songs.front())) {
                if (newPlaylist.addSong(songs.front())) { addedSongs++;}
            }
            
            songs.pop();

        }

    return addedSongs;
    
}



queue<Song> getNewSongs(int len, Playlist& currPlaylist) {
    queue<Song> newSongs;


    std::string command = "python GetSimilarSongs.py \"" + currPlaylist.getPlaylistNames() + "\"";
    
    // Use popen to capture the output of the Python script
    std::array<char, 128> buffer;
    std::string result;
    FILE* pipe = popen(command.c_str(), "r");

    if (!pipe) {
        throw std::runtime_error("Failed to run Python script!");
    }

    while (fgets(buffer.data(), buffer.size(), pipe) != nullptr) {
        result += buffer.data(); // Append the result to the output string
    }

    fclose(pipe);

    newSongs.push(result);

    
    return newSongs;
}

int main() {
    Playlist currPlaylist; // get input data
    currPlaylist.addSong(Song("Imagine"));
    currPlaylist.addSong(Song("Bohemian Rhapsody"));
    currPlaylist.addSong(Song("Like a Rolling Stone"));
    currPlaylist.addSong(Song("Smells Like Teen Spirit"));
    currPlaylist.addSong(Song("What's Going On"));
    currPlaylist.addSong(Song("Respect"));
    currPlaylist.addSong(Song("Hey Jude"));
    currPlaylist.addSong(Song("Billie Jean"));
    currPlaylist.addSong(Song("Sweet Child O' Mine"));
    currPlaylist.addSong(Song("Rolling in the Deep"));
    currPlaylist.addSong(Song("Shape of You"));
    currPlaylist.addSong(Song("Crazy in Love"));
    currPlaylist.addSong(Song("Thunder Road"));
    currPlaylist.addSong(Song("Born to Run"));
    currPlaylist.addSong(Song("Total Eclipse of the Heart"));
    currPlaylist.addSong(Song("I Will Always Love You"));
    currPlaylist.addSong(Song("Yesterday"));
    currPlaylist.addSong(Song("Fight the Power"));
    currPlaylist.addSong(Song("A Change Is Gonna Come"));
    currPlaylist.addSong(Song("Good Vibrations"));

    Playlist newPlaylist; 

    int addedSongs = 0;

    // while (addedSongs < 30) {
    // }


    addedSongs += findSongs(getNewSongs(30, currPlaylist), currPlaylist, newPlaylist);

    cout << newPlaylist.getPlaylistNames();

}