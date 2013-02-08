//
//  CBoxButton.cpp
//  Kinect_3DJ
//
//  Created by LJ on 10/2/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef Kinect_3DJ_CSongs_h
#define Kinect_3DJ_CSongs_h
#include <iostream>
#include "ConfigFile.h"
using namespace std;


class CSongs
{
public:
    // singleton this class.
    static CSongs& getInstance(){
        static CSongs _instance;
        return _instance;
    }

    
    bool getFirst( string& songName, mapEntity& mapSong);    // get the first song of folder.
    bool getCurrent( string& songName, mapEntity& mapSong);
    bool getNext( string& songName, mapEntity& mapSong); // if you are the end of list, you will loop to first node.
    bool isLast();  // check whether the node is the last or not.

private:
    // singleton this class. 
    CSongs();
    CSongs( const CSongs& );
    CSongs& operator=( const CSongs&);

    // load the songs from songs folder in data.
    bool load();
    bool load(string path);
    void unload();

    CConfigFile m_configFile;
    ofDirectory m_dir;
    unsigned int m_cursor;
};

#endif
