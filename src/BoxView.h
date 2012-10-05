//
//  BoxButton.h
//  Kinect_3DJ
//
//  Created by LJ on 9/23/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//


#ifndef Kinect_3DJ_BoxView_h
#define Kinect_3DJ_BoxView_h

#include "ofMain.h"
#include "DataPool.h"
#include "Interface.h"
#include "Common.h"
using namespace DataPool;
using namespace Interface;
using namespace Common;

class CBoxView: public IView{
    struct SBoxInfo{
        string name;
        ofSoundPlayer* soundPlayer;
    };

public:
    CBoxView(CDataPoolSimple* DataPool): IView(DataPool){
        SBoxInfo boxInfo;
        boxInfo.name = "world_sample_a1";
        boxInfo.soundPlayer = new ofSoundPlayer;
        boxInfo.soundPlayer->loadSound( m_dataPool->getDataPool()[boxInfo.name + "_soundName"] );
        m_boxInfo.push_back( boxInfo );

        boxInfo.name = "world_sample_a2";
        boxInfo.soundPlayer = new ofSoundPlayer;
        boxInfo.soundPlayer->loadSound( m_dataPool->getDataPool()[boxInfo.name + "_soundName"] );
        m_boxInfo.push_back( boxInfo );

        boxInfo.name = "world_sample_a3";
        boxInfo.soundPlayer = new ofSoundPlayer;
        boxInfo.soundPlayer->loadSound( m_dataPool->getDataPool()[boxInfo.name + "_soundName"] );
        m_boxInfo.push_back( boxInfo );

        boxInfo.name = "world_sample_a4";
        boxInfo.soundPlayer = new ofSoundPlayer;
        boxInfo.soundPlayer->loadSound( m_dataPool->getDataPool()[boxInfo.name + "_soundName"] );
        m_boxInfo.push_back( boxInfo );

        boxInfo.name = "world_sample_b1";
        boxInfo.soundPlayer = new ofSoundPlayer;
        boxInfo.soundPlayer->loadSound( m_dataPool->getDataPool()[boxInfo.name + "_soundName"] );
        m_boxInfo.push_back( boxInfo );

        boxInfo.name = "world_sample_b2";
        boxInfo.soundPlayer = new ofSoundPlayer;
        boxInfo.soundPlayer->loadSound( m_dataPool->getDataPool()[boxInfo.name + "_soundName"] );
        m_boxInfo.push_back( boxInfo );

        boxInfo.name = "world_sample_b3";
        boxInfo.soundPlayer = new ofSoundPlayer;
        boxInfo.soundPlayer->loadSound( m_dataPool->getDataPool()[boxInfo.name + "_soundName"] );
        m_boxInfo.push_back( boxInfo );

        boxInfo.name = "world_sample_b4";
        boxInfo.soundPlayer = new ofSoundPlayer;
        boxInfo.soundPlayer->loadSound( m_dataPool->getDataPool()[boxInfo.name + "_soundName"] );
        m_boxInfo.push_back( boxInfo );

        boxInfo.name = "world_sample_c1";
        boxInfo.soundPlayer = new ofSoundPlayer;
        boxInfo.soundPlayer->loadSound( m_dataPool->getDataPool()[boxInfo.name + "_soundName"] );
        m_boxInfo.push_back( boxInfo );

        boxInfo.name = "world_sample_c2";
        boxInfo.soundPlayer = new ofSoundPlayer;
        boxInfo.soundPlayer->loadSound( m_dataPool->getDataPool()[boxInfo.name + "_soundName"] );
        m_boxInfo.push_back( boxInfo );

        boxInfo.name = "world_sample_c3";
        boxInfo.soundPlayer = new ofSoundPlayer;
        boxInfo.soundPlayer->loadSound( m_dataPool->getDataPool()[boxInfo.name + "_soundName"] );
        m_boxInfo.push_back( boxInfo );

        boxInfo.name = "world_sample_c4";
        boxInfo.soundPlayer = new ofSoundPlayer;
        boxInfo.soundPlayer->loadSound( m_dataPool->getDataPool()[boxInfo.name + "_soundName"] );
        m_boxInfo.push_back( boxInfo );
    }
    bool init();

    void render( vector<SBoxInfo>::iterator it );
    bool isCurrentlyHit( string val );
    float percentIncluded( string val );
    float swellAnimation( string val );

    vector<SBoxInfo> m_boxInfo;
};

#endif
