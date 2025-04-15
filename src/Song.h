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

    static string toLower(const string& str) {
        string lowerStr = str;
        transform(lowerStr.begin(), lowerStr.end(), lowerStr.begin(),
                  [](unsigned char c){ return tolower(c); });
        return lowerStr;
    }

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

    bool operator==(const Song& other) const {
        return toLower(name) == toLower(other.name) &&
               toLower(artist) == toLower(other.artist);
    }
};

namespace std {
    template<>
    struct hash<Song> {
        size_t operator()(const Song& s) const {
            auto toLower = [](const string& str) {
                string lowerStr = str;
                transform(lowerStr.begin(), lowerStr.end(), lowerStr.begin(),
                          [](unsigned char c){ return tolower(c); });
                return lowerStr;
            };

            return hash<string>()(toLower(s.getName())) ^ hash<string>()(toLower(s.getArtist()));
        }
    };
}

#endif