#ifndef Kinect_3DJ_Interface_h
#define Kinect_3DJ_Interface_h

#include <iostream>
#include <vector>
#include "DataPool.h"
using namespace DataPool;

namespace Interface{
    typedef bool (*func)( vector<string> params );

    class IController{
        // inherit from this class to implement your controller.
    public:
        IController( ){
            m_dataPool = &CDataPool::getInstance();
        }
        virtual bool update() = 0;
                
        CDataPool* m_dataPool;
    };

    class IView{
        // inherit from this class to implement your view.
    public:
        IView( ){
            m_dataPool = &CDataPool::getInstance();
        }
        virtual bool draw() = 0;

        CDataPool* m_dataPool;
        // todo: Change it to unordered_multimap(since C++ 11)
//      multimap< func, vector<string>> mapUpdateFunctions;
    };

};
#endif
