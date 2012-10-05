//
//  CBoxButton.cpp
//  Kinect_3DJ
//
//  Created by LJ on 10/1/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef Kinect_3DJ_Common_h
#define Kinect_3DJ_Common_h

#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <map>
using namespace std;

namespace Common{

    // u can add member in the structure.
    struct SEntity{
        bool isSaved;
        string value;        
    };
    typedef map<string, SEntity> mapEntity;

    float stringToFloat( string val );

    string floatToString( float f );

    int stringToInt( string val);

    string intToString( int i);
};

#endif
