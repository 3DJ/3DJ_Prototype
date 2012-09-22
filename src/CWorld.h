//
//  CWorld.h
//  Kinect_3DJ
//
//  Created by Samuel Ruberti on 6/30/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef Kinect_3DJ_World_h
#define Kinect_3DJ_World_h
#include "Entity.h"
#include "BoxButton.h"
#include "ControlBoxButton.h"
#include "KinectData.h"
#include "PointView.h"
#include "EQView.h"
#include "SonicOcean.h"
#include "CNavigationUIController.h"
#include <vector>

using namespace std;

//===========================================================
// Class : CWorld
// The entire world in which all entities exist
//===========================================================
class CWorld
{

public:

    CWorld();
    ~CWorld();

    void render();

    void effectBoxbutton();

    void setUpTranslation();

    void update(double time_since_last_update);
    void addBoxButton(CBoxButton * _boxButton);
    void clearButtons();
    void handleCollisions(ofPoint * XYZ);
    void setInitialVolume (float  volumeLevel) ;
    void drawDepthPointsAndTestHits();

    //stuff for OpenNI=========================================
    CKinectData m_oniKinect;


    //Stuff For Buttons========================================

    CBoxButton *m_a1Button;
    CBoxButton *m_a2Button;
    CBoxButton *m_a3Button;
    CBoxButton *m_a4Button;

    CBoxButton *m_b1Button;
    CBoxButton *m_b2Button;
    CBoxButton *m_b3Button;
    CBoxButton *m_b4Button;

    CBoxButton *m_c1Button;
    CBoxButton *m_c2Button;
    CBoxButton *m_c3Button;
    CBoxButton *m_c4Button;

    bool m_isRepeat;
    double m_totalTime;
    int m_scale;
    int m_angle;
    int m_red,m_green, m_blue, m_alpha;
    int m_background_r, m_background_g, m_background_b;
    int m_boxSize, m_boxCenterX, m_boxCenterY;
    vector<CBoxButton *> m_boxButtons;

    CPointView * m_pointView;
    ofEasyCam *m_easyCam;
    CEQView *m_equalizerView;
    CSonicOcean *m_sonicOcean;
    
    CNavigationUIController *m_navigationController;
    
};

#endif
