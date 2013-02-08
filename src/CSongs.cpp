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
        return false;
    }

    //go through and checkout out all the paths
    for(int i = 0; i < m_dir.size(); i++){
        if ( !m_dir[i].isDirectory()){
            ofLogVerbose("You shound not put file in songs folder.");
            return false;
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
    string filePath = m_dir.getPath( 0 ) + "\\init.3dj";
    m_configFile.loadFromFile( filePath, mapSong, false );
    
    return true;
}

bool CSongs::getNext( string& songName, mapEntity& mapSong)
{
    m_cursor++;
    if ( m_cursor >= m_dir.size() )
    {
        m_cursor = 0;
    }
    
    string filePath = m_dir.getPath( m_cursor ) + "\\init.3dj";
    m_configFile.loadFromFile( filePath, mapSong, false );

    return true;
}

bool CSongs::getCurrent( string& songName, mapEntity& mapSong)
{    
    string filePath = m_dir.getPath( m_cursor ) + "\\init.3dj";
    m_configFile.loadFromFile( filePath, mapSong, false );

    return true;
}

bool CSongs::isLast()
{
    return (m_cursor == (m_dir.size()-1) );
}