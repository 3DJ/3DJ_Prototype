//
//  CBoxButton.h
//  Kinect_3DJ
//
//  Created by Samuel Ruberti on 6/30/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef Kinect_3DJ_BoxButton_h
#define Kinect_3DJ_BoxButton_h
#include "Entity.h"

class CBoxButton : public CBoxEntity
{

public:
    CBoxButton(float centerX, float centerY, float centerZ, int boxSize, 
        float redVal, float greenVal, float blueVal, float alphaVal, string soundName);
    CBoxButton();
    ~CBoxButton();

    // set up the box button's properties.
    virtual void setupBoxButton( int threshold, int pointThreshold = 2000, EntityType type = ET_MusicSampleButton );
    void render();

	void update(double time_since_last_update);

    float swellAnimation();
    float percentIncluded();
    bool isCurrentlyHit();
    bool isHit();
    void clear();
    virtual bool collisionTest( ofPoint point)  ;
    virtual bool collisionTest( ofPoint *pPoint);

    virtual int getBoxType();

    ofSoundPlayer m_soundPlayer;
    bool m_isRepeat;
    bool m_toBeStop;
    float  m_speed;
    float  m_volume;
    float  m_pan;

protected:
    bool hitTest(float x, float y, float z);

private:

	void setHitMode();

	void setDefaultMode();
};

#endif
