//
//  CBoxButton.cpp
//  Kinect_3DJ
//
//  Created by LJ on 1/10/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include "ConfigFile.h"

bool CConfigFile::loadFromFile( string filePath, mapEntity& mapData, bool isSaved )
{    
    if (m_ofxXmlFile.loadFile( filePath )){
        cout<<"Load file from " << filePath << " success" <<endl;
    }
    else{
        cout<<"Load file from " << filePath << " failed... Is your xml valid" <<endl;
        return false;
    }
    
    string val;
    string number = m_ofxXmlFile.getValue("number", val );
    int count = stringToInt( number );

    // using this "_" to name the tag. tiny xml not allow to name tag with number.
    string underScore = "_";

    SEntity entity;
    entity.isSaved = isSaved;
    for ( int index = 1; index <= count; index++ )
    {
        string key = m_ofxXmlFile.getAttribute( underScore + intToString(index), "key", val, 0);
        entity.value = m_ofxXmlFile.getValue( underScore + intToString(index), val );
        mapData[key] = entity;
    }
    m_ofxXmlFile.clear();

    return true;
}

bool CConfigFile::saveToFile( string filePath, mapEntity& mapData)
{
    // remove the file if it exists. becoz the ofxxml just append the data. cannot rewrite the data.
    ofFile file;
    file.removeFile(filePath);
    file.close();

    m_ofxXmlFile.clear();       // clear the xml data first.
    m_ofxXmlFile.addTag("3-dj");
    m_ofxXmlFile.setAttribute("3-dj", "link", "www.3-dj.com", 0);
    m_ofxXmlFile.pushTag("3-dj");

    int index = 1;
    int number = 0; // the saving number of data
    // using this "_" to name the tag. tiny xml not allow to name tag with number.
    string underScore = "_";
    for ( mapEntity::iterator it = mapData.begin(); it != mapData.end(); it++ )
    {
        if ( it->second.isSaved )
        {
            number ++;
            m_ofxXmlFile.addTag( underScore + intToString(number));
            m_ofxXmlFile.setAttribute( underScore + intToString(number), "key", it->first, 0);
            m_ofxXmlFile.setValue( underScore + intToString(number), it->second.value );            
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
