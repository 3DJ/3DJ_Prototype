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
{

public:
    CBoxButton(string boxName, float centerX, float centerY, float centerZ, int boxSize,
        float redVal, float greenVal, float blueVal, float alphaVal, string soundName, float rotation);
    CBoxButton();
    ~CBoxButton();

    void render();

    void render(int m_slideOffset);

    void drawBox( float complexor );

    void update(double time_since_last_update);
    float swellAnimation();
    float percentIncluded();
    bool isCurrentlyHit();
    bool isHit();
    void clear();
    bool collisionTest( ofPoint point)  ;
    bool collisionTest( ofPoint *pPoint);
    void reloadSound(string soundName);

    virtual bool isLoopBox();

    ofSoundPlayer *m_soundPlayer;
    bool m_isRepeat;
    bool m_toBeStop;
    string m_boxName;
protected:
    bool hitTest(float x, float y, float z);

private:

	void setHitMode();
	void setDefaultMode();
    CDataPoolSimple* m_datapool;

};

#endif
