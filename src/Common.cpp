//
//  CBoxButton.cpp
//  Kinect_3DJ
//
//  Created by LJ on 1/10/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include "Common.h"

namespace Common{

    float stringToFloat( string val )
    {
        return atof( val.c_str());
    }

    string floatToString( float f )
    {
        string str;
        str.resize(100);
        // to do: use sprintf_s.
        sprintf( (char *)str.c_str(), "%f", f );
        return str;
    }

    int stringToInt( string val)
    {
        return atoi( val.c_str());
    }

    string intToString( int i)
    {
        string str;
        str.resize(100);
        // to do: use sprintf_s.
        sprintf( (char *)str.c_str(), "%d", i );
        return str;
    }
};