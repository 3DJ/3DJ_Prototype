//
//  Particles.h
//  openNI-3DJ
//
//  Created by Samuel Ruberti on 10/13/12.
//
//

#ifndef __openNI_3DJ__Particles__
#define __openNI_3DJ__Particles__
#include "ofMain.h"

#define NUM_BILLBOARDS 1000

class Particles : public ofBaseApp {

public:
    Particles();
    ~Particles();
    void render();
    void update();

    float billboardSizeTarget[NUM_BILLBOARDS];
    
    ofShader  billboardShader;
    ofImage   texture;
    ofVboMesh billboards;
    ofVec3f   billboardVels[NUM_BILLBOARDS];

};


#endif /* defined(__openNI_3DJ__Particles__) */
