//
//  CHands.cpp
//  Kinect_3DJ
//
//  Created by Li Jing on 2/30/13.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include "CHands.h"

CHands::CHands( )
{
    m_datapool = &CDataPoolSimple::getInstance();
    // get the openNI device from CKinectData object, that means kinect object must be created before this operation.
    void *temp;
    m_datapool->getRefByName("ofxOpenNIDevice", temp);
    m_openNIDevice = (ofxOpenNI*)temp;

    // set the sliding variable
    m_slide = false;    
    m_slideTriggerPoint.x = 0;
    m_slideTriggerPoint.y = -250;
    m_slideTriggerPoint.z = 800;
    m_slideRadius = 200;    
    m_slideHand = JOINT_RIGHT_HAND;
    m_slideStart = false;
    m_slideThreshold = 1400; // this means: if z>1400, slide is over. 

    // set the start up switch variable.
    m_isBoxStartedUp = false; 
    m_isTriggerBoxSwitch = false;
}

CHands::~CHands()
{

}

void CHands::drawCirclesOnPoint(ofPoint &p, float radius)
{// draw cirle on hand
    ofPushMatrix();
    ofFill();
    ofSetLineWidth(5.f);

    ofCircle(p.x, p.y, p.z, radius);

    ofPopMatrix();
}

void CHands::getHands()
{
    static float lastClock = 0;
    int numUsers = m_openNIDevice->getNumTrackedUsers();
    if (numUsers) {
        m_mapHands.clear();
        for (int i = 0; i < numUsers; i++) {
            ofxOpenNIUser & user = m_openNIDevice->getTrackedUser(i);
            if (user.isTracking()) {

                //Get Left and right hand posisitons
                ofPoint rhp = m_openNIDevice->getTrackedUser(i).getJoint(JOINT_RIGHT_HAND).getWorldPosition();
                ofPoint lhp = m_openNIDevice->getTrackedUser(i).getJoint(JOINT_LEFT_HAND).getWorldPosition();;

                // this coordinator translating is for adapting to box view.
                rhp.y *= -2;  //flip in y direction
                lhp.y *= -2;  //flip in y direction    
                rhp.x *= 2;
                lhp.x *= 2;

                if ( lhp.z < m_slideTriggerPoint.z + m_slideRadius
                    &&lhp.z > m_slideTriggerPoint.z - m_slideRadius
                    &&lhp.y < m_slideTriggerPoint.y + m_slideRadius
                    &&lhp.z > m_slideTriggerPoint.y - m_slideRadius
                    &&lhp.x < m_slideTriggerPoint.x + m_slideRadius
                    &&lhp.x > m_slideTriggerPoint.x - m_slideRadius)
                {
                    //cout<<"trigger left"<<endl; 
                    //cout<<lastClock<<endl;
                    //cout<<ofGetElapsedTimef()<<endl;
                    if ( ofGetElapsedTimef() - lastClock > 2)
                    {
                        m_isBoxStartedUp = !m_isBoxStartedUp;
                        lastClock = ofGetElapsedTimef();
                    }                    
                    m_slideStart = false;                    
                }
                if ( rhp.z < m_slideTriggerPoint.z + m_slideRadius
                    &&rhp.z > m_slideTriggerPoint.z - m_slideRadius
                    &&rhp.y < m_slideTriggerPoint.y + m_slideRadius
                    &&rhp.z > m_slideTriggerPoint.y - m_slideRadius
                    &&rhp.x < m_slideTriggerPoint.x + m_slideRadius
                    &&rhp.x > m_slideTriggerPoint.x - m_slideRadius)
                {
                    //cout<<"trigger right"<<endl;
                    m_slideUser = &user;
                    m_slideHand = JOINT_RIGHT_HAND;
                    m_slideStart = true;
                    m_isBoxStartedUp = false;
                }

                // save hands point to map.
                handsPoint hp;
                hp.lhp = lhp;
                hp.rhp = rhp;
                m_mapHands[i] = hp;
            }
        }
    }
}

void CHands::draw()
{
    // checking current hands position.
    getHands();

    if ( m_slide ){
        if ( m_slideStart && m_slideUser->isTracking() ){
            ofPoint hp = m_slideUser->getJoint(m_slideHand).getWorldPosition();
            // this coordinator translating is for adapting to box view.
            hp.y *= -2;  //flip in y direction
            hp.x *= 2;
            if ( hp.z > m_slideThreshold )
            {// if z > 
                m_slideStart = false;
                m_slideUser = 0;
                m_slideOffset = 0;
            }else{
                m_slideOffset = hp.x - m_slideTriggerPoint.x;
                drawCirclesOnPoint(hp, m_slideRadius);            
            }
            m_datapool->createRef("slideOffset", &m_slideOffset);            
        }else{            
            //drawCirclesOnPoint(m_slideTriggerPoint, m_slideRadius);
        }            
    }    

    if ( m_isBoxStartedUp ){      
        m_datapool->createRef("isBoxStartedUp", &m_isBoxStartedUp);
        drawStartSignal( m_slideTriggerPoint, m_slideRadius);
    }else{
        drawCirclesOnPoint(m_slideTriggerPoint, m_slideRadius);
    }

    //drawHands();
}

void CHands::triggerSlide()
{
    m_slide = true;
}

void CHands::drawHands()
{
    getHands();
    for ( map<int, handsPoint>::iterator iter = m_mapHands.begin(); iter != m_mapHands.end(); iter++)
    {
        //cout<< "left hand x:" << iter->second.lhp.x << "left hand y:" << iter->second.lhp.y << "left hand z:" << iter->second.lhp.z <<endl;
        //cout<< "left hand x:" << iter->second.rhp.x << "left hand y:" << iter->second.rhp.y << "left hand z:" << iter->second.rhp.z <<endl;
        drawCirclesOnPoint( iter->second.lhp, 200);
        drawCirclesOnPoint( iter->second.rhp, 100);
    }
}

void CHands::drawStartSignal( ofPoint p, float radius )
{// draw a filled circle to indicates the box is started up
    ofPushMatrix();
    ofNoFill();
    ofSetLineWidth(5.f);

    ofCircle(p.x, p.y, p.z, radius);

    ofPopMatrix();
}

void CHands::triggerBoxSwitch()
{
    m_isTriggerBoxSwitch = true;
}