//
//  CHands.cpp
//  Kinect_3DJ
//
//  Created by Li Jing on 2/30/13.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef Kinect_3DJ_CHands_h
#define Kinect_3DJ_CHands_h
#include "ofxOpenNI.h"
#include "DataPool.h"
using namespace DataPool;

typedef struct{
    ofPoint rhp;
    ofPoint lhp;
}handsPoint;

class CHands{
public:
    CHands(CDataPoolSimple* datapool);
    ~CHands();
    // this is for public use
    void draw();  
    // call this to trigger sliding gesture.
    void triggerSlide();
    // call this to trigger the box start up/shut down switch.
    void triggerBoxSwitch();

private:
    // draw a filled circle to indicates the box is started up
    void drawStartSignal( ofPoint p, float radius );

    // this is for draw all hands on screen.
    void drawHands();    

    // get all hands position. 
    void getHands();
    void  drawCirclesOnPoint(ofPoint &p, float radiu);

    CDataPoolSimple* m_datapool;

    ofxOpenNI*           m_openNIDevice;
    map<int, handsPoint>   m_mapHands;
    
    // this group member is for slide gesture
    bool m_slide;
    ofPoint m_slideTriggerPoint;    // I draw a circle at m_slideTriggerPoint to let you know where to start slide.
    float m_slideRadius;
    ofxOpenNIUser *m_slideUser;
    Joint m_slideHand;          // current tracking slide hand.
    bool m_slideStart;
    float m_slideOffset;
    int m_slideThreshold; // this means: if hand.z>1400, sliding is over. that indicates the end of once sliding.

    // this group member is for start box sounds
    bool m_isBoxStartedUp;
    bool m_isTriggerBoxSwitch;
};

#endif
