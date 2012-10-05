#ifndef Kinect_3DJ_CWorld_h
#define Kinect_3DJ_CWorld_h

#include <vector>
using namespace std;

#include "Entity.h"
#include "KinectData.h"
#include "PointView.h"
#include "EQView.h"
#include "SonicOcean.h"

#include "DataPool.h"
#include "Interface.h"
using namespace Interface;
using namespace DataPool;

namespace World{

    class CWorld{

    public:
        // singleton this class. becos we just need one world.
        static CWorld& getInstance(){
            static CWorld _instance;
            return _instance;
        }

        bool init( IController* controller, IView* view );

        bool unInit();

        bool update();

        bool draw();

        ofEasyCam *m_easyCam;
        CEQView *m_equalizerView;
        CSonicOcean *m_sonicOcean;

        int m_scale;
        int m_angle;

    private:
        // singleton this class. becos we just need one world.
        CWorld() {}
        CWorld( const CWorld& );
        CWorld& operator=( const CWorld&);

        IController* m_controller;
        IView* m_view;
    };
};
#endif
