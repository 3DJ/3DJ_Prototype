//
//  CBoxView.h
//  Kinect_3DJ
//
//  Created by Samuel Ruberti on 6/30/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef Kinect_3DJ_CBoxView_h
#define Kinect_3DJ_CBoxView_h
#include "Entity.h"
#include "BoxButton.h"
#include "ControlBoxButton.h"
#include "KinectData.h"
#include "PointView.h"
#include "EQView.h"
#include <vector>
#include "SnakeFish.h"
#include "Particles.h"
#include "Interface.h"
#include "CHands.h"
#include "CSongs.h"

using namespace Interface;
using namespace std;

//===========================================================
// Class : CBoxView
// The box viewer
//===========================================================
class CBoxView:public IView
{// draw the box on the screen and handle sounds of box.
public:

    CBoxView();
    ~CBoxView();

    bool draw();

private:
    // render the box and body on the screen.
    void render();
    // handle the box sounds and draw boxes on the screen
    void renderBoxes();

    void addBoxButton(CBoxButton * _boxButton);
    void drawDepthPoints();
    void reloadSounds();
    float scaleRatioForKinectDepthMap();

    //stuff for OpenNI=========================================
    CKinectData* m_oniKinect;
    
    //Stuff For Buttons========================================
    CBoxButton *m_controlButton_1;

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
    vector<CBoxButton *> *m_boxButtons;
    ofColor m_gradientColorOutside, m_gradientColorInside;
    int m_background_r, m_background_g, m_background_b;
    float m_scale;

    CPointView * m_pointView;
    ofEasyCam * m_easyCam;
    CEQView *m_equalizerView;
    SnakeFish *m_snakeFish;
    Particles *m_particles;

    float m_WidthScale, m_HeightScale;
    float m_playerDepth;
    CHands *m_hands;
};

#endif
