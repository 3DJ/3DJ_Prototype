//
//  CWorld.cpXYZ
//  Kinect_3DJ
//
//  Created by Samuel Ruberti on 6/30/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "CWorld.h"

CWorld::CWorld()
{
    //Set up Kinect
	m_oniKinect.setup();

	m_background_r = 100;
    m_background_g = 100;
    m_background_b = 100;
    m_gradientColorOutside = ofColor(24);
    m_gradientColorInside = ofColor(64);
    
    //Setup Scale ratio to map Kinect depth image to screen and buttons
    m_WidthScale = 1.0f;
    m_HeightScale = 1.0f;
    m_scale = scaleRatioForKinectDepthMap();

    //SET UP BUTTONS and add all buttons to world vector============
    //    x, y, z, box size, r, g, b, a, music sample name
    //==============================================================
    m_red               = 255;
    m_green             = 255;
    m_blue              = 255;
    m_alpha             = 30;
    m_boxSize           = 200;
    m_boxCenterX        = 200;
    m_boxCenterY        = 200;
    m_boxCenterZ        = 0;

    //Row A
    m_a1Button = new CBoxButton(500, -270, m_boxCenterZ, m_boxSize,m_red,0,0,m_alpha,"sounds/SSP/SSP_BeatsNLeads.wav");
    addBoxButton(m_a1Button);
    m_a2Button = new CBoxButton(167, -270, m_boxCenterZ, m_boxSize,m_red,m_green,m_blue,m_alpha,"sounds/SSP/SSP_BassFills.wav");
    addBoxButton(m_a2Button);
    m_a3Button = new CBoxButton(-167,-270,m_boxCenterZ, m_boxSize,m_red,m_green,m_blue,m_alpha,"sounds/SSP/SSP_Bass_02.wav");
    addBoxButton(m_a3Button);
    m_a4Button = new CBoxButton(-500, -270, m_boxCenterZ, m_boxSize, m_red,m_green,m_blue,m_alpha, "sounds/SSP/SSP_Bass_01.wav");
    m_a4Button->m_soundPlayer.setVolume(0.60f);
    addBoxButton(m_a4Button);
    
    //Row B
    m_b1Button = new CBoxButton(500, 0, m_boxCenterZ, m_boxSize,m_red,m_green,m_blue,m_alpha,"sounds/SSP/SSP_Oh.wav");
    addBoxButton(m_b1Button);
    m_b2Button = new CBoxButton(167, 0, m_boxCenterZ, m_boxSize,m_red,m_green,m_blue,m_alpha,"sounds/SSP/SSP_Hero_Button_Long.wav");
    addBoxButton(m_b2Button);
    m_b3Button = new CBoxButton(-167, 0, m_boxCenterZ, m_boxSize,m_red,m_green,m_blue,m_alpha,"sounds/SSP/SSP_Hero_Button_Short.wav");
    addBoxButton(m_b3Button);
    m_b4Button = new CBoxButton(-500,0,m_boxCenterZ, m_boxSize,m_red,m_green,m_blue,m_alpha,"sounds/SSP/SSP_Press_The_Superhero.wav");
    addBoxButton(m_b4Button);
    
    //Row C
    m_c1Button = new CLoopBoxButton(500, 270, m_boxCenterZ, m_boxSize,m_red,m_green,m_blue,m_alpha,"");
    addBoxButton(m_c1Button);
    m_c2Button = new CBoxButton(167, 270, m_boxCenterZ, m_boxSize, m_red,m_green,m_blue,m_alpha,"sounds/SSP/SSP_Oh.wav");
    addBoxButton(m_c2Button);
    m_c3Button = new CBoxButton(-167, 270, m_boxCenterZ, m_boxSize,m_red,m_green,m_blue,m_alpha,"sounds/SSP/SSP_Leads_N_Pads.wav");
    addBoxButton(m_c3Button);
    m_c4Button = new CBoxButton(-500, 270,m_boxCenterZ, m_boxSize,m_red,m_green,m_blue,m_alpha,"sounds/SSP/SSP_Pad_01.wav");
    addBoxButton(m_c4Button);

    setInitialVolume(1.0f);

    m_pointView     = new CPointView();
    m_easyCam       = new ofEasyCam;
    //m_easyCam->setFov(40);
    //m_easyCam->setTarget(ofVec3f(ofGetWidth()/2,ofGetHeight()/2,0));

    m_equalizerView = new CEQView;
    m_sonicOcean    = new CSonicOcean;

    m_isRepeat      = false;
    
    m_navigationController = new CNavigationUIController();
}

CWorld::~CWorld()
{
    for( vector<CBoxButton *>::iterator eachBox = m_boxButtons.begin(); eachBox != m_boxButtons.end(); eachBox++)
    {// delete all boxButtons
        delete (*eachBox);
    }

    if(m_pointView) delete m_pointView;
    if(m_easyCam) delete m_easyCam;
    if(m_equalizerView) delete m_equalizerView;
    if(m_sonicOcean) delete m_sonicOcean;
    if(m_navigationController) delete m_navigationController;
}


void CWorld::render()
{
    ofBackgroundGradient(m_gradientColorInside,m_gradientColorOutside);
    m_easyCam->begin();
    //setUpTranslation();             //Set up translation for all drawing
    
    ofPushMatrix();
    ofScale(-1, 1);
    ofRotateX(180);
    effectBoxbutton();              // render boxbutton and handle the sound.
    if(m_oniKinect.m_isTracking){ drawDepthPointsAndTestHits();}   // Do both here so we only look up the m_oniKinect data once...
    ofPopMatrix();

    ofPushMatrix();                 // ofPushMatrix before ofTranslate.
    ofTranslate(0, -1.5*ofGetHeight(), -5000);
    m_sonicOcean->drawEQSonicOcean();//EQ OCEAN
    ofPopMatrix();
    m_easyCam->end();
    //m_equalizerView->drawEQRect();
   
    m_navigationController->m_navConButtons->render();
   
    string msg = "Scale : " + ofToString(m_scale,2);
    ofDrawBitmapString(msg, ofGetWindowWidth()/2, ofGetWindowHeight()/2);
}

void CWorld::update(double time_since_last_update)
{
	//ofBackground(m_background_r, m_background_g, m_background_b);
    //ofBackgroundGradient(ofColor(0), ofColor(25,22,10));

    m_oniKinect.update();
    m_equalizerView->soundUpdate();
    m_sonicOcean->soundUpdate();
    m_navigationController->m_navConButtons->update(time_since_last_update);
}

void CWorld::drawDepthPointsAndTestHits()
{
    int w = m_oniKinect.m_recordUser.getWidth();
	int h = m_oniKinect.m_recordUser.getHeight();
    
	int step = 5;
	for(int y = 0; y < h; y += step) {
		for(int x = 0; x < w; x += step) {
            ofPoint XYZ = m_oniKinect.m_recordUser.getWorldCoordinateAt(x, y, m_oniKinect.m_numberOfUsersToTrack);
            if (XYZ.z > 0) {
                XYZ.x = (XYZ.x - w/2)*m_scale;
                XYZ.y = (XYZ.y - h/2)*m_scale;
                XYZ.z -= 1000;
                handleCollisions(&XYZ); //check for hits for all buttons
                m_pointView->addPoint(XYZ.x, XYZ.y, XYZ.z);
            }
		}
	}
    
    m_pointView->uploadDataToVbo();
    m_pointView->drawParticles();
    m_pointView->clearData();
}


void CWorld::addBoxButton(CBoxButton * _boxButton)
{
    m_boxButtons.push_back(_boxButton);
}

void CWorld::handleCollisions(ofPoint *XYZ)
{
    for ( vector<CBoxButton *>::iterator eachBox = m_boxButtons.begin(); eachBox != m_boxButtons.end(); eachBox++ )
    {
        (*eachBox)->collisionTest(XYZ); //test Each Box for hits
    }
    m_navigationController->m_navConButtons->collisionTest(XYZ);
}

void CWorld::clearButtons()
{
    for ( vector<CBoxButton *>::iterator eachBox = m_boxButtons.begin(); eachBox != m_boxButtons.end(); eachBox++ )
    {
        (*eachBox)->clear();
    }
}

void CWorld::setInitialVolume(float volumeLevel)
{
    for ( vector<CBoxButton *>::iterator eachBox = m_boxButtons.begin(); eachBox != m_boxButtons.end(); eachBox++ )
    {
        (*eachBox)->m_soundPlayer.setVolume(volumeLevel);
    }

}

void CWorld::setUpTranslation()
{
    
    //ofTranslate(0, 0, -500); // center the points a bit
                      //Rotate around Axis

    //ofTranslate(0,0,500);            // Move back into Camera View
    //ofTranslate(m_scale ,m_scale, m_scale *-800 + 1000);
    //ofScale(m_scale,m_scale,m_scale);
}

void CWorld::effectBoxbutton()
{
    for ( vector<CBoxButton *>::iterator eachBox = m_boxButtons.begin(); eachBox != m_boxButtons.end(); eachBox++)
    {
        if ( (*eachBox)->isLoopBox() && (*eachBox)->isCurrentlyHit() )
        {// when the current hit boxButton is loop control box, open repeat switch of world.
            m_isRepeat             = true;
        }
        if ( m_isRepeat && !(*eachBox)->isLoopBox() && (*eachBox)->isCurrentlyHit() )
        {// do not repeat the control boxButton. And close the repeat switch when it touched once.
            (*eachBox)->m_isRepeat = true;
            m_isRepeat             = false;
        }

        (*eachBox)->render(); // Draw BoxButtons and Handle Sound.
    }
}

float CWorld::scaleRatioForKinectDepthMap()
{
    float w = 640.0f;
    float h = 480.0f;
    float screenW = float(ofGetScreenWidth());
    float screenH = float(ofGetScreenHeight());
    
    if((w/h) < (screenW/screenH)){
        return screenW/w;
    }else {
        return screenH/h;
    }
}
