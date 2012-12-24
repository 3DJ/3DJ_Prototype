//
//  Particles.cpp
//  openNI-3DJ
//
//  Created by Samuel Ruberti on 10/13/12.
//
//

#include "Particles.h"

Particles::Particles()
{
    billboards.getVertices().resize(NUM_BILLBOARDS);
    billboards.getColors().resize(NUM_BILLBOARDS);
    //billboards.getNormals().resize(NUM_BILLBOARDS,0);
    
    // ------------------------- billboard particles
    for (int i=0; i<NUM_BILLBOARDS; i++) {
        
        billboardVels[i].set(ofRandomf(), -1.0, ofRandomf());
        billboards.getVertices()[i].set(ofRandom(-500, 500),
                                        ofRandom(-500, 500),
                                        ofRandom(-500, 500));
        
        billboards.getColors()[i].set(ofColor(ofRandom(80, 180),ofRandom(180, 255), ofRandom(80, 180)));
        billboardSizeTarget[i] = ofRandom(4, 64);
        
    }

    billboards.setUsage( GL_DYNAMIC_DRAW );
    billboards.setMode(OF_PRIMITIVE_POINTS);
    
    billboardShader.load("Billboard");
    
    // we need to disable ARB textures in order to use normalized texcoords
    ofDisableArbTex();
    texture.loadImage("dot2.png");
    ofEnableAlphaBlending();
}

Particles::~Particles()
{
    
}

void Particles::render()
{
    string info = ofToString(ofGetFrameRate(), 2)+"\n";
    info += "Particle Count: "+ofToString(NUM_BILLBOARDS);
    ofDrawBitmapStringHighlight(info, 30, 30);
    
    ofSetColor(255);
    
    ofPushMatrix();
    
    ofEnableAlphaBlending();
    ofEnableBlendMode(OF_BLENDMODE_ADD);
    
    // bind the shader so that wee can change the
    // size of the points via the vert shader
    billboardShader.begin();
    
    ofEnablePointSprites();
    texture.getTextureReference().bind();
    billboards.draw();
    texture.getTextureReference().unbind();
    ofDisablePointSprites();
    
    billboardShader.end();
    
    ofPopMatrix();
}

void Particles::update()
{
    float t = (ofGetElapsedTimef()) * 0.9f;
    float div = 250.0;
    
    for (int i=0; i<NUM_BILLBOARDS; i++) {
        
        // noise
        ofVec3f vec(ofSignedNoise(t, billboards.getVertex(i).y/div, billboards.getVertex(i).z/div),
                    ofSignedNoise(billboards.getVertex(i).x/div, t, billboards.getVertex(i).z/div),
                    ofSignedNoise(billboards.getVertex(i).x/div, billboards.getVertex(i).y/div, t));
        
        vec *= 10 * ofGetLastFrameTime();
        billboardVels[i] += vec;
        billboards.getVertices()[i] += billboardVels[i];
        billboardVels[i] *= 0.94f;
        billboards.setNormal(i,ofVec3f(12 + billboardSizeTarget[i] * ofNoise(t+i),0,0));
    }
    
}