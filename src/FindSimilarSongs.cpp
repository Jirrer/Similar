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
    
    
    string command = "python src/GetSimilarSongs.py \""  + to_string(len) + "|" + currPlaylist.getPlaylistInfo();
    
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

        if (!currPlaylist.songInPlaylist(selectedSong) && !newPlaylist.songInPlaylist(selectedSong)) {
            if (newPlaylist.addSong(selectedSong)) { addedSongs++;}
        }
        
        songs.pop();

    }

    return addedSongs;
    
}

Playlist submittedPlaylist(string url) {
    Playlist currPlaylist; 

    string command = "python src/UserPlaylist.py \""  + url;
    
    array<char, 128> buffer;
    string result;
    FILE* pipe = popen(command.c_str(), "r");
    
    if (!pipe) {
        throw runtime_error("Failed to parse user playlist!");
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
        
        currPlaylist.addSong(newSong);
    }
 
    return currPlaylist;

}

string getType(string input) {
    string appleCheck = "apple";
    string spotifyCheck = "spotify";
    
    int appleIndex = 0;
    int spotifyIndex = 0;

    for (char x : input) {
        if (tolower(x) == appleCheck[appleIndex]) { appleIndex++; }
        else if (tolower(x) == spotifyCheck[spotifyIndex]) { spotifyIndex++; }

        if (appleIndex >= 5) { return "APPLE"; }
        else if (spotifyIndex >= 7) { return "SPOTIFY"; }
    }

    return NULL;
}

string parsePlaylist(string input) {
    int sliceIndex = 0;

    for (int x = 0; x < input.length(); x++) {
        if (input[x] == '|') { sliceIndex = x; break; }
    }

    return input.substr(sliceIndex + 1);
}

bool verifyPlaylist(string playlistType, string uncheckedPlaylist) {
    string command = "";

    if (playlistType == "Apple") {
        command = "python src/VerifyApple.py \""  + uncheckedPlaylist;
    }

    else if (playlistType == "SPOTIFY") {
        command = "python src/VerifySpotify.py \""  + uncheckedPlaylist;
    }


    
    array<char, 128> buffer;
    string result;
    FILE* pipe = popen(command.c_str(), "r");
    
    if (!pipe) {
        throw runtime_error("Failed to parse user playlist!");
    }
    
    while (fgets(buffer.data(), buffer.size(), pipe) != nullptr) {
        result += buffer.data(); 
    }
    
    int exitCode = pclose(pipe);

    if (exitCode == 3) { return false; } 
    else if (exitCode == 1) { return true; } 
    else { return true; }
}

int main() {
    string input;
    getline(cin, input);

    string playlistType = getType(input);
    string playlist = parsePlaylist(input);

    if (!verifyPlaylist(playlistType, playlist)) {exit(2); }

    int length_of_new_playlist = 30;

    Playlist currPlaylist = submittedPlaylist(input); //user submitted
    Playlist newPlaylist; 

    int addedSongs = 0;

    while (addedSongs < length_of_new_playlist) {
        addedSongs += findSongs(getNewSongs(length_of_new_playlist - addedSongs, currPlaylist), currPlaylist, newPlaylist);
    }
        
   newPlaylist.printSpotifyCodes();
}