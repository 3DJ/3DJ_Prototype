//
//  CWorld.cpXYZ
//  Kinect_3DJ
//
//  Created by Samuel Ruberti on 6/30/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "World.h"

CWorld::CWorld()
{
    //Set up Kinect
	m_oniKinect.setup();

	m_angle = 20; // 20 degree tilt on startup
	//m_oniKinect.setCameraTiltAngle(m_angle);

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

    //Row A
    m_a1Button = new CBoxButton(375, -250, 1000, m_boxSize,m_red,m_green,m_blue,m_alpha,"sounds/Melody/GuitarStrummin.wav");
    addBoxButton(m_a1Button);
    m_a2Button = new CBoxButton(125, -250, 1000,m_boxSize,m_red,m_green,m_blue,m_alpha,"sounds/Melody/Piano.wav");
    addBoxButton(m_a2Button);
    m_a3Button = new CBoxButton(-125,-250,1000,m_boxSize,m_red,m_green,m_blue,m_alpha,"sounds/Melody/GuitarPick.wav");
    addBoxButton(m_a3Button);
    m_a4Button = new CBoxButton(-375, -250, 1000, m_boxSize, m_red,m_green,m_blue,m_alpha, "sounds/Melody/Blip_Melody_01.wav");
    m_a4Button->m_soundPlayer.setVolume(0.60f);
    addBoxButton(m_a4Button);

    //Row B
    m_b1Button = new CBoxButton(375, 0, 1000, m_boxSize,m_red,m_green,m_blue,m_alpha,"sounds/Effects/Warp_1.wav");
    addBoxButton(m_b1Button);
    m_b2Button = new CBoxButton(125, 0, 1000, m_boxSize,m_red,m_green,m_blue,m_alpha,"sounds/Effects/Uplifter.wav");
    addBoxButton(m_b2Button);
    m_b3Button = new CBoxButton(-125, 0, 1000,m_boxSize,m_red,m_green,m_blue,m_alpha,"sounds/Bass/BassSlap.wav");
    addBoxButton(m_b3Button);

    m_b4Button = new CBoxButton(-375,0,1000,m_boxSize,m_red,m_green,m_blue,m_alpha,"sounds/Bass/NastyBass.wav");
    addBoxButton(m_b4Button);

    //Row C
    m_c1Button = new CLoopBoxButton(375, 250, 1000,m_boxSize,m_red,m_green,m_blue,m_alpha,"sounds/Effects/Vinyl_Scratch_01.wav");
    addBoxButton(m_c1Button);
    m_c2Button = new CBoxButton(125, 250, 1000,m_boxSize, m_red,m_green,m_blue,m_alpha,"sounds/Effects/RemixCrazyScratch_FX_02.wav");
    addBoxButton(m_c2Button);
    m_c3Button = new CBoxButton(-125, 250, 1000,m_boxSize,m_red,m_green,m_blue,m_alpha,"sounds/Beat/TimbalesMerged_1.wav");
    addBoxButton(m_c3Button);
    m_c4Button = new CBoxButton(-375, 250,1000,m_boxSize,m_red,m_green,m_blue,m_alpha,"sounds/Beat/Wee_Kick.wav");
    addBoxButton(m_c4Button);

    setInitialVolume(1.0f);
    m_scale =3;

    m_pointView     = new CPointView();
    m_easyCam       = new ofEasyCam;
    //m_easyCam->setFov(40);
    //m_easyCam->setTarget(ofVec3f(ofGetWidth()/2,ofGetHeight()/2,0));

    m_equalizerView = new CEQView;
    m_sonicOcean    = new CSonicOcean;

    m_isRepeat      = false;
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
}


void CWorld::render()
{
    m_easyCam->begin();

    m_oniKinect.draw(); //draw top Left dot user tracking indicator

    setUpTranslation();             //Set up translation for all drawing
    effectBoxbutton();              // render boxbutton and handle the sound.
    drawDepthPointsAndTestHits();   // Do both here so we only look up the m_oniKinect data once...
    ofPopMatrix();

    ofPushMatrix();                 // ofPushMatrix before ofTranslate.
    ofTranslate(0, -1.5*ofGetHeight(), -5000);
    m_sonicOcean->drawEQSonicOcean();//EQ OCEAN
    ofPopMatrix();
    m_easyCam->end();
    //m_equalizerView->drawEQRect();
}

void CWorld::update(double time_since_last_update)
{
	ofBackground(100, 100, 100);
    //ofBackgroundGradient(ofColor(0), ofColor(25,22,10));

    m_oniKinect.update();
    m_equalizerView->soundUpdate();
    m_sonicOcean->soundUpdate();
}

void CWorld::drawDepthPointsAndTestHits()
{
    int w = m_oniKinect.m_recordUser.getWidth();
	int h = m_oniKinect.m_recordUser.getHeight();

	int step = 5;
	for(int y = 0; y < h; y += step) {
		for(int x = 0; x < w; x += step) {
            ofPoint XYZ = m_oniKinect.m_recordUser.getWorldCoordinateAt(x, y, m_oniKinect.m_numberOfUsersToTrack);
            //if (XYZ.z > 615 && XYZ.z < 2000) {
            XYZ.x = (XYZ.x - w/2)*1.5;
            XYZ.y = (XYZ.y - h/2)*1.5;

            handleCollisions(&XYZ); //check for hits for all buttons
            m_pointView->addPoint(XYZ.x, XYZ.y, XYZ.z);
            //}
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
    ofPushMatrix();
    ofScale(-1, 1);
    ofTranslate((ofGetWidth()/2)-320, (ofGetHeight()/2) -240, -1000); // center the points a bit
    ofRotateX(180);                   //Rotate around Axis

    // ofTranslate(0,0,1000);            // Move back into Camera View
    ofTranslate(m_scale ,m_scale, m_scale *-800 + 1000);
    ofScale(m_scale,m_scale,m_scale);
}

void CWorld::effectBoxbutton()
{
    for ( vector<CBoxButton *>::iterator eachBox = m_boxButtons.begin(); eachBox != m_boxButtons.end(); eachBox++)
    {
        if ( (*eachBox)->isLoopBox() && (*eachBox)->isCurrentlyHit() )
        {// when the current hit boxButton is loop control box, open repeat switch of world.
            m_isRepeat             = true;
        }
        if ( m_isRepeat && !(*eachBox)->isLoopBox() )
        {// do not repeat the control boxButton. And close the repeat switch when it touched once.
            (*eachBox)->m_isRepeat = true;
            m_isRepeat             = false;
        }

        (*eachBox)->render(); // Draw BoxButtons and Handle Sound.
    }
}

