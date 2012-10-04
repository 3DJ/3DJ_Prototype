//
//  CBoxButton.cpp
//  Kinect_3DJ
//
//  Created by LJ on 1/10/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include "DataPool.h"
using namespace DataPool;

bool CDataPool::getElementValue( string group, string entity, string key, iterElement& e )
{
    iterGroups iterMapGroup = m_mapGroups.find( group );
    if ( iterMapGroup != m_mapGroups.end() )
    {
        iterGroup iterMapEntity = iterMapGroup->second.find( entity );
        if ( iterMapEntity != iterMapGroup->second.end() )
        {
            e = iterMapEntity->second.find( key );
            if ( e != iterMapEntity->second.end() )
            {
                return true;
            }
        }
    }

    return false;
}


bool CDataPool::getGroup( string name, mapGroup& group )
{
    iterGroups iterMapGroups = m_mapGroups.find( name );
    if ( iterMapGroups != m_mapGroups.end() )
    {
        group = (iterMapGroups->second);
        return true;
    }

    return false;
}

mapWorld CDataPool::getWorld()
{
    return m_mapWorld;
}

mapGroups CDataPool::getGroups()
{
    return m_mapGroups;
}


void CDataPool::setElementValue( string group, string entity, string key, string val )
{
    m_mapGroups[group][entity][key] = val;
}

void CDataPool::setEntityValue( string group, string entity, mapEntity val )
{
    m_mapGroups[group][entity] = val;
}

void CDataPool::setGroupValue( string group, mapGroup val )
{
    m_mapGroups[group] = val;
}

CDataPool::CDataPool()
{
    //mapBox.insert( pair<string, string>("x", 1));
    initGroup( m_mapGroups["sample"] );
}

bool CDataPool::initEntityAnimation( mapEntity& entity )
{
    string boxSize = "250", redVal = "255",  greenVal = "255",  blueVal = "255",  alphaVal = "30";

    string speed    = "1.0";
    string volume   = "1.0";
    string pan      = "0";
    string isRepeat = "0";   
    string pointsInArea = "0";
    string pointThreshold = "2000";
    string threshold = "2";

    try{
        entity["boxSize"] = boxSize; 

        entity["redVal"]  = redVal;
        entity["greenVal"]= greenVal;
        entity["blueVal"] = blueVal;
        entity["alphaVal"]= alphaVal;

        entity["speed"]   = speed;
        entity["volume"]  = volume;
        entity["pan"]     = pan;
        entity["repeat"]  = isRepeat;
        entity["pointsInArea"] = pointsInArea;
        entity["pointThreshold"] = pointThreshold;
        entity["threshold"]  = threshold;
    }
    catch(exception e)
    {
        cout<<"throw error:"<<e.what();
        return false;
    }

    return true;
}

bool CDataPool::initEntity( mapEntity& entity, string centerX, string centerY,
    string centerZ, string type, string soundName)
{
    try{
        entity["centerX"] = centerX;
        entity["centerY"] = centerY;
        entity["centerZ"] = centerZ;
        entity["type"]    = type;
        entity["soundName"] = soundName;
    }
    catch( exception e )
    {
        cout<<"throw error:"<<e.what();
        return false;
    }

    return true;
}

void CDataPool::initGroup(mapGroup& group )
{    
    initEntityAnimation( group["a1"] ); 
    initEntity( group["a1"], "375", "-250", "1000", "ET_SwapButton","sounds/Melody/GuitarStrummin.wav");
    initEntityAnimation( group["a2"] ); 
    initEntity( group["a2"], "125", "-250", "1000", "ET_MusicSampleButton","sounds/Melody/Piano.wav" );
    initEntityAnimation( group["a3"] ); 
    initEntity( group["a3"], "-125", "-250", "1000", "ET_MusicSampleButton","sounds/Melody/GuitarPick.wav" );
    initEntityAnimation( group["a4"] ); 
    initEntity( group["a4"], "-325", "-250", "1000", "ET_MusicSampleButton","sounds/Melody/Blip_Melody_01.wav" );

    initEntityAnimation( group["b1"] ); 
    initEntity( group["b1"], "375", "0", "1000", "ET_EffectsButton","sounds/Effects/Warp_1.wav" );    
    initEntityAnimation( group["b2"] ); 
    initEntity( group["b2"], "125", "0", "1000", "ET_MusicSampleButton","sounds/Effects/Uplifter.wav" );
    initEntityAnimation( group["b3"] ); 
    initEntity( group["b3"], "-125", "0", "1000", "ET_MusicSampleButton","sounds/Bass/BassSlap.wav" );
    initEntityAnimation( group["b4"] ); 
    initEntity( group["b4"], "-375", "0", "1000", "ET_MusicSampleButton","sounds/Bass/NastyBass.wav" );


    initEntityAnimation( group["c1"] ); 
    initEntity( group["c1"], "375", "250", "1000", "ET_EffectsButton","sounds/Effects/Vinyl_Scratch_01.wav" );    
    initEntityAnimation( group["c2"] ); 
    initEntity( group["c2"], "125", "250", "1000", "ET_MusicSampleButton","sounds/Effects/RemixCrazyScratch_FX_02.wav" );
    initEntityAnimation( group["c3"] ); 
    initEntity( group["c3"], "-125", "250", "1000", "ET_MusicSampleButton","sounds/Beat/TimbalesMerged_1.wav" );
    initEntityAnimation( group["c4"] ); 
    initEntity( group["c4"], "-375", "250", "1000", "ET_MusicSampleButton","sounds/Beat/Wee_Kick.wav" );
}


bool CDataPoolSimple::init()
{
    if ( !initEntities() ){ return false; }
    if ( !initAnimations()) { return false;}

    for ( mapEntity::iterator it = mapDataPool.begin(); it != mapDataPool.end(); it++ )
    {
        vectorAllData.push_back( it );
    }

    for ( mapEntity::iterator it = mapDataPoolAnimation.begin(); it != mapDataPoolAnimation.end(); it++ )
    {
        vectorAllData.push_back( it );
    }

    return true;
}


bool CDataPoolSimple::getDateByName( string key, string& val )
{
    mapEntity::iterator iterData = mapDataPool.find( key );
    if ( iterData != mapDataPool.end() )
    {
        val = iterData->second;
        return true;
    }

    mapEntity::iterator iterDataAnimation = mapDataPoolAnimation.find( key );
    if ( iterDataAnimation != mapDataPoolAnimation.end() )
    {
        val = iterDataAnimation->second;
        return true;
    }

    return false;
}

mapEntity CDataPoolSimple::getDataPool()
{
    return mapDataPool;
}

mapEntity CDataPoolSimple::getDataPoolAnimation()
{
    return mapDataPoolAnimation;
}

vector<mapEntity::iterator> CDataPoolSimple::getVector()
{
    return vectorAllData;
}

bool CDataPoolSimple::setDateAnimation( string key, string val )
{    
    try{
        mapDataPoolAnimation[key] = val;
    }
    catch(exception e){    
        cout<<"CDataPoolSimple::setDateAnimation exception:"<<e.what();
        return false;
    }

    return true;
}

bool CDataPoolSimple::setDate( string key, string val )
{
    try{
        mapDataPool[key] = val;
    }
    catch(exception e){
        cout<<"CDataPoolSimple::setDate exception:"<<e.what();
        return false;
    }

    return true;
}


bool CDataPoolSimple::initEntity( string key, string centerX, string centerY,
    string centerZ, string type, string soundName)
{    
    try{
        mapDataPool[key + "_centerX"] = centerX;
        mapDataPool[key + "_centerY"] = centerY;
        mapDataPool[key + "_centerZ"] = centerZ;
        mapDataPool[key + "_type"]    = type;
        mapDataPool[key + "_soundName"] = soundName;
    }
    catch( exception e )
    {
        cout<<"throw error:"<<e.what();
        return false;
    }

    return true;
}


bool CDataPoolSimple::initAnimation( string key )
{
    string boxSize = "250", redVal = "255",  greenVal = "255",  blueVal = "255",  alphaVal = "30";

    string speed    = "1.0";
    string volume   = "1.0";
    string pan      = "0";
    string isRepeat = "0";   
    string pointsInArea = "0";
    string pointThreshold = "2000";
    string threshold = "2";

    try{
        mapDataPoolAnimation[key + "_boxSize"] = boxSize; 

        mapDataPoolAnimation[key + "_redVal"]  = redVal;
        mapDataPoolAnimation[key + "_greenVal"]= greenVal;
        mapDataPoolAnimation[key + "_blueVal"] = blueVal;
        mapDataPoolAnimation[key + "_alphaVal"]= alphaVal;

        mapDataPoolAnimation[key + "_speed"]   = speed;
        mapDataPoolAnimation[key + "_volume"]  = volume;
        mapDataPoolAnimation[key + "_pan"]     = pan;
        mapDataPoolAnimation[key + "_repeat"]  = isRepeat;
        mapDataPoolAnimation[key + "_pointsInArea"] = pointsInArea;
        mapDataPoolAnimation[key + "_pointThreshold"] = pointThreshold;
        mapDataPoolAnimation[key + "_threshold"]  = threshold;
    }
    catch(exception e)
    {
        cout<<"throw error:"<<e.what();
        return false;
    }

    return true;
}


bool CDataPoolSimple::initEntities()
{
    if( !initEntity( "world_sample_a1", "375", "-250", "1000", "ET_SwapButton","sounds/Melody/GuitarStrummin.wav")){return false;}
    if( !initEntity( "world_sample_a2", "125", "-250", "1000", "ET_MusicSampleButton","sounds/Melody/Piano.wav" )){return false;}
    if( !initEntity( "world_sample_a3", "-125", "-250", "1000", "ET_MusicSampleButton","sounds/Melody/GuitarPick.wav" )){return false;}
    if( !initEntity( "world_sample_a4", "-375", "-250", "1000", "ET_MusicSampleButton","sounds/Melody/Blip_Melody_01.wav" )){return false;}

    if( !initEntity( "world_sample_b1", "375", "0", "1000", "ET_EffectsButton","sounds/Effects/Warp_1.wav" )){return false;}    
    if( !initEntity( "world_sample_b2", "125", "0", "1000", "ET_MusicSampleButton","sounds/Effects/Uplifter.wav" )){return false;}
    if( !initEntity( "world_sample_b3", "-125", "0", "1000", "ET_MusicSampleButton","sounds/Bass/BassSlap.wav" )){return false;}
    if( !initEntity( "world_sample_b4", "-375", "0", "1000", "ET_MusicSampleButton","sounds/Bass/NastyBass.wav" )){return false;}

    if( !initEntity( "world_sample_c1", "375", "250", "1000", "ET_EffectsButton","sounds/Effects/Vinyl_Scratch_01.wav" )){return false;}    
    if( !initEntity( "world_sample_c2", "125", "250", "1000", "ET_MusicSampleButton","sounds/Effects/RemixCrazyScratch_FX_02.wav" )){return false;}
    if( !initEntity( "world_sample_c3", "-125", "250", "1000", "ET_MusicSampleButton","sounds/Beat/TimbalesMerged_1.wav" )){return false;}
    if( !initEntity( "world_sample_c4", "-375", "250", "1000", "ET_MusicSampleButton","sounds/Beat/Wee_Kick.wav" )){return false;}

    return true;
}

bool CDataPoolSimple::initAnimations()
{
    if( !initAnimation( "world_sample_a1" ) ){return false;}
    if( !initAnimation( "world_sample_a2" ) ){return false;}
    if( !initAnimation( "world_sample_a3" ) ){return false;}
    if( !initAnimation( "world_sample_a4" ) ){return false;}

    if( !initAnimation( "world_sample_b1" ) ){return false;}
    if( !initAnimation( "world_sample_b2" ) ){return false;}
    if( !initAnimation( "world_sample_b3" ) ){return false;}
    if( !initAnimation( "world_sample_b4" ) ){return false;}

    if( !initAnimation( "world_sample_c1" ) ){return false;}
    if( !initAnimation( "world_sample_c2" ) ){return false;}
    if( !initAnimation( "world_sample_c3" ) ){return false;}
    if( !initAnimation( "world_sample_c4" ) ){return false;}   

    return true;
}

int CDataPoolSimple::findIndexInVector( string val )
{
    for ( int index = 0; index < vectorAllData.size(); index ++)
    {
        if ( vectorAllData[index]->first == val )
        {
            return index;
        }
    }

    return -1;
}