#ifndef Song_H
#define Song_H

#include <string>
using namespace std;

class Song {
    private: 
    string name;
    string artist;
    string spotifyID;
    string appleMusicID;

    public:
    Song(string name, string artist, string spotifyId, string appleMusicID) { 
        this->name = name; 
        this->artist = artist;
        this->spotifyID = spotifyID;
        this->appleMusicID = appleMusicID;
    }

    string getName() const { return this->name; }
    string getArtist() const { return artist; }

    bool operator==(const Song& other) const {
        return name == other.name && artist == other.artist;
    }
};

namespace std {
    template<>
    struct hash<Song> {
        size_t operator()(const Song& s) const {
            return hash<string>()(s.getName()) ^ hash<string>()(s.getArtist());
        }
    };
}

#endif