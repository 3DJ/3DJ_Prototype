//
//  CBoxButton.cpp
//  Kinect_3DJ
//
//  Created by LJ on 1/10/12.
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

namespace DataPool{

    typedef map<string, string> mapWorld;
    typedef map<string, string> mapEntity;
    typedef map<string, mapEntity> mapGroup;
    typedef map<string, mapGroup> mapGroups;

    typedef map<string, string>::iterator iterElement;
    typedef pair<string, string> pairEntity;
    typedef map<string, mapEntity>::iterator iterGroup;
    typedef map<string, mapGroup>::iterator iterGroups;


    class CDataPool{

    public:
        CDataPool();

        bool getElementValue(  string group, string entity, string key, iterElement& e );
        bool getGroup( string name, mapGroup& group );
        mapEntity getWorld();
        mapGroups getGroups();
        // if the element didn't exist, the set function can create a new element. So u need use the get
        // function first to check whether it exists or not.
        // becos I didn't use insert(i use operation []).
        // if u didn't check it and set the exist item. the item will be overwritten.
        void setElementValue(  string group, string entity, string key, string val );
        void setEntityValue(  string group, string entity, mapEntity e );
        void setGroupValue(  string group, mapGroup val );

    private:
        // the data is set by the function append animation suffix will not be stored in the file.
        // that means it will reset when u close 3DJ and start over.
        void initGroup( mapGroup& group );
        bool initEntityAnimation( mapEntity& entity );
        bool initEntity( mapEntity& entity, string centerX, string centerY,
            string centerZ, string type, string soundName);

        // this map stores the data that will be saved in file.
        mapGroups m_mapGroups;
        // this map stores the animation data. not saved to file.
        mapGroups m_mapGroupsAnimation;

        mapEntity m_mapWorld;
    };

    class CDataPoolSimple{

    public:
        static CDataPoolSimple& getInstance(){
            static CDataPoolSimple _instance;
            return _instance;
        }
        bool init();

        bool getDateByName( string key, string& val );
        mapEntity getDataPool();
        mapEntity getDataPoolAnimation();
        vector<mapEntity::iterator> getVector();

        // if the key not exists. create new one.
        bool setDateAnimation( string key, string val );
        bool setDate( string key, string val );
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

        ofxXmlSettings m_ofxXmlFile;
        vector<mapEntity::iterator> m_vectorAllData;
        mapEntity m_mapDataPool;
        mapEntity m_mapDataPoolAnimation;

    };
};

#endif
