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

    m_boxController = new CBoxController(&CDataPoolSimple::getInstance());
    m_boxView = new CBoxView( &CDataPoolSimple::getInstance());

    m_menuVC = new CMenuViewController( m_red, m_green, m_blue, m_alpha, &CDataPoolSimple::getInstance());
    g_currentState = ST_MENU_STATE;

    m_world = &CWorld::getInstance(); // world controls all buttons and sound
}

//--------------------------------------------------------------
void CStateManager::update() {

    if (g_currentState == ST_MENU_STATE) {
        m_world->init( 0, m_menuVC);
    }else if(g_currentState == ST_BOX_STATE) {
        m_world->init( m_boxController, m_boxView );
    }

    updateBackgroundColors();
    ofSoundUpdate();

    m_world->update(ofGetElapsedTimef());

}

//--------------------------------------------------------------
void CStateManager::draw() {
    ofBackground(m_red, m_green, m_blue, m_alpha);
    m_world->draw();
}


//--------------------------------------------------------------
void CStateManager::exit() {
	//Make changes to hardware before exiting 3DJ. i.e. re-set Kinect angle, etc
    if(!m_menuVC){ delete m_menuVC;}
    if(!m_boxController) {delete m_boxController;}
    if(!m_boxView) {delete m_boxView;}
}

//--------------------------------------------------------------
void CStateManager::keyPressed (int key) {
	switch (key) {

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

        case 'd':

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
    //if(m_world) m_world->m_navigationController->m_navConButtons->windowSizeChanged();

}

void CStateManager::updateBackgroundColors()
{
    m_red = m_menuVC->m_r;
    m_green = m_menuVC->m_g;
    m_blue = m_menuVC->m_b;
    m_alpha = m_menuVC->m_a;
}

void CStateManager::cleanUp()
{
    if(m_world)  delete m_world;
    if(m_menuVC) delete m_menuVC;
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
