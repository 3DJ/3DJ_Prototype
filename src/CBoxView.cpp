//
//  CBoxView.cpXYZ
//  Kinect_3DJ
//
//  Created by Samuel Ruberti on 6/30/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "CBoxView.h"

CBoxView::CBoxView(CDataPoolSimple* dataPool): IView(dataPool)
{
    void* temporary;
    if( dataPool->getPointerByName( "oniKinect", temporary)) { m_oniKinect = (CKinectData*) temporary; }
    if( dataPool->getPointerByName( "pointView", temporary)) { m_pointView = (CPointView *) temporary; };
    
    if( dataPool->getPointerByName( "easyCam", temporary)) { m_easyCam = (ofEasyCam *) temporary; }
    if( dataPool->getPointerByName( "equalizerView", temporary)) { m_equalizerView = (CEQView *) temporary; }
    if( dataPool->getPointerByName( "snakeFish", temporary)) { m_snakeFish = (SnakeFish *) temporary; }
    if( dataPool->getPointerByName( "particles", temporary)) { m_particles = (Particles *) temporary; }

    if( dataPool->getPointerByName( "a1Button", temporary)) { 
        m_a1Button = (CBoxButton*) temporary; 
        m_boxButtons.push_back( m_a1Button );       
    }
    if( dataPool->getPointerByName( "a2Button", temporary)) { 
        m_a2Button = (CBoxButton*) temporary; 
        m_boxButtons.push_back( m_a2Button );       
    }
    if( dataPool->getPointerByName( "a3Button", temporary)) { 
        m_a3Button = (CBoxButton*) temporary; 
        m_boxButtons.push_back( m_a3Button );       
    }
    if( dataPool->getPointerByName( "a4Button", temporary)) { 
        m_a4Button = (CBoxButton*) temporary; 
        m_boxButtons.push_back( m_a4Button );       
    }

    if( dataPool->getPointerByName( "b2Button", temporary)) {
        m_b2Button  = (CBoxButton*) temporary; 
        m_boxButtons.push_back( m_b2Button );       
    }
    if( dataPool->getPointerByName( "b3Button", temporary)) { 
        m_b3Button  = (CBoxButton*) temporary; 
        m_boxButtons.push_back( m_b3Button );       
    }
    if( dataPool->getPointerByName( "b4Button", temporary)) { 
        m_b4Button  = (CBoxButton*) temporary; 
        m_boxButtons.push_back( m_b4Button );       
    }
    if( dataPool->getPointerByName( "controlButton_1", temporary)) { 
        m_controlButton_1 = (CBoxButton*) temporary; 
        m_boxButtons.push_back( m_controlButton_1 ); 
    }

    if( dataPool->getPointerByName( "c1Button", temporary)) { 
        m_c1Button  = (CBoxButton*) temporary; 
        m_boxButtons.push_back( m_c1Button );
    }
    if( dataPool->getPointerByName( "c2Button", temporary)) { 
        m_c2Button  = (CBoxButton*) temporary; 
        m_boxButtons.push_back( m_c2Button );       
    }
    if( dataPool->getPointerByName( "c3Button", temporary)) {
        m_c3Button  = (CBoxButton*) temporary;
        m_boxButtons.push_back( m_c3Button );       
    }
    if( dataPool->getPointerByName( "c4Button", temporary)) { 
        m_c4Button  = (CBoxButton*) temporary; 
        m_boxButtons.push_back( m_c4Button );       
    }    

    m_complexor = 0;

	m_background_r = 100;
    m_background_g = 100;
    m_background_b = 100;
    m_gradientColorOutside = ofColor(24);
    m_gradientColorInside = ofColor(64);
    
    //Setup Scale ratio to map Kinect depth image to screen and buttons
    m_WidthScale = 1.0f;
    m_HeightScale = 1.0f;
    m_scale = scaleRatioForKinectDepthMap();
    m_playerDepth = 1000.0f;

    //SET UP BUTTONS and add all buttons to world vector============
    //    x, y, z, box size, r, g, b, a, music sample name
    //==============================================================
    m_red               = 255;
    m_green             = 255;
    m_blue              = 255;
    m_alpha             = 30;
    m_boxSize           = 225;
    m_boxCenterX        = 200;
    m_boxCenterY        = 200;
    m_boxCenterZ        = 0;
    m_controlBox_r      = 220; //control box buttons
    m_controlBox_g      = 50;
    m_controlBox_b      = 50;
    m_controlBox_a      = 30;
    float m_z = 0;

    setInitialVolume(1.0f);

    m_isRepeat      = false;
}

CBoxView::~CBoxView()
{
}

bool CBoxView::draw()
{
    render();

    return true;
}

void CBoxView::render()
{
    ofBackgroundGradient(m_gradientColorInside,m_gradientColorOutside);
    m_easyCam->begin();
    //setUpTranslation();             //Set up translation for all drawing
    
    ofPushMatrix();
    ofScale(-1, 1);
    ofRotateX(180);
    effectBoxbutton();              // render boxbutton and handle the sound.
    if(m_oniKinect->m_isTracking){ drawDepthPoints();}   // Do both here so we only look up the m_oniKinect->data once...
   
    ofPopMatrix();

    ofPushMatrix();                 // ofPushMatrix before ofTranslate.
    ofTranslate(0, -1.5*ofGetHeight(), -5000);
    ofPopMatrix();
    
    //m_snakeFish->render();      //Draw Creature
    //m_snakeFish->postRender();
    
    m_easyCam->end();
    
    ofPushMatrix();
    ofTranslate(ofGetWindowWidth()/2, + ofGetWindowHeight());
    //m_particles->render();
    ofPopMatrix();
    //m_equalizerView->drawEQRect();
    
//    string msg = "Scale : " + ofToString(m_scale,2);
//    ofDrawBitmapString(msg, ofGetWindowWidth()/2, ofGetWindowHeight()/2);
    
}

void CBoxView::drawDepthPoints()
{
    int w = m_oniKinect->m_openNIDevice.getWidth();
	int h = m_oniKinect->m_openNIDevice.getHeight();

    m_pointView->uploadDataToVbo();
    m_pointView->drawParticles();
    m_pointView->clearData();
    
    ofPushMatrix();
    ofTranslate(-w/2, -h/2, m_playerDepth);
    ofPopMatrix();
       
}


void CBoxView::addBoxButton(CBoxButton * _boxButton)
{
    m_boxButtons.push_back(_boxButton);
}

void CBoxView::handleCollisions(ofPoint *XYZ)
{
    for ( vector<CBoxButton *>::iterator eachBox = m_boxButtons.begin(); eachBox != m_boxButtons.end(); eachBox++ )
    {
        (*eachBox)->collisionTest(XYZ); //test Each Box for hits
    }
}

void CBoxView::clearButtons()
{
    for ( vector<CBoxButton *>::iterator eachBox = m_boxButtons.begin(); eachBox != m_boxButtons.end(); eachBox++ )
    {
        (*eachBox)->clear();
    }
}

void CBoxView::setInitialVolume(float volumeLevel)
{
    for ( vector<CBoxButton *>::iterator eachBox = m_boxButtons.begin(); eachBox != m_boxButtons.end(); eachBox++ )
    {
        (*eachBox)->m_soundPlayer.setVolume(volumeLevel);
    }

}

void CBoxView::setUpTranslation()
{
    
}

void CBoxView::effectBoxbutton()
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

        (*eachBox)->render( ); // Draw BoxButtons and Handle Sound.
    }
}

float CBoxView::scaleRatioForKinectDepthMap()
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

