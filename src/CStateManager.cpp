#include "CStateManager.h"


//--------------------------------------------------------------
void CStateManager::setup() {
	ofSetLogLevel(OF_LOG_VERBOSE);
    ofSetVerticalSync(true);
    ofEnableAlphaBlending();
    ofEnableSmoothing();
    
    setDefaultValues();
    setupLights(); 
    ofSetFrameRate(60);
    
    g_menuVC = new CMenuViewController(m_red, m_green, m_blue, m_alpha);
    m_currentState = ST_MENU_STATE;

    g_world = new CWorld(); // world controls all buttons and sound

}

//--------------------------------------------------------------
void CStateManager::stateSwitch()
{
    if (m_currentState == ST_MENU_STATE) {
        m_currentState = ST_WORLD_STATE;
        if(!g_world) g_world = new CWorld();
    }else if(m_currentState == ST_WORLD_STATE) {
        m_currentState = ST_MENU_STATE;
    }
}

//--------------------------------------------------------------
void CStateManager::update() {
    
    if(g_menuVC->m_exitMenu){
        stateSwitch();
        g_menuVC->m_exitMenu = false;
    }
    
    if(m_currentState == ST_MENU_STATE){
        updateBackgroundColors();
    } else if(m_currentState == ST_WORLD_STATE){
        ofSoundUpdate();
        if(g_world) g_world->update(ofGetElapsedTimef());
    }
}

//--------------------------------------------------------------
void CStateManager::draw() {
    ofBackground(m_red, m_green, m_blue, m_alpha);
	
    if(m_currentState == ST_MENU_STATE) {
        
    }else if(m_currentState == ST_WORLD_STATE){            
        if(g_world) g_world->render();
    }

}


//--------------------------------------------------------------
void CStateManager::exit() {
	//Make changes to hardware before exiting 3DJ. i.e. re-set Kinect angle, etc
}

//--------------------------------------------------------------
void CStateManager::keyPressed (int key) {
	switch (key) {
		case ' ':
            stateSwitch();
			break;

		case'p':

			break;

		case '>':
		case '.':
			break;

		case '<':
		case ',':

			break;

		case '+':
		case '=':

			break;

		case '-':

			break;

		case 'w':

			break;

		case 'o':
			break;

		case 'c':

			break;
            
        case 'f':
            ofToggleFullscreen();
            break;
        case 'u':
            if(g_world){
                g_world->m_angle++;  
                if(g_world->m_angle>30) g_world->m_angle=30;
            }
			break;

        case 'd':
            if(g_world){
                g_world->m_angle--;
                if(g_world->m_angle<-30) g_world->m_angle=-30;
            }
			break;

		case OF_KEY_UP:
            
			break;

		case OF_KEY_DOWN:
    
			break;
	}
}

//--------------------------------------------------------------
void CStateManager::mouseDragged(int x, int y, int button)
{}

//--------------------------------------------------------------
void CStateManager::mousePressed(int x, int y, int button)
{}

//--------------------------------------------------------------
void CStateManager::mouseReleased(int x, int y, int button)
{}

//--------------------------------------------------------------
void CStateManager::windowResized(int w, int h)
{
    if(w < 800){
        ofSetWindowShape(800, h);
        w = 800;
    }
    if(h<600) ofSetWindowShape(w, 600);

}

void CStateManager::updateBackgroundColors()
{
    m_red = g_menuVC->m_r;
    m_green = g_menuVC->m_g;
    m_blue = g_menuVC->m_b;
    m_alpha = g_menuVC->m_a;
}

void CStateManager::cleanUp()
{
    if(g_world)  delete g_world;
    if(g_menuVC) delete g_menuVC;
    if(m_light)  delete m_light;
}

void CStateManager::setupLights()
{
    m_light = new ofLight();
    m_light->enable();
    m_light->setPointLight();
    m_light->setPosition(0, 0, 0); 
    ofEnableLighting();
}

void CStateManager::setDefaultValues()
{
    m_red = 50;
    m_green = 50;
    m_blue = 50;
    m_alpha = 255;
}
