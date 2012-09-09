//
//  CEntity.h
//  Kinect_3DJ
//
//  Created by Samuel Ruberti on 6/30/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef Kinect_3DJ_Entity_h
#define Kinect_3DJ_Entity_h
#include "ofMain.h"

typedef enum et {
    ET_None = 0,
    ET_MusicSampleButton,
    ET_LoopButton,
    ET_EffectsButton,
    ET_SwapButton,
    ET_ScrollLeftButtons
}EntityType;

//===========================================================
// Class : CEntity
// Abstract base class for all entities in the world
//===========================================================

class CEntity : public ofBaseApp
{

public:

    // member functions
    CEntity(){};

    virtual void render() = 0;
    virtual void update(double time_since_last_update) = 0;

    //member vars
    bool m_active;

    float m_x, m_y, m_z; //location
    float m_r, m_g, m_b, m_a; //color
    float m_total_time; //time elapsed since creation

    EntityType m_type;

};

//===========================================================
// Class : CBoxEntity
//===========================================================

class CBoxEntity : public CEntity
{
public:

    //member functions
    CBoxEntity(){};

    virtual float swellAnimation() = 0;
    virtual float percentIncluded() = 0;
    virtual bool isCurrentlyHit() = 0;
    virtual bool isHit() = 0;
    virtual void clear() = 0;
    virtual bool collisionTest(ofPoint point) = 0;
    virtual bool collisionTest(ofPoint *point) = 0;

    //member vars
    int m_size;
    int m_pointsInArea;
    int m_pointThreshold;
    int m_threshold;

protected:
    virtual bool hitTest(float x, float y, float z) = 0;
};

#endif
