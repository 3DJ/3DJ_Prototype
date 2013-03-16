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
    void draw();

    void drawHands();

    void triggerSlide();

private:
    void getHands();
    void  drawCirclesOnHand(ofPoint &p, float radiu);
    CDataPoolSimple* m_datapool;

    ofxOpenNI*           m_openNIDevice;
    map<int, handsPoint>   m_mapHands;
    
    bool m_slide;
    ofPoint m_slideTriggerPoint;
    float m_slideRadius;
    ofxOpenNIUser *m_slideUser;
    Joint m_slideHand;   // true stands for right hand, false stands for left hand.
    bool m_slideStart;
    float m_slideOffset;
};

#endif
