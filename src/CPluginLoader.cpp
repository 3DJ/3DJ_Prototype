//
//  CBoxButton.cpp
//  Kinect_3DJ
//
//  Created by LJ on 10/1/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include "CPluginLoader.h"

bool CPluginLoader::loadPlugin(string filePath)
{
    XN_LIB_HANDLE pLib;
    if ( xnOSLoadLibrary( filePath.c_str(), &pLib) ){
        return false;
    }

    return true;
}

bool CPluginLoader::loadFromDir()
{
    string  path;
    //some path, may be absolute or relative to bin/data
#ifdef TARGET_OSX
    path = "linux";
#else
    path = "win";
#endif
    ofDirectory dir(path);
    string str = dir.getAbsolutePath();
    //only show dll files
    //dir.allowExt("png");
    //populate the directory object
    dir.listDir();

    //go through and print out all the paths
    for(int i = 0; i < dir.numFiles(); i++){
        cout << dir.getPath(i) << endl;
        loadPlugin( dir.getPath(i));
    }
}
