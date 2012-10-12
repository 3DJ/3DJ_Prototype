//
//  World.h
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
#include <vector>

using namespace std;

typedef struct{
    CBoxButton *box1;
    CBoxButton *box2;
}SSwapBoxes;

//===========================================================
// Class : World
// The entire world in which all entities exist
//===========================================================
class World
{

public:

    World();

    void initializeBoxButton( int xDistance, int yDistance, int zDistance );

    ~World();

    void render();

    void effectBoxbutton();

    void swapDouble( vector<CBoxButton *>::iterator eachBox );

    void setCurHitControlFlags( vector<CBoxButton *>::iterator eachBox );
    void setUnHitControlFlags( vector<CBoxButton *>::iterator eachBox );

    void setUpTranslation();

    void update(double time_since_last_update);
    void addBoxButton(CBoxButton * _boxButton);
    void clearButtons();
    void handleCollisions(ofPoint * XYZ);
    void setInitialVolume(float volumeLevel);
    void drawDepthPointsAndTestHits();    
    void swapBoxes( SSwapBoxes &boxes );

    void baseSwapBoxes( CBoxButton *box1, CBoxButton *box2);

    void scrollLeftBoxes(bool scrollDown);  // true for down, false for up
    //stuff for OpenNI=========================================
    CKinectData m_oniKinect;

    // events
    ofEvent<SSwapBoxes> eventSwapBoxes;

    //Stuff For Buttons========================================

    CBoxButton *m_a1Button;
    CBoxButton *m_a2Button;
    CBoxButton *m_a3Button;
    CBoxButton *m_a4Button;

    CBoxButton *m_b1Button;
    CBoxButton *m_b2Button;
    CBoxButton *m_b3Button;
    CBoxButton *m_b4Button;
    CBoxButton *m_b5Button;

    CBoxButton *m_c1Button;
    CBoxButton *m_c2Button;
    CBoxButton *m_c3Button;
    CBoxButton *m_c4Button;

    bool m_repeatFlag;
    float  m_pan;
    float  m_volume;
    float  m_setVolume;
    float  m_speed;
    bool m_swapBoxes;
    bool m_scrollLeftBoxes;
    CBoxButton *m_previousBox;


    double m_totalTime;
    int m_scale;
    int m_angle;
    int m_red,m_green, m_blue, m_alpha;
    int m_boxSize, m_boxCenterX, m_boxCenterY;
    vector<CBoxButton *> m_boxButtons;
    vector<CBoxButton *> m_leftButtons;

    CPointView * m_pointView;
    ofEasyCam *m_easyCam;
    CEQView *m_equalizerView;
    CSonicOcean *m_sonicOcean;

};

#endif
