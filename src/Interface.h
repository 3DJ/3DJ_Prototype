#ifndef Kinect_3DJ_Interface_h
#define Kinect_3DJ_Interface_h

#include <iostream>
#include <vector>
#include "DataPool.h"
using namespace DataPool;

namespace Interface{
    typedef bool (*func)( vector<string> params );

    class IController{
    public:
        IController( CDataPoolSimple* dataPool = 0 ){
            m_dataPool = dataPool;
        }
        virtual bool update() = 0;
                
        CDataPoolSimple* m_dataPool;
    };

    class IView{
    public:
        IView( CDataPoolSimple* dataPool  = 0 ){
            m_dataPool = dataPool;
        }
        virtual bool draw() = 0;

        CDataPoolSimple* m_dataPool;
        // todo: Change it to unordered_multimap(since C++ 11)
//      multimap< func, vector<string>> mapUpdateFunctions;
    };

};
#endif
