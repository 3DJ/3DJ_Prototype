//
//  CBoxButton.cpp
//  Kinect_3DJ
//
//  Created by LJ on 10/1/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef Kinect_3DJ_DataPool_h
#define Kinect_3DJ_DataPool_h

#include <iostream>
#include <string>
#include <map>
#include <vector>
using namespace std;

#include "ofxXmlSettings.h"
#include "ConfigFile.h"
#include "Common.h"
using namespace Common;

namespace DataPool{
    
class CDataPoolSimple{

    public:
        static CDataPoolSimple& getInstance(){
            static CDataPoolSimple _instance;
            return _instance;
        }
        bool init();

        bool getEntityByName( string key, SEntity& entity);
        bool getValueByName( string key, string& val );
        bool getPointerByName( string key, void* &val );
        mapEntity getDataPool();        
        vector<mapEntity::iterator> getVector();

        // return value: false not mean U didn't create the entity. u need to check it by findValue
        bool createEntity( string key, SEntity entity );
        bool createRef( string key, void* val);

        // return value: false not mean U didn't set the value. u need to check it by findValue
        bool setEntity( string key, SEntity entity);
        bool setAnimateValue( string key, string val );
        bool setValue( string key, string val );
        // recommend 
        string* findValueRef( string val);
        SEntity* findEntityRefInVector( string val );
        // deprecated
        int findIndexInVector( string val );

    private:
        CDataPoolSimple(){ init(); }
        CDataPoolSimple(const CDataPoolSimple&);
        CDataPoolSimple& operator=(const CDataPoolSimple&);
        //
        bool loadFromFile( string filePath );
        bool saveToFile( string filePath );
        bool initEntities();
        bool initAnimations();
        bool initEntity( string key, string centerX, string centerY,
            string centerZ, string type, string soundName);
        bool initAnimation( string key );

        CConfigFile m_configFile;
        vector<mapEntity::iterator> m_vectorRefEntity;
        mapEntity m_mapDataPool;
    };
};


namespace DataPoolEx{

    typedef map<string, string> mapEntityEx;
    typedef map<string, string> mapWorld;    
    typedef map<string, mapEntityEx> mapGroup;
    typedef map<string, mapGroup> mapGroups;

    typedef map<string, string>::iterator iterElement;
    typedef pair<string, string> pairEntity;
    typedef map<string, mapEntityEx>::iterator iterGroup;
    typedef map<string, mapGroup>::iterator iterGroups;


    class CDataPoolEx{

    public:
        CDataPoolEx();

        bool getElementValue(  string group, string entity, string key, iterElement& e );
        bool getGroup( string name, mapGroup& group );
        mapEntityEx getWorld();
        mapGroups getGroups();
        // if the element didn't exist, the set function can create a new element. So u need use the get
        // function first to check whether it exists or not.
        // becos I didn't use insert(i use operation []).
        // if u didn't check it and set the exist item. the item will be overwritten.
        void setElementValue(  string group, string entity, string key, string val );
        void setEntityValue(  string group, string entity, mapEntityEx e );
        void setGroupValue(  string group, mapGroup val );

    private:
        // the data is set by the function append animation suffix will not be stored in the file.
        // that means it will reset when u close 3DJ and start over.
        void initGroup( mapGroup& group );
        bool initEntityAnimation( mapEntityEx& entity );
        bool initEntity( mapEntityEx& entity, string centerX, string centerY,
            string centerZ, string type, string soundName);

        // this map stores the data that will be saved in file.
        mapGroups m_mapGroups;
        // this map stores the animation data. not saved to file.
        mapGroups m_mapGroupsAnimation;

        mapEntityEx m_mapWorld;
    };
};

#endif
