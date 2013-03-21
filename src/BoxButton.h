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
#include "DataPool.h"
#include "CWorld.h"

using namespace DataPool;

class CBoxButton : public CBoxEntity
{// box class, include the box drawing, box render, box slide animation
public:
    CBoxButton(string boxName, float centerX, float centerY, float centerZ, int boxSize,
        float redVal, float greenVal, float blueVal, float alphaVal, string soundName, float rotation);
    CBoxButton();
    ~CBoxButton();

    // render the boxes on screen.
    void render(int m_slideOffset);
    // reload the another sound file.
    void reloadSound(string soundName);
    // check whether the box is a loop box
    virtual bool isLoopBox();

    string getBoxName();

    bool isCurrentlyHit();
    bool collisionTest( ofPoint *pPoint);
    ofSoundPlayer *m_soundPlayer;
    void clear();

    bool m_isRepeat;    
    string m_boxName;       // box name which used to recognize by up-level.
protected:
    bool hitTest(float x, float y, float z);

private:
    // this is only for implementing abstract method.
    void render();
    void drawRepeatingBox();
    void drawBox( float complexor );
    void update(double time_since_last_update);
    float swellAnimation();
    float percentIncluded();   

    bool isHit();

    bool collisionTest( ofPoint point);    
    void setHitMode();
    void setDefaultMode();
    CDataPoolSimple* m_datapool;       

    bool m_toBeStop;
};

#endif
