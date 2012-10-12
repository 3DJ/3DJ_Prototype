//
//  World.cpXYZ
//  Kinect_3DJ
//
//  Created by Samuel Ruberti on 6/30/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "World.h"


World::World()
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
    m_boxSize           = 250;
    m_boxCenterX        = 200;
    m_boxCenterY        = 200;

    int xDistance     = 250;
    int yDistance     = 250;
    int zDistance     = 1000;
    // initialize the box button.
    initializeBoxButton(xDistance, yDistance, zDistance);

    setInitialVolume(1.0f);
    m_scale =3;

    m_pointView     = new CPointView();
    m_easyCam       = new ofEasyCam;
    //m_easyCam->setFov(40);
    //m_easyCam->setTarget(ofVec3f(ofGetWidth()/2,ofGetHeight()/2,0));

    m_equalizerView = new CEQView;
    m_sonicOcean    = new CSonicOcean;

    m_repeatFlag      = false;
    m_speed       = 1.0f;
    m_volume      = 1.0f;
    m_setVolume   = 1.0f;
    m_swapBoxes   = false;
    m_previousBox = 0;
    m_scrollLeftBoxes = true;
    // add listener on events
    ofAddListener( eventSwapBoxes, this, &World::swapBoxes );
}

World::~World()
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


void World::render()
{
    m_easyCam->begin();

    setUpTranslation();             //Set up translation for all drawing

    effectBoxbutton();              // render boxbutton and handle the sound.
    if(m_oniKinect.m_isTracking)
    {  // Do both here so we only look up the m_oniKinect data once...
        drawDepthPointsAndTestHits();
    }

    ofPopMatrix();

    ofPushMatrix();                 // ofPushMatrix before ofTranslate.
    ofTranslate(0, -1.5*ofGetHeight(), -5000);
    m_sonicOcean->drawEQSonicOcean();//EQ OCEAN
    ofPopMatrix();
    m_easyCam->end();
    //m_equalizerView->drawEQRect();
}

void World::update(double time_since_last_update)
{
	ofBackground(100, 100, 100);
    //ofBackgroundGradient(ofColor(0), ofColor(25,22,10));

    m_oniKinect.update();
    m_equalizerView->soundUpdate();
    m_sonicOcean->soundUpdate();
}

void World::drawDepthPointsAndTestHits()
{
    int w = m_oniKinect.m_recordUser.getWidth();
	int h = m_oniKinect.m_recordUser.getHeight();

	int step = 5;
	for(int y = 0; y < h; y += step) {
		for(int x = 0; x < w; x += step) {
            ofPoint XYZ = m_oniKinect.m_recordUser.getWorldCoordinateAt(x, y, m_oniKinect.m_numberOfUsersToTrack);
            if (XYZ.z > 0) {
            XYZ.x = (XYZ.x - w/2) * 2;
            XYZ.y = (XYZ.y - h/2) * 2;

            handleCollisions(&XYZ); //check for hits for all buttons
            m_pointView->addPoint(XYZ.x, XYZ.y, XYZ.z);
            }
		}
	}

    m_pointView->uploadDataToVbo();
    m_pointView->drawParticles();
    m_pointView->clearData();
}


void World::addBoxButton(CBoxButton * _boxButton)
{
    m_boxButtons.push_back(_boxButton);
}

void World::handleCollisions(ofPoint *XYZ)
{
    for ( vector<CBoxButton *>::iterator eachBox = m_boxButtons.begin(); eachBox != m_boxButtons.end(); eachBox++ )
    {
        (*eachBox)->collisionTest(XYZ); //test Each Box for hits
    }
}

void World::clearButtons()
{
    for ( vector<CBoxButton *>::iterator eachBox = m_boxButtons.begin(); eachBox != m_boxButtons.end(); eachBox++ )
    {
        (*eachBox)->clear();
    }
}

void World::setInitialVolume(float volumeLevel)
{
    for ( vector<CBoxButton *>::iterator eachBox = m_boxButtons.begin(); eachBox != m_boxButtons.end(); eachBox++ )
    {
        (*eachBox)->m_soundPlayer.setVolume(volumeLevel);
    }

}

void World::setUpTranslation()
{
    ofPushMatrix();
    ofScale(-1, 1);
    ofTranslate((ofGetWidth()/2)-320, (ofGetHeight()/2) -240, -1000); // center the points a bit
    ofRotateX(180);                   //Rotate around Axis

    // ofTranslate(0,0,1000);            // Move back into Camera View
    ofTranslate(m_scale ,m_scale, m_scale *-800 + 1000);
    ofScale(m_scale,m_scale,m_scale);
}

void World::effectBoxbutton()
{
    for ( vector<CBoxButton *>::iterator eachBox = m_boxButtons.begin(); eachBox != m_boxButtons.end(); eachBox++)
    {
        // set the status by control boxes's flags.
        if ( (*eachBox)->isCurrentlyHit() ){

            if ( m_swapBoxes )
            {
                swapDouble(eachBox);
            }

            setCurHitControlFlags(eachBox);
        }
        else{
            setUnHitControlFlags(eachBox);
        }

        (*eachBox)->render(); // Draw BoxButtons and Handle Sound.

    }
}

void World::initializeBoxButton( int xDistance, int yDistance, int zDistance )
{
    //Row A
    m_a1Button = new CBoxButton(xDistance*3/2, -yDistance, zDistance, m_boxSize,m_red,m_green,m_blue,m_alpha,"");
    m_a1Button->setupBoxButton( 1, 2000,  ET_SwapButton );
    m_leftButtons.push_back( m_a1Button );
    addBoxButton(m_a1Button);
    m_a2Button = new CBoxButton( xDistance/2 , -yDistance, zDistance,200,m_red,m_green,m_blue,m_alpha,"sounds/Melody/Piano.wav");
    addBoxButton(m_a2Button);
    m_a3Button = new CBoxButton( -xDistance/2, -yDistance,zDistance,m_boxSize,m_red,m_green,m_blue,m_alpha,"sounds/Melody/GuitarPick.wav");
    addBoxButton(m_a3Button);
    m_a4Button = new CBoxButton(-xDistance*3/2, -yDistance, zDistance, m_boxSize, m_red,m_green,m_blue,m_alpha, "sounds/Melody/Blip_Melody_01.wav");
    m_a4Button->m_soundPlayer.setVolume(0.60f);
    m_a4Button->setupBoxButton( 1 );
    addBoxButton(m_a4Button);

    //Row B
    m_b1Button = new CEffectBoxButton(xDistance*3/2, 0, zDistance, 200,m_red,m_green,m_blue,m_alpha,"");
    m_b1Button->setupBoxButton( 1, 2000, ET_EffectsButton);
    m_leftButtons.push_back( m_b1Button );
    addBoxButton(m_b1Button);
    m_b2Button = new CBoxButton(xDistance/2, 0, zDistance, m_boxSize,m_red,m_green,m_blue,m_alpha,"sounds/Effects/Uplifter.wav");
    addBoxButton(m_b2Button);
    m_b3Button = new CBoxButton(-xDistance/2, 0, zDistance,m_boxSize,m_red,m_green,m_blue,m_alpha,"sounds/Bass/BassSlap.wav");
    addBoxButton(m_b3Button);
    m_b4Button = new CBoxButton(-xDistance*3/2 , 0 ,zDistance,m_boxSize,m_red,m_green,m_blue,m_alpha,"sounds/Bass/NastyBass.wav");
    addBoxButton(m_b4Button);
    m_b5Button = new CBoxButton(-xDistance*3/2-250 ,0,zDistance,m_boxSize,m_red,m_green,m_blue,m_alpha,"");
    m_b5Button->setupBoxButton( 1, 2000, ET_ScrollLeftButtons);
    addBoxButton( m_b5Button );

    //Row C
    m_c1Button = new CLoopBoxButton(xDistance*3/2, yDistance, zDistance, 200, m_red, m_green, m_blue, m_alpha, "");
    m_c1Button->setupBoxButton( 1, 2000, ET_LoopButton );
    m_leftButtons.push_back( m_c1Button );
    addBoxButton(m_c1Button);
    m_c2Button = new CBoxButton(xDistance/2, yDistance, zDistance,m_boxSize, m_red,m_green,m_blue,m_alpha,"sounds/Effects/RemixCrazyScratch_FX_02.wav");
    addBoxButton(m_c2Button);
    m_c3Button = new CBoxButton(-xDistance/2, yDistance, zDistance,m_boxSize,m_red,m_green,m_blue,m_alpha,"sounds/Beat/TimbalesMerged_1.wav");
    addBoxButton(m_c3Button);
    m_c4Button = new CBoxButton(-xDistance*3/2, yDistance,zDistance,m_boxSize,m_red,m_green,m_blue,m_alpha,"sounds/Beat/Wee_Kick.wav");
    m_c4Button->setupBoxButton( 1 );
    addBoxButton(m_c4Button);
}

void World::setCurHitControlFlags( vector<CBoxButton *>::iterator eachBox )
{
    switch( (*eachBox)->getBoxType() )
    {
    case ET_LoopButton:
        {
            m_repeatFlag = true;
        }
        break;
    case ET_EffectsButton:
        {
            // set the world's flags.
            //m_speed = (*eachBox)->m_speed;
            m_volume = (*eachBox)->m_volume;
            //m_pan   = (*eachBox)->m_pan;
            //cout<<"m_speed"<<m_speed<<endl;
            //cout<<"m_pan"<<m_pan<<endl;
            //cout<<"m_volume"<<m_volume<<endl;
        }
        break;
    case ET_SwapButton:
        {
            m_swapBoxes = true;
            m_setVolume = 0;
        }
        break;
    case ET_ScrollLeftButtons:
        {
            // to test scroll up.
            if ( m_scrollLeftBoxes == true )
            {
                scrollLeftBoxes( true );
                m_scrollLeftBoxes = false;
            }
        }
        break;
    case ET_MusicSampleButton:
        {
            if ( m_repeatFlag )
            {// do not repeat the control boxButton. And close the repeat switch when it touched once.
                (*eachBox)->m_isRepeat = true;
                m_repeatFlag             = false;
            }
            // set the flags of each boxes.
            //(*eachBox)->m_speed = m_speed;
            //(*eachBox)->m_pan   = m_pan;
            (*eachBox)->m_volume = m_volume;
        }
        break;
    }
}


void World::setUnHitControlFlags( vector<CBoxButton *>::iterator eachBox )
{
    switch( (*eachBox)->getBoxType() )
    {
    case ET_EffectsButton:
        {
            m_speed = 1;
            m_volume = m_setVolume;
            m_pan   = 0;
        }
        break;
    case ET_MusicSampleButton:
        {
            (*eachBox)->m_speed = m_speed;
            (*eachBox)->m_volume = m_volume;
            (*eachBox)->m_pan   = m_pan;
        }
        break;
    case ET_SwapButton:
        {
            m_swapBoxes = false;
            m_previousBox = 0;
            m_setVolume  = 1.0f;
        }
        break;
    case ET_ScrollLeftButtons:
        {
            m_scrollLeftBoxes = true;
        }
        break;
    }
}

void World::swapBoxes( SSwapBoxes &boxes )
{
    baseSwapBoxes( boxes.box1, boxes.box2 );
}

void World::swapDouble( vector<CBoxButton *>::iterator eachBox )
{
    if ( (*eachBox)->getBoxType() == ET_MusicSampleButton )
    {
        // save the previous box
        if ( m_previousBox == 0)
        {
            m_previousBox = *eachBox;
        }
        else
        {
            baseSwapBoxes( m_previousBox, (*eachBox));
//             // emit the swap event to swapboxes. but it's not neccessary in here. just call baseSwapBoxes is okay
//             SSwapBoxes swapBoxes;
//             swapBoxes.box1 = m_previousBox;
//             swapBoxes.box2 = (*eachBox);
//             // for test the event-driven.
//             ofNotifyEvent( eventSwapBoxes, swapBoxes );
        }
    }
}

void World::scrollLeftBoxes( bool scrollDown)
{// true for down, false for up
    if ( scrollDown )
    {
        for ( int index = 0 ; index < m_leftButtons.size()-1 ; )
        {// iterate the left buttons
            baseSwapBoxes( m_leftButtons[index], m_leftButtons[index++]);
        }
    }
    else
    {
        for ( int index = m_leftButtons.size() - 1 ; index > 0 ; )
        {// iterate the left buttons
            baseSwapBoxes( m_leftButtons[index], m_leftButtons[index--]);
        }
    }
}

void World::baseSwapBoxes(CBoxButton *box1, CBoxButton *box2)
{// swap two box by resetting the position and size
    float x = box1->getXCoordinate();
    float y = box1->getYCoordinate();
    float z = box1->getZCoordinate();

    box1->setXYZ( box2->getXCoordinate(), box2->getYCoordinate(), box2->getZCoordinate() );
    box2->setXYZ( x, y, z );
}
