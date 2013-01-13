//
//  CBoxButton.cpp
//  Kinect_3DJ
//
//  Created by LJ on 10/1/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef Kinect_3DJ_ConfigFile_h
#define Kinect_3DJ_ConfigFile_h

#include <string>
using namespace std;

#include "Common.h"
#include "ofxXmlSettings.h"
using namespace Common;

class CConfigFile{
public:
    bool loadFromFile( string filePath, mapEntity& mapDataPool );
    bool saveToFile( string filePath, mapEntity& mapDataPool);

private:
    ofxXmlSettings m_ofxXmlFile;
};

#endif
