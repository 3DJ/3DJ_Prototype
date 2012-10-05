//
//  BoxButton.h
//  Kinect_3DJ
//
//  Created by LJ on 10/1/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include "BoxView.h"
#include "Log.h"

CBoxView::CBoxView(CDataPoolSimple* DataPool): IView(DataPool){
    SBoxInfo boxInfo;
    boxInfo.name = "world_sample_a1";
    boxInfo.soundPlayer = new ofSoundPlayer;
    boxInfo.soundPlayer->loadSound( m_dataPool->getDataPool()[boxInfo.name + "_soundName"].value );
    m_boxInfo.push_back( boxInfo );

    boxInfo.name = "world_sample_a2";
    boxInfo.soundPlayer = new ofSoundPlayer;
    boxInfo.soundPlayer->loadSound( m_dataPool->getDataPool()[boxInfo.name + "_soundName"].value );
    m_boxInfo.push_back( boxInfo );

    boxInfo.name = "world_sample_a3";
    boxInfo.soundPlayer = new ofSoundPlayer;
    boxInfo.soundPlayer->loadSound( m_dataPool->getDataPool()[boxInfo.name + "_soundName"].value );
    m_boxInfo.push_back( boxInfo );

    boxInfo.name = "world_sample_a4";
    boxInfo.soundPlayer = new ofSoundPlayer;
    boxInfo.soundPlayer->loadSound( m_dataPool->getDataPool()[boxInfo.name + "_soundName"].value );
    m_boxInfo.push_back( boxInfo );

    boxInfo.name = "world_sample_b1";
    boxInfo.soundPlayer = new ofSoundPlayer;
    boxInfo.soundPlayer->loadSound( m_dataPool->getDataPool()[boxInfo.name + "_soundName"].value );
    m_boxInfo.push_back( boxInfo );

    boxInfo.name = "world_sample_b2";
    boxInfo.soundPlayer = new ofSoundPlayer;
    boxInfo.soundPlayer->loadSound( m_dataPool->getDataPool()[boxInfo.name + "_soundName"].value );
    m_boxInfo.push_back( boxInfo );

    boxInfo.name = "world_sample_b3";
    boxInfo.soundPlayer = new ofSoundPlayer;
    boxInfo.soundPlayer->loadSound( m_dataPool->getDataPool()[boxInfo.name + "_soundName"].value );
    m_boxInfo.push_back( boxInfo );

    boxInfo.name = "world_sample_b4";
    boxInfo.soundPlayer = new ofSoundPlayer;
    boxInfo.soundPlayer->loadSound( m_dataPool->getDataPool()[boxInfo.name + "_soundName"].value);
    m_boxInfo.push_back( boxInfo );

    boxInfo.name = "world_sample_c1";
    boxInfo.soundPlayer = new ofSoundPlayer;
    boxInfo.soundPlayer->loadSound( m_dataPool->getDataPool()[boxInfo.name + "_soundName"].value );
    m_boxInfo.push_back( boxInfo );

    boxInfo.name = "world_sample_c2";
    boxInfo.soundPlayer = new ofSoundPlayer;
    boxInfo.soundPlayer->loadSound( m_dataPool->getDataPool()[boxInfo.name + "_soundName"].value );
    m_boxInfo.push_back( boxInfo );

    boxInfo.name = "world_sample_c3";
    boxInfo.soundPlayer = new ofSoundPlayer;
    boxInfo.soundPlayer->loadSound( m_dataPool->getDataPool()[boxInfo.name + "_soundName"].value );
    m_boxInfo.push_back( boxInfo );

    boxInfo.name = "world_sample_c4";
    boxInfo.soundPlayer = new ofSoundPlayer;
    boxInfo.soundPlayer->loadSound( m_dataPool->getDataPool()[boxInfo.name + "_soundName"].value );
    m_boxInfo.push_back( boxInfo );
}

bool CBoxView::init( ){
    for ( vector<SBoxInfo>::iterator it = m_boxInfo.begin(); it != m_boxInfo.end(); it++ ){
        render( it );
    }

    return true;
}

void CBoxView::render( vector<SBoxInfo>::iterator it ){
    string val = it->name;
    string strCenterX = m_dataPool->getDataPool()[val + "_centerX"].value;
    string strCenterY = m_dataPool->getDataPool()[val + "_centerY"].value;
    string strCenterZ = m_dataPool->getDataPool()[val + "_centerZ"].value;
    string strSize = m_dataPool->getDataPool()[val + "_boxSize"].value;
    string strRed = m_dataPool->getDataPool()[val + "_redVal"].value;
    string strGreen = m_dataPool->getDataPool()[val + "_greenVal"].value;
    string strBlue = m_dataPool->getDataPool()[val + "_blueVal"].value;
    string strAlpha = m_dataPool->getDataPool()[val + "_alphaVal"].value;

    float centerX = stringToFloat( strCenterX);
    float centerY = stringToFloat( strCenterY);
    float centerZ = stringToFloat( strCenterZ);
    int boxSize = stringToInt( strSize);
    float red = stringToFloat( strRed );
    float green = stringToFloat( strGreen );
    float blue = stringToFloat( strBlue );
    float alpha = stringToFloat( strAlpha );

    if ( isCurrentlyHit( val )) {
        ofPushMatrix();
        ofEnableSmoothing();
        ofEnableAlphaBlending();
        ofEnableBlendMode(OF_BLENDMODE_ADD);
        ofTranslate(centerX, centerY, centerZ);
        ofSetColor(255, 255, 255, 51+ (204 * percentIncluded( val )));
        //ofSetColor(0, 0, 0);
        ofFill();
        ofBox(boxSize + swellAnimation(val));
        ofNoFill();
        ofSetColor(255);
        ofBox(boxSize + swellAnimation(val));
        ofDisableAlphaBlending();
        ofDisableSmoothing();
        ofPopMatrix();

        if ( !it->soundPlayer->getIsPlaying()){
            it->soundPlayer->setLoop(true);
            it->soundPlayer->play();
        }
    } else {

        ofPushMatrix();
        ofEnableSmoothing();
        ofEnableAlphaBlending();
        //ofEnableBlendMode(OF_BLENDMODE_ADD);
        ofSetColor(red, green, blue, alpha);
        ofFill();
        ofBox(centerX, centerY, centerZ, boxSize);
        ofNoFill();
        ofSetColor(255,255,255);
        ofBox(centerX, centerY, centerZ, boxSize);
        ofDisableAlphaBlending();
        ofDisableSmoothing();
        ofPopMatrix();

        it->soundPlayer->setLoop(false);
        it->soundPlayer->stop();
        it->soundPlayer->setPosition(0);
    }

    m_dataPool->setAnimateValue( val + "_pointsInArea", "0");
}

bool CBoxView::isCurrentlyHit( string val ){
//    fs<<"boxView->world_sample_b1_pointsInArea:"<<m_dataPool->getDataPool()["world_sample_b1_pointsInArea"]<<endl;
    string strPointsInArea = m_dataPool->getDataPool()[val + "_pointsInArea"].value;
    string strThreshold = m_dataPool->getDataPool()[val + "_threshold"].value;
    int pointsInArea = stringToInt( strPointsInArea );
    int threshold = stringToInt( strThreshold );
//     fs<<val+"points:"<<pointsInArea<<endl;
//     fs<<val+"thres:"<<threshold<<endl;
//     fs<<(pointsInArea > threshold)<<endl;

    return (pointsInArea > threshold);
}

float CBoxView::percentIncluded( string val ){
    string strPointsInArea = m_dataPool->getDataPool()[val + "_pointsInArea"].value;
    string strpointThreshold = m_dataPool->getDataPool()[val + "_pointThreshold"].value;
    int pointsInArea = stringToInt( strPointsInArea );
    int pointThreshold = stringToInt( strpointThreshold );

    return ofMap( pointsInArea, 0, pointThreshold, 0, 1);
}


float CBoxView::swellAnimation( string val ){
    string strBoxSize = m_dataPool->getDataPool()[val + "_boxSize"].value;
    int boxSize = stringToInt( strBoxSize );

    return (boxSize/10) * cos(ofGetElapsedTimef()*15);
}