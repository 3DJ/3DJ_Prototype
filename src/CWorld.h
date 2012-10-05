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

namespace nsWorld{

    class CWorld{

    public:
        // singleton this class. becos we just need one world.
        static CWorld& getInstance(){
            static CWorld _instance;
            return _instance;
        }

        bool init( IController* controller, IView* view ){

            m_equalizerView = new CEQView;
            m_sonicOcean    = new CSonicOcean;
            m_easyCam       = new ofEasyCam;

            m_controller = controller;
            m_view = view;
            return true;
        }

        bool unInit(){

            if(m_easyCam) delete m_easyCam;
            if(m_equalizerView) delete m_equalizerView;
            if(m_sonicOcean) delete m_sonicOcean;
            m_controller = 0;
            m_view = 0;
        }

        bool update(){

            ofBackground(100, 100, 100);
            m_equalizerView->soundUpdate();
            m_sonicOcean->soundUpdate();

            if ( !m_controller->init( ) ) {
                return false;
            }

            return true;
        }

        bool draw(){
            m_easyCam->begin();

            ofPushMatrix();
            ofScale(-1, 1);
            ofTranslate((ofGetWidth()/2)-320, (ofGetHeight()/2) -240, -1000); // center the points a bit
            ofRotateX(180);                   //Rotate around Axis
            // ofTranslate(0,0,1000);            // Move back into Camera View
            ofTranslate(3 ,3, 3 *-800 + 1000);
            ofScale(3,3,3);
            // init view
            m_view->init();
            ofPopMatrix();

            ofPushMatrix();                 // ofPushMatrix before ofTranslate.
            ofTranslate(0, -1.5*ofGetHeight(), -5000);
            m_sonicOcean->drawEQSonicOcean();//EQ OCEAN
            ofPopMatrix();
            m_easyCam->end();

            return true;
        }

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
