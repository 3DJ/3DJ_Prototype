//
//  CWorld.h
//  Kinect_3DJ
//
//  Created by Samuel Ruberti on 6/30/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef Kinect_3DJ_CWorld_h
#define Kinect_3DJ_CWorld_h
#include <iostream>
#include "Interface.h"
using namespace Interface;
using namespace std;

//===========================================================
// Class : CWorld
// The entire world in which all entities exist
//===========================================================

typedef enum st {
    ST_None = 0,
    ST_MENU_STATE,
    ST_BOX_STATE,
}CurrentState;

extern CurrentState g_currentState;
class CWorld
{

public:

    // singleton this class. becos we just need one world.
    static CWorld& getInstance(){
        static CWorld _instance;
        return _instance;
    }

    ~CWorld();

    bool init( IController* controller = 0, IView* view = 0);

    void render();   

    void update(double time_since_last_update);
    
private:
    // singleton this class. becos we just need one world.
    CWorld();
    CWorld( const CWorld& );
    CWorld& operator=( const CWorld&);

    IController* m_controller;
    IView* m_view;
};

#endif
