#ifndef Playlist_H
#define Playlist_H

#include "Song.h"
#include <unordered_set>
#include <string>
#include <iostream>
#include <vector>
using namespace std;

class Playlist {
    private: unordered_set<string> songs;

    public: 
    bool songInPlaylist(Song song) {
        string songName = song.getName();

        if (songs.find(songName) != songs.end()) { return true; }
        else {return false; }
    }

    Playlist() = default;
    
    bool addSong(Song song){
        if (!songInPlaylist(song)) { songs.insert(song.getName()); return true; }
        else { return false; }
    }

    string getPlaylistNames() {
        string tempSongs;

        for (const string& song : songs) {
            tempSongs += ", " + song;
        }

        return tempSongs;

    }

};

#endif 