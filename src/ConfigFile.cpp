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
        cout<<"Load file success" <<endl;
    }
    else{
        cout<<"Load file failed" <<endl;
        return false;
    }

    string val;
    string number = m_ofxXmlFile.getValue("number", val );
    int count = stringToInt( number );
    int index = 0;
    // using this "_" to name the tag. tiny xml not allow to name tag with number.
    string underScore = "_";
    // clear the pool and then load it from file.
    mapDataPool.clear();
    for ( int index = 0; index < count; index++ )
    {
        string key = m_ofxXmlFile.getAttribute( underScore + intToString(index), "key", val, 0);
        mapDataPool[key] = m_ofxXmlFile.getValue( underScore + intToString(index), val );
    }

    return true;
}

bool CConfigFile::saveToFile( string filePath, mapEntity& mapDataPool)
{
    m_ofxXmlFile.addTag("3-dj");
    m_ofxXmlFile.setAttribute("3-dj", "link", "www.3-dj.com", 0);
    m_ofxXmlFile.pushTag("3-dj");
    m_ofxXmlFile.addTag("number");
    m_ofxXmlFile.setValue("number", intToString(mapDataPool.size()) );
    int index = 0;
    // using this "_" to name the tag. tiny xml not allow to name tag with number.
    string underScore = "_";
    for ( mapEntity::iterator it = mapDataPool.begin(); it != mapDataPool.end(); it++ )
    {
        m_ofxXmlFile.addTag( underScore + intToString(index));
        m_ofxXmlFile.setAttribute( underScore + intToString(index), "key", it->first, 0);
        m_ofxXmlFile.setValue( underScore + intToString(index), it->second );
        index ++;
    }
    m_ofxXmlFile.popTag();
    if (m_ofxXmlFile.saveFile( filePath )){
        cout<<"Saving file success" << endl;
    }
    else{
        cout<<"Saving file failed" <<endl;
        return false;
    }

    return true;
}
