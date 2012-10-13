//
//  BoxButton.h
//  Kinect_3DJ
//
//  Created by LJ on 8/23/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include "BoxController.h"

#include "Log.h"

CBoxController::CBoxController(CDataPoolSimple* dataPool):IController(dataPool){
    m_oniKinect.setup();
    m_pointView = new CPointView;

    m_boxName.push_back( "world_sample_a1" );
    m_boxName.push_back( "world_sample_a2" );
    m_boxName.push_back( "world_sample_a3" );
    m_boxName.push_back( "world_sample_a4" );
    m_boxName.push_back( "world_sample_b1" );
    m_boxName.push_back( "world_sample_b2" );
    m_boxName.push_back( "world_sample_b3" );
    m_boxName.push_back( "world_sample_b4" );
    m_boxName.push_back( "world_sample_c1" );
    m_boxName.push_back( "world_sample_c2" );
    m_boxName.push_back( "world_sample_c3" );
    m_boxName.push_back( "world_sample_c4" );

    for ( vector<string>::iterator it = m_boxName.begin(); it != m_boxName.end(); it++)
    {
        SBoxInfo boxInfo;

        boxInfo.name = (*it);

        boxInfo.centerX = m_dataPool->findValueRef( (*it) + "_centerX" );

        boxInfo.centerY = m_dataPool->findValueRef( (*it) + "_centerY" );

        boxInfo.centerZ = m_dataPool->findValueRef( (*it) + "_centerZ" );

        boxInfo.boxSize = m_dataPool->findValueRef( (*it) + "_boxSize" );

        boxInfo.threshold = m_dataPool->findValueRef( (*it) + "_threshold" );

        m_boxInfo.push_back( boxInfo );
    }
}

bool CBoxController::init()
{
    m_oniKinect.update();

    ofPushMatrix();
    ofScale(-1, 1);
    ofTranslate((ofGetWidth()/2)-320, (ofGetHeight()/2) -240, -1000); // center the points a bit
    ofRotateX(180);                   //Rotate around Axis
    // ofTranslate(0,0,1000);            // Move back into Camera View
    ofTranslate(3 ,3, 3 *-800 + 1000);
    ofScale(3,3,3);

    if(m_oniKinect.m_isTracking)
    {
        int w = m_oniKinect.m_recordUser.getWidth();
        int h = m_oniKinect.m_recordUser.getHeight();

        int step = 5;

        for ( vector<SBoxInfo>::iterator it = m_boxInfo.begin(); it != m_boxInfo.end(); it++ )
        {
            int threshold = stringToInt( *(it->threshold) );
            int centerX = stringToInt( *(it->centerX));
            int centerY = stringToInt( *(it->centerY));
            int centerZ = stringToInt( *(it->centerZ));
            int size = stringToInt( *(it->boxSize));

            int startW = (centerX - size/2)/2 + w/2;
            int endW = (centerX + size/2)/2 + w/2;
            int startH = (centerY - size/2)/2 + h/2;
            int endH = (centerY + size/2)/2 + h/2;

            for(int y = startH; y < endH; y += step) {
                for(int x = startW; x < endW; x += step) {
                    ofPoint XYZ = m_oniKinect.m_recordUser.getWorldCoordinateAt(x, y, m_oniKinect.m_numberOfUsersToTrack);
                    //fs<<"x:"<<XYZ.x<<"y:"<<XYZ.y<<"z:"<<XYZ.z<<endl;
                    XYZ.x = (XYZ.x - w/2) * 2;
                    XYZ.y = (XYZ.y - h/2) * 2;


                    if (XYZ.z > 0 )
                    {
                        //cout<<"x:"<<XYZ.x<<"y:"<<XYZ.y<<"z:"<<XYZ.z<<endl;
                        if( ((XYZ.x > centerX - size/2) && (XYZ.y > centerY - size/2) && (XYZ.z > centerZ*2 - size))
                            &&(XYZ.x < centerX + size/2) && (XYZ.y < centerY + size/2) && (XYZ.z < centerZ*2 + size)){
                                m_pointsInArea++;
                                if ( m_pointsInArea > threshold )
                                {
                                    m_dataPool->setValue( it->name + "_isHit", "1");
                                }
                        }
                        m_pointView->addPoint(XYZ.x, XYZ.y, XYZ.z);
                    }
                }
            }
            m_pointsInArea = 0;
        }

        int points = 0;
        static float frontPoint;
        for(int y = 40; y > 0; y -= step) {
            for(int x = 0; x < w; x += step) {
                ofPoint XYZ = m_oniKinect.m_recordUser.getWorldCoordinateAt(x, y, m_oniKinect.m_numberOfUsersToTrack);
                if ( XYZ.z > 0)
                {
                    points++;
                    int distance = abs(m_frontPosition - XYZ.x);
                    if ( points > 7 && distance > 80){
                        if ( m_frontPosition == 0)
                        {
                            frontPoint = XYZ.x;
                            m_frontPosition = XYZ.x;
                        }

                        if ( abs( XYZ.x - frontPoint) < 100 )
                        {
                            frontPoint = XYZ.x;
                            m_dataPool->setValue( "world_complexor", floatToString( XYZ.x - m_frontPosition ));
                        }
                    }

                }
            }
        }

        if ( points == 0 )
        {
            m_frontPosition = 0;
            m_dataPool->setValue( "world_complexor", "0");
        }


        m_pointView->uploadDataToVbo();
        m_pointView->drawParticles();
        m_pointView->clearData();
    }

    ofPopMatrix();

    return true;
}
