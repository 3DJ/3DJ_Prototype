//
//  CSonicOcean.cpp
//  Kinect_3DJ
//
//  Created by Samuel Ruberti on 7/30/12.
//
//

#include "SonicOcean.h"

CSonicOcean::CSonicOcean()
{
    //Set up fft Stuff
    setUpfft( 8192 );

    //Set up Mesh
    setUpMesh();

	setRows();

    m_mesh.setMode(OF_PRIMITIVE_TRIANGLE_STRIP);
}

CSonicOcean::~CSonicOcean()
{
    if(m_fftSmoothed) delete m_fftSmoothed;
}

void CSonicOcean::soundUpdate()
{
    ofSoundUpdate();

    float * val = ofSoundGetSpectrum(m_nBandsToGet);
    for (int i = 0; i<m_nBandsToGet; i++) {
        //let the smoothed value sink to zero
        m_fftSmoothed[i] *= 0.96f; //Creates an animated drop back to zero
        if (m_fftSmoothed[i] < val[i]) {m_fftSmoothed[i] = val[i];}
    }
}

void CSonicOcean::drawEQSonicOcean()
{
    ofPushMatrix();
    ofEnableAlphaBlending();
    ofSetLineWidth(1.0f);
    
    for(int r = 0; r < m_rows*3; r++){
        for (int c = 0; c < m_cols-3; c++) {
            //Change the vertexes based on fft results
            int index = c * r + c;
            alterVertexes(index, r);
        }
    }

    m_mesh.drawFaces();

    m_mesh.disableColors(); //wireframe
    ofSetColor(0);
    m_mesh.drawWireframe();
    m_mesh.enableColors();

    ofPopMatrix();

}

void CSonicOcean::setEvenRows( const int r, const int c )
{
    //color
    ofColor color;
    //color.setHsb(20+ 25 * sin(r*c), 255, 255, 127);
    color.set(ofRandom(80,120), 255,ofRandom(80,120), 127);

    //point2
    ofVec3f p2(r*m_step,  0.0f, c*m_step);
    p2.x = p2.x - (m_rows/2)*m_step + m_step;
    m_mesh.addVertex(p2);
    m_mesh.addColor(color);

    p2.x = p2.x - (m_rows/2)*m_step + m_step;

    //point3
    ofVec3f p3(r*m_step - m_step, 0.0f, c*m_step + m_step);
    p3.x = p3.x - (m_rows/2)*m_step + m_step;
    m_mesh.addVertex(p3);
    m_mesh.addColor(color);
}

void CSonicOcean::setOddRows( const int r, const int c )
{
    //color
    ofColor color;
    //color.setHsb(20+ 25 * sin(r*c), 255, 255, 127);
    color.set(ofRandom(80,120), 255, ofRandom(80,120), 127);

    //point2
    ofVec3f p2(r*m_step, 0.0f, (m_cols-c)*m_step);
    p2.x = p2.x - (m_rows/2)*m_step + m_step;
    m_mesh.addVertex(p2);
    m_mesh.addColor(color);

    //point3
    ofVec3f p3(r*m_step - m_step, 0.0f, (m_cols-c)*m_step - m_step);
    p3.x = p3.x - (m_rows/2)*m_step + m_step;
    m_mesh.addVertex(p3);
    m_mesh.addColor(color);
}

void CSonicOcean::setUpMesh()
{
    m_rows = 128;
    m_cols = 30;
    m_step = 80;
    m_mesh.addVertex(ofPoint( - (m_rows/2)*m_step + m_step,0,0));
    m_mesh.addColor(ofColor(ofRandom(80,120),255,ofRandom(80,120), 127));

    m_nBandsToGet = m_rows*2.5; // for FFT
    m_heightThresh = 1200;
}

void CSonicOcean::setUpfft( const unsigned int n)
{
    m_fftSmoothed = new float[n];
    for (int i = 0; i < n; i++) {
        m_fftSmoothed[i] = 0;
    }
}

void CSonicOcean::alterVertexes( const int index, const int r )
{
    ofVec3f tempVec = m_mesh.getVertex(index + 1);
    tempVec.y = m_fftSmoothed[r]*2000;
    if(tempVec.y> m_heightThresh){ tempVec.y = m_heightThresh;}
    m_mesh.setVertex(index + 1, tempVec);

    ofVec3f tempVec2 = m_mesh.getVertex(index+2);
    tempVec2.y = m_fftSmoothed[r]*2000;
    if(tempVec2.y > m_heightThresh){ tempVec2.y = m_heightThresh;}
    m_mesh.setVertex((index + 2), tempVec2);
}

void CSonicOcean::setRows()
{
	for(int r = 0; r < m_rows; ++r){
		for (int c = 0; c < m_cols; ++c){
			if ((r&1)==0) { //even rows
				// set the even rows color and vertex
				setEvenRows(r, c);
			} else { //odd rows
				// set the odd rows color and vertex
				setOddRows(r, c);
			}
		}
	}
}
