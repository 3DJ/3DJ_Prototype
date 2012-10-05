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
        IController( CDataPoolSimple* dataPool ){
            m_dataPool = dataPool;
        }
        virtual bool init() = 0;
                
        CDataPoolSimple* m_dataPool;
//     protected:
//         bool addFuncToMap( func f, vector<string> params ){
//             try{
//                 mapUpdateFunctions.insert(make_pair( f, params ));
//             }
//             catch(std::exception e){
//                 cout<<"controller addFuncToMap error->"<<e.what();
//                 return false;
//             }
//             return true;
//         }
// 
//         bool execute(){
//             try{
//                 for ( multimap< func, vector<string>>::iterator it = mapUpdateFunctions.begin();
//                     it != mapUpdateFunctions.end(); it++ ){
//                         it->first(it->second);
//                 }
//             }
//             catch(std::exception e){
//                 cout<<"controller execute error->"<<e.what();
//                 return false;
//             }
//             return true;
// 
//         }

        // todo: Change it to unordered_multimap(since C++ 11)
//      multimap< func, vector<string>> mapUpdateFunctions;
    };

    class IView{
    public:
        IView( CDataPoolSimple* dataPool ){
            m_dataPool = dataPool;
        }
        virtual bool init() = 0;

        CDataPoolSimple* m_dataPool;
        // todo: Change it to unordered_multimap(since C++ 11)
//      multimap< func, vector<string>> mapUpdateFunctions;
    };

};
#endif
