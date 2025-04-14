#ifndef Song_H
#define Song_H

#include <string>
using namespace std;

class Song {
    private: 
    string name;

    public:
    Song(string name ) { this->name = name; }

    string getName() { return this->name; }
};

#endif