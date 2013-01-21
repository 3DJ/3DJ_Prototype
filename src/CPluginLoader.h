//
//  CBoxButton.cpp
//  Kinect_3DJ
//
//  Created by LJ on 10/1/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef Kinect_3DJ_PluginLoader_h
#define Kinect_3DJ_PluginLoader_h

#include <string>
#include <iostream>
using namespace std;

#include "XnOS.h"
#include "ofMain.h"

class CPluginLoader{
public:
    bool loadPlugin( string filePath );
    bool loadFromDir(  );
};

#endif
