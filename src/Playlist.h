#ifndef Playlist_H
#define Playlist_H

#include "Song.h"
#include <unordered_set>
#include <string>
#include <iostream>
#include <vector>
using namespace std;

class Playlist {
    private: unordered_set<Song> songs;

    public: 
    Playlist() = default;

    bool songInPlaylist(const Song& song) {
        return songs.find(song) != songs.end();
    }
    
    bool addSong(Song song){
        if (!songInPlaylist(song)) { songs.insert(song); return true; }
        else { return false; }
    }

    string getPlaylistInfo() {
        string tempSongs;

        for (const Song& song : songs) {
            tempSongs += song.getName() + " | " + song.getArtist() + " | " + song.getSpotifyCode() + " | " + song.getAppleCode();
        }

        return tempSongs;

    }

    int getPlaylistSize() {return songs.size(); }

};

#endif 