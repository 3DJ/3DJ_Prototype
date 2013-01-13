//
//  CBoxButton.cpp
//  Kinect_3DJ
//
//  Created by LJ on 1/10/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include "ConfigFile.h"

bool CConfigFile::loadFromFile( string filePath, mapEntity& mapDataPool )
{    
    if (m_ofxXmlFile.loadFile( filePath )){
        cout<<"Load file to " << filePath << " success" <<endl;
    }
    else{
        cout<<"Load file to " << filePath << " failed" <<endl;
        return false;
    }
    // clear the pool and then load it from file.
    mapDataPool.clear();
    string val;
    string number = m_ofxXmlFile.getValue("number", val );
    int count = stringToInt( number );
    int index = 0;
    // using this "_" to name the tag. tiny xml not allow to name tag with number.
    string underScore = "_";    

    SEntity entity;
    entity.isSaved = true;
    for ( int index = 0; index < count; index++ )
    {
        string key = m_ofxXmlFile.getAttribute( underScore + intToString(index), "key", val, 0);
        entity.value = m_ofxXmlFile.getValue( underScore + intToString(index), val );
        mapDataPool[key] = entity;
    }

    return true;
}

bool CConfigFile::saveToFile( string filePath, mapEntity& mapDataPool)
{
//     fstream fs(filePath, fstream::out | fstream::trunc);
//     fs<<"";
//     fs.close();
    
    m_ofxXmlFile.addTag("3-dj");
    m_ofxXmlFile.setAttribute("3-dj", "link", "www.3-dj.com", 0);
    m_ofxXmlFile.pushTag("3-dj");    
    int index = 0;
    int number = 0; // the saving number of data
    // using this "_" to name the tag. tiny xml not allow to name tag with number.
    string underScore = "_";
    for ( mapEntity::iterator it = mapDataPool.begin(); it != mapDataPool.end(); it++ )
    {
        if ( it->second.isSaved )
        {
            m_ofxXmlFile.addTag( underScore + intToString(index));
            m_ofxXmlFile.setAttribute( underScore + intToString(index), "key", it->first, 0);
            m_ofxXmlFile.setValue( underScore + intToString(index), it->second.value );
            number ++;
        }
        index ++;
    }

    m_ofxXmlFile.addTag("number");
    m_ofxXmlFile.setValue("number", intToString( number ) );
    m_ofxXmlFile.popTag();
    if (m_ofxXmlFile.saveFile( filePath )){
        cout<<"Save file to " << filePath << " success" <<endl;
    }
    else{
        cout<<"Save file to " << filePath << " failed" <<endl;
        return false;
    }

    return true;
}
