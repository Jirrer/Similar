#ifndef Song_H
#define Song_H

#include <string>
#include <algorithm> 
#include <cctype> 
using namespace std;

class Song {
    private: 
    string name;
    string artist;
    string spotifyID;
    string appleMusicID;

    public:
    Song(string name, string artist, string spotifyID, string appleMusicID) { 
        this->name = name; 
        this->artist = artist;
        this->spotifyID = spotifyID;
        this->appleMusicID = appleMusicID;
    }

    string getName() const { return this->name; }
    string getArtist() const { return this->artist; }
    string getSpotifyCode() const { return this->spotifyID; }
    string getAppleCode() const { return this->appleMusicID; }

    bool operator<(const Song& other) const {
        return spotifyID < other.spotifyID; 
    }

    bool operator==(const Song& other) const {
        return spotifyID == other.spotifyID;
    }

};

#endif