#ifndef Playlist_H
#define Playlist_H

#include "Song.h"
#include <unordered_set>
#include <string>
#include <iostream>
#include <vector>
#include <set>
using namespace std;

class Playlist {
private:
    set<Song> songs;

    bool duplicate(Song song) {


        return false;
    }


public:
    Playlist() = default;

    bool addSong(const Song& song) {
        if (duplicate(song)) {
            return false;
        }

        else {
            songs.insert(song);
            return true;
        }

    }

    string getPlaylistInfo() const {
        string tempSongs;

        for (const Song& song : songs) {
            tempSongs += song.getName() + " | " + song.getArtist() + " | " + song.getSpotifyCode() + " | " + song.getAppleCode() + "\n";
        }

        return tempSongs;
    }

    int getPlaylistSize() const { return songs.size(); }

    void printSpotifyCodes() {
        for (const Song& song : songs) {
            cout << song.getSpotifyCode() << "|";
        }
    }

    void printSongs() {
        for (const Song& song : songs) {
            cout << song.getName() << "|";
        }
    }
};

#endif
