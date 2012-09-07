#pragma once

#include "ofMain.h"
#include "CMenuViewController.h"
#include "CWorld.h"

// uncomment this to read from two kinects simultaneously
//#define USE_TWO_KINECTS

typedef enum st {
    ST_None = 0,
    ST_MENU_STATE,
    ST_WORLD_STATE,
}CurrentState;

class CStateManager : public ofBaseApp {

    void cleanUp();

public:
	
	void setup();
    void stateSwitch();
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
	
    CurrentState m_currentState;
    CMenuViewController *g_menuVC; //menu view controller: Menu State
    CWorld              *g_world; // world to hold and test all buttons, etc: World State
    
    //Variables to pass from g_menuVC to g_world, & vice vera
    int m_red, m_green, m_blue, m_alpha;
	
	// used for viewing the point cloud
	ofLight *m_light; 
};
