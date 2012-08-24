//
//  CBoxButton.cpp
//  Kinect_3DJ
//
//  Created by Samuel Ruberti on 6/30/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "BoxButton.h"

CBoxButton::CBoxButton(float centerX, float centerY, float centerZ, int boxSize, float redVal, float greenVal, float blueVal, float alphaVal, string soundName)
{
    m_x = centerX;
    m_y = centerY;
    m_z = centerZ;
    m_size = boxSize;
    m_r = redVal;
    m_g = greenVal;
    m_b = blueVal;
    m_a = alphaVal;

    m_isRepeat = false;
    m_toBeStop = false;
    m_pointsInArea = 0;
    m_pointThreshold = 2000;
    m_threshold = 10;
    m_type = ET_MusicSampleButton;
    m_soundPlayer.loadSound(soundName);
}

CBoxButton::CBoxButton()
{

}

CBoxButton::~CBoxButton()
{

}

void CBoxButton::render()  //Draw boxes and set color
{
    if ( m_isRepeat && !isCurrentlyHit() )
    {// make it stop on next hit.
        m_toBeStop = true;     
    }

    if ( m_isRepeat && isCurrentlyHit() )
    {// if check this signal, close repeat option.
        if ( m_toBeStop == true ){
            m_isRepeat = false;
            m_toBeStop = false;
        }
    }

    if ( isCurrentlyHit() || m_isRepeat) {
		// set the current hit button to hit mode.
		setHitMode();
        // handle the sound
        if ( !m_soundPlayer.getIsPlaying()){
            m_soundPlayer.setLoop(true);
            m_soundPlayer.play();
        }
    } else{
		// set the unhit button as default mode.
		setDefaultMode();
        // shut down the sound.
        m_soundPlayer.setLoop(false);
        m_soundPlayer.stop();
        m_soundPlayer.setPosition(0);    
    }

    clear(); //clear point count
}

void CBoxButton::update(double timeSinceLastUpdate)
{

}

float CBoxButton::swellAnimation()
{
    return (m_size/10) * cos(ofGetElapsedTimef()*15);   
}

float CBoxButton::percentIncluded()
{
    return ofMap(m_pointsInArea, 0, m_pointThreshold, 0, 1);
}

bool CBoxButton::isCurrentlyHit()
{
    return (m_pointsInArea > m_threshold);
}

bool CBoxButton::isHit()
{
    return isCurrentlyHit() && !m_active;
}

void CBoxButton::clear()
{
    m_active = isCurrentlyHit();
    m_pointsInArea = 0;
}

bool CBoxButton::collisionTest( ofPoint point) 
{
    bool result = false;

    if( ((point.x > m_x - m_size/2) && (point.y > m_y - m_size/2) && (point.z > m_z - m_size/2))
       &&(point.x < m_x + m_size/2) && (point.y < m_y + m_size/2) && (point.z < m_z + m_size/2)){
       
          result = true;
          m_pointsInArea++;
    }        
    return result;
}

bool CBoxButton::collisionTest( ofPoint *pPoint) 
{
    return collisionTest( *pPoint );        // call the collisionTest( ofPoint point)
}

bool CBoxButton::hitTest(float x, float y, float z)
{
    return isCurrentlyHit() && !m_active;
}

void CBoxButton::setDefaultMode()
{
	ofPushMatrix();
	ofEnableSmoothing();
	ofEnableAlphaBlending();
	//ofEnableBlendMode(OF_BLENDMODE_ADD);
	ofSetColor(m_r, m_g, m_b, m_a);
	ofFill();
	ofBox(m_x, m_y, m_z, m_size);
	ofNoFill();
	ofSetColor(255,255,255);
	ofBox(m_x, m_y, m_z, m_size);
	ofDisableAlphaBlending();
	ofDisableSmoothing();
	ofPopMatrix();
}

void CBoxButton::setHitMode()
{
	ofPushMatrix();
	ofEnableSmoothing();
	ofEnableAlphaBlending();
	ofEnableBlendMode(OF_BLENDMODE_ADD);
	ofTranslate(m_x, m_y, m_z);
	ofSetColor(255, 255, 255, 51+ (204 * percentIncluded()));
	//ofSetColor(0, 0, 0);
	ofFill();
	ofBox(m_size + swellAnimation());
	ofNoFill();
	ofSetColor(255);
	ofBox(m_size + swellAnimation());
	ofDisableAlphaBlending();
	ofDisableSmoothing();
	ofPopMatrix();
}

bool CBoxButton::isLoopBox()
{
    return false;
}