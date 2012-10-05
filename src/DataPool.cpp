//
//  CBoxButton.cpp
//  Kinect_3DJ
//
//  Created by LJ on 1/10/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include "Common.h"
#include "DataPool.h"
using namespace Common;
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
    // if ( !initEntities() ){ return false; }
    if ( !initAnimations()) { return false;}

    if ( !loadFromFile( "3dj.config") ) { return false; };
    // this is used to test the load file function.
    // loadFromFile("log");

    for ( mapEntity::iterator it = m_mapDataPool.begin(); it != m_mapDataPool.end(); it++ )
    {
        m_vectorAllData.push_back( it );
    }

    for ( mapEntity::iterator it = m_mapDataPoolAnimation.begin(); it != m_mapDataPoolAnimation.end(); it++ )
    {
        m_vectorAllData.push_back( it );
    }

    return true;
}

bool CDataPoolSimple::loadFromFile( string filePath )
{
    if (m_ofxXmlFile.loadFile( filePath )){
        cout<<"Load file success" <<endl;
    }
    else{
        cout<<"Load file failed" <<endl;
        return false;
    }

    string val;
    string number = m_ofxXmlFile.getValue("number", val );
    int count = stringToInt( number );
    int index = 0;
    // using this "_" to name the tag. tiny xml not allow to name tag with number.
    string underScore = "_";
    // clear the pool and then load it from file.
    m_mapDataPool.clear();
    for ( int index = 0; index < count; index++ )
    {
        string key = m_ofxXmlFile.getAttribute( underScore + intToString(index), "key", val, 0);
        m_mapDataPool[key] = m_ofxXmlFile.getValue( underScore + intToString(index), val );
    }

    return true;
}

bool CDataPoolSimple::saveToFile( string filePath)
{
    m_ofxXmlFile.addTag("3-dj");
    m_ofxXmlFile.setAttribute("3-dj", "link", "www.3-dj.com", 0);
    m_ofxXmlFile.pushTag("3-dj");
    m_ofxXmlFile.addTag("number");
    m_ofxXmlFile.setValue("number", intToString(m_mapDataPool.size()) );
    int index = 0;
    // using this "_" to name the tag. tiny xml not allow to name tag with number.
    string underScore = "_";
    for ( mapEntity::iterator it = m_mapDataPool.begin(); it != m_mapDataPool.end(); it++ )
    {
        m_ofxXmlFile.addTag( underScore + intToString(index));
        m_ofxXmlFile.setAttribute( underScore + intToString(index), "key", it->first, 0);
        m_ofxXmlFile.setValue( underScore + intToString(index), it->second );
        index ++;
    }
    m_ofxXmlFile.popTag();
    if (m_ofxXmlFile.saveFile( filePath )){
        cout<<"Saving file success" << endl;
    }
    else{
        cout<<"Saving file failed" <<endl;
        return false;
    }

    return true;
}

bool CDataPoolSimple::getDateByName( string key, string& val )
{
    mapEntity::iterator iterData = m_mapDataPool.find( key );
    if ( iterData != m_mapDataPool.end() )
    {
        val = iterData->second;
        return true;
    }

    mapEntity::iterator iterDataAnimation = m_mapDataPoolAnimation.find( key );
    if ( iterDataAnimation != m_mapDataPoolAnimation.end() )
    {
        val = iterDataAnimation->second;
        return true;
    }

    return false;
}

mapEntity CDataPoolSimple::getDataPool()
{
    return m_mapDataPool;
}

mapEntity CDataPoolSimple::getDataPoolAnimation()
{
    return m_mapDataPoolAnimation;
}

vector<mapEntity::iterator> CDataPoolSimple::getVector()
{
    return m_vectorAllData;
}

bool CDataPoolSimple::setDateAnimation( string key, string val )
{
    try{
        m_mapDataPoolAnimation[key] = val;
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
        m_mapDataPool[key] = val;
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
        m_mapDataPool[key + "_centerX"] = centerX;
        m_mapDataPool[key + "_centerY"] = centerY;
        m_mapDataPool[key + "_centerZ"] = centerZ;
        m_mapDataPool[key + "_type"]    = type;
        m_mapDataPool[key + "_soundName"] = soundName;
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
        m_mapDataPoolAnimation[key + "_boxSize"] = boxSize;

        m_mapDataPoolAnimation[key + "_redVal"]  = redVal;
        m_mapDataPoolAnimation[key + "_greenVal"]= greenVal;
        m_mapDataPoolAnimation[key + "_blueVal"] = blueVal;
        m_mapDataPoolAnimation[key + "_alphaVal"]= alphaVal;

        m_mapDataPoolAnimation[key + "_speed"]   = speed;
        m_mapDataPoolAnimation[key + "_volume"]  = volume;
        m_mapDataPoolAnimation[key + "_pan"]     = pan;
        m_mapDataPoolAnimation[key + "_repeat"]  = isRepeat;
        m_mapDataPoolAnimation[key + "_pointsInArea"] = pointsInArea;
        m_mapDataPoolAnimation[key + "_pointThreshold"] = pointThreshold;
        m_mapDataPoolAnimation[key + "_threshold"]  = threshold;
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
    for ( int index = 0; index < m_vectorAllData.size(); index ++)
    {
        if ( m_vectorAllData[index]->first == val )
        {
            return index;
        }
    }

    return -1;
}
