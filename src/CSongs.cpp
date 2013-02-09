//
//  CBoxButton.cpp
//  Kinect_3DJ
//
//  Created by LJ on 1/10/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include "CSongs.h"


CSongs::CSongs()
{
    load();
}

bool CSongs::load( string path )
{        
    m_dir.listDir(path);
    if ( m_dir.size() == 0)
    {
        ofLogVerbose("No song bundle is found in sounds flolder");
        return false;
    }

    //go through and checkout out all the paths
    for(int i = 0; i < m_dir.size(); i++){
        if ( !m_dir[i].isDirectory()){
            ofLogVerbose("You should not put file in songs folder.");
            ofSleepMillis(5000);
            return false;
        }else{
            ofLogVerbose("found song bundle:" + m_dir[i].getFileName());
            if ( !m_dir[i].doesFileExist( m_dir[i].getAbsolutePath() + "/init.3dj")){
                ofLogVerbose("Error, didn't find init.3dj in song bundle: " + m_dir[i].getFileName());                
                ofSleepMillis(5000);
            }
        }
    }

    m_cursor = 0;
    return true;
}

bool CSongs::load()
{
    return load("sounds");
}

void CSongs::unload()
{
    m_dir.close();
}

bool CSongs::getFirst(string& songName, mapEntity& mapSong)
{
    m_cursor = 0;
    string filePath = m_dir.getPath( 0 ) + "/init.3dj";
    ofLogVerbose("Loading:" + filePath);
    m_configFile.loadFromFile( filePath, mapSong, false );
    songName = mapSong["soundName"].value;

    return true;
}

bool CSongs::getNext( string& songName, mapEntity& mapSong)
{
    m_cursor++;
    if ( m_cursor >= m_dir.size() )
    {
        m_cursor = 0;
    }
    
    string filePath = m_dir.getPath( m_cursor ) + "/init.3dj";
    ofLogVerbose("Loading: " + filePath);
    m_configFile.loadFromFile( filePath, mapSong, false );
    songName = mapSong["soundName"].value;

    return true;
}

bool CSongs::getCurrent( string& songName, mapEntity& mapSong)
{    
    string filePath = m_dir.getPath( m_cursor ) + "/init.3dj";
    m_configFile.loadFromFile( filePath, mapSong, false );
    songName = mapSong["soundName"].value;

    return true;
}

bool CSongs::isLast()
{
    return (m_cursor == (m_dir.size()-1) );
}
