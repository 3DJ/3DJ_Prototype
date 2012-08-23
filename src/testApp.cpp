#include "testApp.h"


//--------------------------------------------------------------
void testApp::setup() {
	ofSetLogLevel(OF_LOG_VERBOSE);
    ofSetVerticalSync(true);
    ofEnableAlphaBlending();
    ofEnableSmoothing();

    g_world = new CWorld(); // world controls all buttons and sound
	ofSetFrameRate(60);
    //easyCam.setFov(35.0f);
    //easyCam.setTarget(ofVec3f(0,0,-1000));
    //easyCam.setDistance(1600);

    light.enable();
    light.setPointLight();
    light.setPosition(0, 0, 0);
}

//--------------------------------------------------------------
void testApp::update() {

	ofSoundUpdate();
    g_world->update(ofGetElapsedTimef());
}

//--------------------------------------------------------------
void testApp::draw() {
	ofEnableLighting();
	ofSetColor(255, 255, 255);

    //easyCam.begin();
    g_world->render();
    //easyCam.end();

}


//--------------------------------------------------------------
void testApp::exit() {
	//g_world->kinect.setCameraTiltAngle(0); // zero the tilt on exit
	//g_world->kinect.close();
}

//--------------------------------------------------------------
void testApp::keyPressed (int key) {
	switch (key) {
		case ' ':

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

        case 'u':
            g_world->m_angle++;
			if(g_world->m_angle>30) g_world->m_angle=30;
			//g_world->kinect.setCameraTiltAngle(g_world->m_angle);
			break;

        case 'd':
            g_world->m_angle--;
			if(g_world->m_angle<-30) g_world->m_angle=-30;
			//g_world->kinect.setCameraTiltAngle(g_world->m_angle);
			break;

		case OF_KEY_UP:
            g_world->m_angle++;
			if(g_world->m_angle>30) g_world->m_angle=30;
			//g_world->kinect.setCameraTiltAngle(g_world->m_angle);
			break;

		case OF_KEY_DOWN:
			g_world->m_angle--;
			if(g_world->m_angle<-30) g_world->m_angle=-30;
			//g_world->kinect.setCameraTiltAngle(g_world->m_angle);
			break;
	}
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button)
{}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button)
{}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button)
{}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h)
{
    if(w < 800){
        ofSetWindowShape(800, h);
        w = 800;
    }
    if(h<600) ofSetWindowShape(w, 600);

}

//Clean up TestApp
void testApp::cleanUp()
{
    if(g_world) delete g_world;
}


