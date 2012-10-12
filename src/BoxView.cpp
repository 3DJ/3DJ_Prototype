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
    m_complexor = 0;
    boxInfo.name = "world_sample_a1";
    boxInfo.soundPlayer = new ofSoundPlayer;
    boxInfo.soundPlayer->loadSound( *m_dataPool->findValueRef(boxInfo.name + "_soundName"));
    m_boxInfo.push_back( boxInfo );

    boxInfo.name = "world_sample_a2";
    boxInfo.soundPlayer = new ofSoundPlayer;
    boxInfo.soundPlayer->loadSound( *m_dataPool->findValueRef(boxInfo.name + "_soundName"));
    m_boxInfo.push_back( boxInfo );

    boxInfo.name = "world_sample_a3";
    boxInfo.soundPlayer = new ofSoundPlayer;
    boxInfo.soundPlayer->loadSound( *m_dataPool->findValueRef(boxInfo.name + "_soundName"));
    m_boxInfo.push_back( boxInfo );

    boxInfo.name = "world_sample_a4";
    boxInfo.soundPlayer = new ofSoundPlayer;
    boxInfo.soundPlayer->loadSound( *m_dataPool->findValueRef(boxInfo.name + "_soundName"));
    m_boxInfo.push_back( boxInfo );

    boxInfo.name = "world_sample_b1";
    boxInfo.soundPlayer = new ofSoundPlayer;
    boxInfo.soundPlayer->loadSound( *m_dataPool->findValueRef(boxInfo.name + "_soundName"));
    m_boxInfo.push_back( boxInfo );

    boxInfo.name = "world_sample_b2";
    boxInfo.soundPlayer = new ofSoundPlayer;
    boxInfo.soundPlayer->loadSound( *m_dataPool->findValueRef(boxInfo.name + "_soundName"));
    m_boxInfo.push_back( boxInfo );

    boxInfo.name = "world_sample_b3";
    boxInfo.soundPlayer = new ofSoundPlayer;
    boxInfo.soundPlayer->loadSound( *m_dataPool->findValueRef(boxInfo.name + "_soundName"));
    m_boxInfo.push_back( boxInfo );

    boxInfo.name = "world_sample_b4";
    boxInfo.soundPlayer = new ofSoundPlayer;
    boxInfo.soundPlayer->loadSound( *m_dataPool->findValueRef(boxInfo.name + "_soundName"));
    m_boxInfo.push_back( boxInfo );

    boxInfo.name = "world_sample_c1";
    boxInfo.soundPlayer = new ofSoundPlayer;
    boxInfo.soundPlayer->loadSound( *m_dataPool->findValueRef(boxInfo.name + "_soundName"));
    m_boxInfo.push_back( boxInfo );

    boxInfo.name = "world_sample_c2";
    boxInfo.soundPlayer = new ofSoundPlayer;
    boxInfo.soundPlayer->loadSound( *m_dataPool->findValueRef(boxInfo.name + "_soundName"));
    m_boxInfo.push_back( boxInfo );

    boxInfo.name = "world_sample_c3";
    boxInfo.soundPlayer = new ofSoundPlayer;
    boxInfo.soundPlayer->loadSound( *m_dataPool->findValueRef(boxInfo.name + "_soundName"));
    m_boxInfo.push_back( boxInfo );

    boxInfo.name = "world_sample_c4";
    boxInfo.soundPlayer = new ofSoundPlayer;
    boxInfo.soundPlayer->loadSound( *m_dataPool->findValueRef(boxInfo.name + "_soundName"));
    m_boxInfo.push_back( boxInfo );
}

bool CBoxView::init( ){

    string strComplexor = "0";
    if ( m_dataPool->findValueRef( "world_complexor") != 0 ){
        strComplexor = *m_dataPool->findValueRef( "world_complexor");        
    }
    float complexor = stringToFloat( strComplexor);    

    if ( complexor != 0 || m_complexor/50 != 0)
    {
            if ( complexor != 0){
                m_complexor = complexor;
            }
            else{
                if ( m_complexor > 0 && m_complexor < 300 )
                {
                    m_complexor = m_complexor - 40;
                }
                else if( m_complexor < 0 && m_complexor > -300 )
                {
                    m_complexor = m_complexor + 40;
                }
                else if ( m_complexor < -300 ){
                    m_complexor = m_complexor - 80;
                }
                else if ( m_complexor > 300 ){
                    m_complexor = m_complexor + 80;
                }

            }

            if ( m_complexor > 2000 || m_complexor < -2000)
            {
                m_complexor = 0;
            }

            for ( vector<SBoxInfo>::iterator it = m_boxInfo.begin(); it != m_boxInfo.end(); it++ ){
                animation ( it );
            }        
    }
    else
    {
        for ( vector<SBoxInfo>::iterator it = m_boxInfo.begin(); it != m_boxInfo.end(); it++ ){
            render( it );
        }

    }

    return true;
}

void CBoxView::animation( vector<SBoxInfo>::iterator it ){
    string val = it->name;
    string strCenterX = *m_dataPool->findValueRef(val + "_centerX");
    string strCenterY = *m_dataPool->findValueRef(val + "_centerY");
    string strCenterZ = *m_dataPool->findValueRef(val + "_centerZ");
    string strSize = *m_dataPool->findValueRef(val + "_boxSize");
    string strRed = *m_dataPool->findValueRef(val + "_redVal");
    string strGreen = *m_dataPool->findValueRef(val + "_greenVal");
    string strBlue = *m_dataPool->findValueRef(val + "_blueVal");
    string strAlpha = *m_dataPool->findValueRef(val + "_alphaVal");
    string strComplexor = "0";
    if ( m_dataPool->findValueRef( "world_complexor") != 0 ){
        strComplexor = *m_dataPool->findValueRef( "world_complexor");        
    }

    float centerX = stringToFloat( strCenterX);
    float centerY = stringToFloat( strCenterY);
    float centerZ = stringToFloat( strCenterZ);
    int boxSize = stringToInt( strSize);
    boxSize = 200;
    float red = stringToFloat( strRed );
    float green = stringToFloat( strGreen );
    float blue = stringToFloat( strBlue );
    float alpha = stringToFloat( strAlpha );
    float complexor = stringToFloat( strComplexor);    

    drawBox(red, green, blue, alpha , centerX, m_complexor, centerY, centerZ, boxSize);    
    drawBox(red, green, blue, alpha , centerX, m_complexor - 2000 , centerY, centerZ, boxSize);    
    drawBox(red, green, blue, alpha , centerX, m_complexor + 2000 , centerY, centerZ, boxSize);    

    it->soundPlayer->setLoop(false);
    it->soundPlayer->stop();
    it->soundPlayer->setPosition(0);
}

void CBoxView::render( vector<SBoxInfo>::iterator it ){
    string val = it->name;
    string strCenterX = *m_dataPool->findValueRef(val + "_centerX");
    string strCenterY = *m_dataPool->findValueRef(val + "_centerY");
    string strCenterZ = *m_dataPool->findValueRef(val + "_centerZ");
    string strSize = *m_dataPool->findValueRef(val + "_boxSize");
    string strRed = *m_dataPool->findValueRef(val + "_redVal");
    string strGreen = *m_dataPool->findValueRef(val + "_greenVal");
    string strBlue = *m_dataPool->findValueRef(val + "_blueVal");
    string strAlpha = *m_dataPool->findValueRef(val + "_alphaVal");
    string strComplexor = "0";
    if ( m_dataPool->findValueRef( "world_complexor") != 0 ){
        strComplexor = *m_dataPool->findValueRef( "world_complexor");        
    }

    float centerX = stringToFloat( strCenterX);
    float centerY = stringToFloat( strCenterY);
    float centerZ = stringToFloat( strCenterZ);
    int boxSize = stringToInt( strSize);
    boxSize = 200;
    float red = stringToFloat( strRed );
    float green = stringToFloat( strGreen );
    float blue = stringToFloat( strBlue );
    float alpha = stringToFloat( strAlpha );
    float complexor = stringToFloat( strComplexor);    

    if ( isCurrentlyHit( val )) {
        ofPushMatrix();
        ofEnableSmoothing();
        ofEnableAlphaBlending();
        ofEnableBlendMode(OF_BLENDMODE_ADD);
        ofTranslate(centerX + complexor, centerY, centerZ);
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
        drawBox(red, green, blue, alpha , centerX, complexor, centerY, centerZ, boxSize);    

        it->soundPlayer->setLoop(false);
        it->soundPlayer->stop();
        it->soundPlayer->setPosition(0);
    }

    m_dataPool->setAnimateValue( val + "_isHit", "0");
}

bool CBoxView::isCurrentlyHit( string val ){
//    fs<<"boxView->world_sample_b1_pointsInArea:"<<m_dataPool->getDataPool()["world_sample_b1_pointsInArea"]<<endl;
    string hitState = "0";
    if ( m_dataPool->findValueRef( val + "_isHit") != 0 )
    {
        hitState = *m_dataPool->findValueRef( val + "_isHit");
    }    
    int isHit = stringToInt( hitState );
    if ( isHit == 1 ){
        return true;
    }
    else{
        return false;
    }
}

float CBoxView::percentIncluded( string val ){
    string strPointsInArea = *m_dataPool->findValueRef( val + "_pointsInArea" );
    string strpointThreshold = *m_dataPool->findValueRef( val + "_pointThreshold" );
    int pointsInArea = stringToInt( strPointsInArea );
    int pointThreshold = stringToInt( strpointThreshold );

    return ofMap( pointsInArea, 0, pointThreshold, 0, 1);
}


float CBoxView::swellAnimation( string val ){
    string strBoxSize = *m_dataPool->findValueRef( val + "_boxSize");
    int boxSize = stringToInt( strBoxSize );

    return (boxSize/10) * cos(ofGetElapsedTimef()*15);
}

void CBoxView::drawBox( float red, float green, float blue, float alpha, float centerX, float complexor, float centerY, float centerZ, int boxSize )
{
    ofPushMatrix();
    ofEnableSmoothing();
    ofEnableAlphaBlending();
    //ofEnableBlendMode(OF_BLENDMODE_ADD);
    ofSetColor(red, green, blue, alpha);
    ofFill();
    ofBox(centerX + complexor, centerY, centerZ, boxSize);
    ofNoFill();
    ofSetColor(255,255,255);
    ofBox(centerX + complexor, centerY, centerZ, boxSize);
    ofDisableAlphaBlending();
    ofDisableSmoothing();
    ofPopMatrix();
}
