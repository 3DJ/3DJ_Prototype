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
using namespace DataPoolEx;

bool CDataPoolSimple::init()
{
    if ( !m_configFile.loadFromFile( "3dj.config", m_mapDataPool) ) { 
        return false; 
    }
    // this is used to test the load file function.       
    if ( !initEntities() ){ return false; }  
    // this is used to init the data which isn't save in the file.
    if ( !initAnimations()) { return false;}
    for ( mapEntity::iterator it = m_mapDataPool.begin(); it != m_mapDataPool.end(); it++ )
    {
        m_vectorRefEntity.push_back( it );
    }
    //    m_configFile.saveToFile( "3dj.config", m_mapDataPool);

    return true;
}

bool CDataPoolSimple::getEntityByName( string key, SEntity& entity)
{
    mapEntity::iterator iterData = m_mapDataPool.find( key );
    if ( iterData != m_mapDataPool.end() )
    {
        entity = iterData->second;
        return true;
    }

    return false;
}

bool CDataPoolSimple::getValueByName( string key, string& val )
{   
    mapEntity::iterator it = m_mapDataPool.find( key );
    if ( it != m_mapDataPool.end() )
    {
        val = it->second.value;
        return true;
    }

    return false;
}

bool CDataPoolSimple::getPointerByName( string key, void* &val )
{
    mapEntity::iterator it = m_mapDataPool.find( key );
    if ( it != m_mapDataPool.end() )
    {
        val = it->second.pointer;
        return true;
    }

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

    return true;
}

bool CDataPoolSimple::createEntity( string key, SEntity entity )
{
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
   
    return true;

}

bool CDataPoolSimple::createRef( string key, void* val)
{
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
        cout<<"CDataPoolSimple::setAnimateValue exception:"<<e.what();
        return false;
    }

    return true;
}

bool CDataPoolSimple::setAnimateValue( string key, string val )
{
    SEntity entity;
    entity.isSaved = true;
    mapEntity::iterator it = m_mapDataPool.find( key );

    try{  
        if ( it == m_mapDataPool.end() ){    
            entity.value = val;       
            m_mapDataPool.insert( it, make_pair( key, entity));
            // update the vector
            m_vectorRefEntity.push_back(it);        
        }  
        else{
            // this will be easy read. but it's inefficient.
            m_mapDataPool[key] = entity;
        }
    }
    catch(exception e){
        cout<<"CDataPoolSimple::setAnimateValue exception:"<<e.what();
        return false;
    }

    return true;
}

bool CDataPoolSimple::setValue( string key, string val )
{
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

    return true;
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

int CDataPoolSimple::findIndexInVector( string val )
{
    for ( int index = 0; index < m_vectorRefEntity.size(); index ++)
    {
        if ( m_vectorRefEntity[index]->first == val )
        {
            return index;
        }
    }

    return -1;
}

string* CDataPoolSimple::findValueRef( string val)
{
    mapEntity::iterator it = m_mapDataPool.find( val );

    if ( it != m_mapDataPool.end() ){      
        return &(it->second.value);
    }

    return 0;
    //     int index = findIndexInVector( val );
    //     return (&(m_vectorRefEntity[index]->second.value));
}

SEntity* CDataPoolSimple::findEntityRefInVector( string val )
{
    int index = findIndexInVector( val );
    return (&(m_vectorRefEntity[index]->second));
}


bool CDataPoolEx::getElementValue( string group, string entity, string key, iterElement& e )
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


bool CDataPoolEx::getGroup( string name, mapGroup& group )
{
    iterGroups iterMapGroups = m_mapGroups.find( name );
    if ( iterMapGroups != m_mapGroups.end() )
    {
        group = (iterMapGroups->second);
        return true;
    }

    return false;
}

mapWorld CDataPoolEx::getWorld()
{
    return m_mapWorld;
}

mapGroups CDataPoolEx::getGroups()
{
    return m_mapGroups;
}


void CDataPoolEx::setElementValue( string group, string entity, string key, string val )
{
    m_mapGroups[group][entity][key] = val;
}

void CDataPoolEx::setEntityValue( string group, string entity, mapEntityEx val )
{
    m_mapGroups[group][entity] = val;
}

void CDataPoolEx::setGroupValue( string group, mapGroup val )
{
    m_mapGroups[group] = val;
}

CDataPoolEx::CDataPoolEx()
{
    //mapBox.insert( pair<string, string>("x", 1));
    initGroup( m_mapGroups["sample"] );
}

bool CDataPoolEx::initEntityAnimation( mapEntityEx& entity )
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

bool CDataPoolEx::initEntity( mapEntityEx& entity, string centerX, string centerY,
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

void CDataPoolEx::initGroup(mapGroup& group )
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
