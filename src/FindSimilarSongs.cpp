#include "Playlist.h"
#include "Song.h"
#include <iostream>
#include <unordered_set>
#include <string>
#include <queue>
#include <cstdlib>
#include <memory>
#include <array>
#include <sstream>
#include <vector>

using namespace std;


vector<string> split(const string& str, char delimiter) {
    vector<string> tokens;
    stringstream ss(str);
    string token;
    
    while (getline(ss, token, delimiter)) {
        tokens.push_back(token);
    }
    
    return tokens;
}

queue<Song> getNewSongs(int len, Playlist& currPlaylist) {
    queue<Song> newSongs;
    
    
    string command = "python GetSimilarSongs.py \""  + to_string(len) + "|" + currPlaylist.getPlaylistInfo();
    
    array<char, 128> buffer;
    string result;
    FILE* pipe = popen(command.c_str(), "r");
    
    if (!pipe) {
        throw runtime_error("Failed to run Python script!");
    }
    
    while (fgets(buffer.data(), buffer.size(), pipe) != nullptr) {
        result += buffer.data(); 
    }
    
    fclose(pipe);
    
    vector<string> songs = split(result, '|');
    
    for (string x : songs) { // |Title~Artist~Spotify ID~Apple Music ID|
        vector<string> parsedSong = split(x, '~');
        if (parsedSong.size() < 4) continue;

        string title = parsedSong[0];
        string artist = parsedSong[1];
        string spotifyID = parsedSong[2];
        string appleMusicID = parsedSong[3];
        
        Song newSong = Song(title, artist, spotifyID, appleMusicID);
        
        newSongs.push(newSong);
        
    }
    
    return newSongs;
}

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

Playlist submittedPlaylist(string data) {
    Playlist currPlaylist; // get input data

    currPlaylist.addSong(Song("Lying from You", "Linkin Park", "3BmjRmFTESgWZLPSVGp8aG", "NULL"));
    currPlaylist.addSong(Song("Always", "Saliva", "7kpa6MWRrPaF3b6C0DgioK", "NULL"));
    currPlaylist.addSong(Song("The Red", "Chevelle", "1gyee1JuFFiP476LQpRMYU", "NULL"));

    return currPlaylist;

}

int main() {
    Playlist currPlaylist = submittedPlaylist("temp"); //user submitted
    Playlist newPlaylist; 

    int addedSongs = 0;

    while (addedSongs < 30) {
        addedSongs += findSongs(getNewSongs(30, currPlaylist), currPlaylist, newPlaylist);
    }
        

    cout << "\n\nprinting songs";
    cout << newPlaylist.getPlaylistInfo();
    cout << newPlaylist.getPlaylistSize();


}