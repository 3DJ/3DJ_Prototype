#pragma once

#include "ofMain.h"
#include "CMenuViewController.h"
#include "CWorld.h"
#include "CBoxController.h"
#include "CBoxView.h"
#include "Interface.h"
#include "DataPool.h"
using namespace DataPool;

// uncomment this to read from two kinects simultaneously
//#define USE_TWO_KINECTS



class CStateManager : public ofBaseApp {

    void cleanUp();

public:
	
	void setup();
	void update();
	void draw();
	void exit();
	
	void keyPressed(int key);
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void windowResized(int w, int h);
    void setupLights();
    void setDefaultValues();
    void updateBackgroundColors();
	   
    CMenuViewController *m_menuVC; //menu view controller: Menu State
    CWorld              *m_world; // world to hold and test all buttons, etc: World State

    IController*        m_boxController;
    IView*              m_boxView;

    //Variables to pass from m_menuVC to m_world, & vice vera
    int m_red, m_green, m_blue, m_alpha;
	
	// used for viewing the point cloud
	ofLight *m_light; 
};
