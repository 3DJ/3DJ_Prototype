#include "testApp.h"
#include "ofAppGlutWindow.h"

int main() {
    ofAppGlutWindow window;
    //ofSetupOpenGL(&window, 1920, 1024, OF_WINDOW);
    ofSetupOpenGL(&window, 720, 640, OF_FULLSCREEN);
    ofRunApp(new testApp());
}
