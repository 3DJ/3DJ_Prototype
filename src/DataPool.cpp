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

bool CDataPoolSimple::init()
{
    if ( !loadFromFile("config.3dj") ) {
        return false;
    }

    if ( !saveToFile(( "datapool.3dj"))) {
        return false;
    }
    // this is used to test the load file function.
    //if ( !initEntities() ){ return false; }
    // this is used to init the data which isn't save in the file.
    //if ( !initAnimations()) { return false;}
    for ( mapEntity::iterator it = m_mapDataPool.begin(); it != m_mapDataPool.end(); it++ )
    {
        m_vectorRefEntity.push_back( it );
    }
    //    m_configFile.saveToFile( "3dj.config", m_mapDataPool);

    return true;
}

bool CDataPoolSimple::getEntityByName( string key, SEntity& entity)
{
    lock(); // add lock for thread safe
    mapEntity::iterator iterData = m_mapDataPool.find( key );
    if ( iterData != m_mapDataPool.end() )
    {
        entity = iterData->second;
        return true;
    }
    unlock();

    return false;
}

bool CDataPoolSimple::getValueByName( string key, string& val )
{
    lock(); // add lock for thread safe
    mapEntity::iterator it = m_mapDataPool.find( key );
    if ( it != m_mapDataPool.end() )
    {
        val = it->second.value;
        return true;
    }
    unlock();

    return false;
}

bool CDataPoolSimple::getPointerByName( string key, void* &val)
{
    return getRefByName( key, val);
}

bool CDataPoolSimple::getRefByName( string key, void* &val )
{
    lock(); // add lock for thread safe
    mapEntity::iterator it = m_mapDataPool.find( key );
    if ( it != m_mapDataPool.end() )
    {
        val = it->second.pointer;
        return true;
    }
    unlock();

    return false;
}

mapEntity CDataPoolSimple::getDataPool()
{
    return m_mapDataPool;
}

vector<mapEntity::iterator> CDataPoolSimple::getVector()
{
    return m_vectorRefEntity;
}

bool CDataPoolSimple::setEntity( string key, SEntity entity)
{
    lock(); // add lock for thread safe
    mapEntity::iterator it = m_mapDataPool.find( key );

    try{
        if ( it == m_mapDataPool.end() ){
            return false;
        }
        else{
            // this will be easy read. but it's inefficient.
            m_mapDataPool[key] = entity;
        }
    }
    catch(exception e){
        cout<<"CDataPoolSimple::setEntity exception:"<<e.what();
        return false;
    }
    unlock();

    return true;
}

bool CDataPoolSimple::createEntity( string key, SEntity entity )
{
    lock(); // add lock for thread safe
    mapEntity::iterator it = m_mapDataPool.find( key );

    try{
        if ( it == m_mapDataPool.end() ){
            m_mapDataPool.insert( it, make_pair( key, entity));
            // update the vector
            m_vectorRefEntity.push_back(it);
        }
        else{
            // exist this key
            return false;
        }
    }
    catch(exception e){
        cout<<"CDataPoolSimple::setEntity exception:"<<e.what();
        // exception
        return false;
    }
    unlock();

    return true;

}

bool CDataPoolSimple::createRef( string key, void* val)
{
    lock(); // add lock for thread safe
    SEntity entity;
    entity.isSaved = false;
    mapEntity::iterator it = m_mapDataPool.find( key );

    try{
        if ( it == m_mapDataPool.end() ){
            entity.pointer = val;
            m_mapDataPool.insert( it, make_pair( key, entity));
            // update the vector
            //m_vectorRefEntity.push_back(it);
        }
        else{
            return false;
        }
    }
    catch(exception e){
        cout<<"CDataPoolSimple::setRefValue exception:"<<e.what();
        return false;
    }
    unlock();

    return true;
}

bool CDataPoolSimple::setValue( string key, string val )
{
    lock(); // add lock for thread safe
    SEntity entity;
    entity.isSaved = true;
    entity.value = val;

    mapEntity::iterator it = m_mapDataPool.find( key );
    try{
        if ( it == m_mapDataPool.end() ){
            return false;
        }
        else{
            // this will be easy read. but it's inefficient.
            m_mapDataPool[key] = entity;
        }
    }
    catch(exception e){
        cout<<"CDataPoolSimple::setValue exception:"<<e.what();
        return false;
    }
    unlock();

    return true;
}

int CDataPoolSimple::findIndexInVector( string val )
{
    lock(); // add lock for thread safe
    for ( int index = 0; index < m_vectorRefEntity.size(); index ++)
    {
        if ( m_vectorRefEntity[index]->first == val )
        {
            return index;
        }
    }
    unlock();

    return -1;
}

string* CDataPoolSimple::findValueRef( string val)
{
    lock(); // add lock for thread safe
    mapEntity::iterator it = m_mapDataPool.find( val );

    if ( it != m_mapDataPool.end() ){
        return &(it->second.value);
    }
    unlock();

    return 0;
}

SEntity* CDataPoolSimple::findEntityRefInVector( string val )
{
    lock(); // add lock for thread safe
    int index = findIndexInVector( val );
    unlock();

    return (&(m_vectorRefEntity[index]->second));
}

bool CDataPoolSimple::loadFromFile( string filePath )
{
    return m_configFile.loadFromFile( filePath.c_str(), m_mapDataPool);
}

bool CDataPoolSimple::saveToFile( string filePath )
{
    return m_configFile.saveToFile( filePath.c_str(), m_mapDataPool);
}

bool CDataPoolSimple::initEntity( string key, string centerX, string centerY,
                                  string centerZ, string type, string soundName)
{
    SEntity entity;
    entity.isSaved = true;

    try{
        entity.value = centerX;
        m_mapDataPool[key + "_centerX"] = entity;
        entity.value = centerY;
        m_mapDataPool[key + "_centerY"] = entity;
        entity.value = centerZ;
        m_mapDataPool[key + "_centerZ"] = entity;
        entity.value = type;
        m_mapDataPool[key + "_type"]    = entity;
        entity.value = soundName;
        m_mapDataPool[key + "_soundName"] = entity;
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
    SEntity entity;
    entity.isSaved = false;

    string boxSize = "250", redVal = "255",  greenVal = "255",  blueVal = "255",  alphaVal = "30";
    string speed    = "1.0";
    string volume   = "1.0";
    string pan      = "0";
    string isRepeat = "0";
    string pointsInArea = "0";
    string pointThreshold = "2000";
    string threshold = "2";

    try{
        entity.value = boxSize;
        m_mapDataPool[key + "_boxSize"] = entity;
        entity.value = redVal;
        m_mapDataPool[key + "_redVal"]  = entity;
        entity.value = greenVal;
        m_mapDataPool[key + "_greenVal"]= entity;
        entity.value = blueVal;
        m_mapDataPool[key + "_blueVal"] = entity;
        entity.value = alphaVal;
        m_mapDataPool[key + "_alphaVal"]= entity;

        entity.value = speed;
        m_mapDataPool[key + "_speed"]   = entity;
        entity.value = volume;
        m_mapDataPool[key + "_volume"]  = entity;
        entity.value = pan;
        m_mapDataPool[key + "_pan"]     = entity;
        entity.value = isRepeat;
        m_mapDataPool[key + "_repeat"]  = entity;
        entity.value = pointsInArea;
        m_mapDataPool[key + "_pointsInArea"] = entity;
        entity.value = pointThreshold;
        m_mapDataPool[key + "_pointThreshold"] = entity;
        entity.value = threshold;
        m_mapDataPool[key + "_threshold"]  = entity;
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
