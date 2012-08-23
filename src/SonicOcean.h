//
//  CSonicOcean.h
//  Kinect_3DJ
//
//  Created by Samuel Ruberti on 7/30/12.
//
//

#ifndef Kinect_3DJ_SonicOcean_h
#define Kinect_3DJ_SonicOcean_h
#include "ofMain.h"

class CSonicOcean : public ofBaseApp
{
public:

    CSonicOcean();

    ~CSonicOcean();

    void drawEQSonicOcean();

    void soundUpdate();

private:

    void setUpfft( const unsigned int n );

    void setUpMesh();

	void setRows();

    void setOddRows ( const int r, const int c );

    void setEvenRows ( const int r, const int c );

    void alterVertexes( const int index, const int r );

    float * m_fftSmoothed;
    int m_nBandsToGet;

    ofMesh m_mesh;
    int m_rows;
    int m_cols;
    int m_step;

    float m_heightThresh;

};

#endif
