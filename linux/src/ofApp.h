#pragma once

#include "ofMain.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    

    ofPolyline slice[32], step[8];
    ofPath path[32], stepPath[8];
    ofPoint center;
    ofColor sliceColor;
    ofColor fxColor[4];
    ofImage banner, colsx, coldx, fondocentral, letra;
    float elapsedTime;
    bool nextStep, fxState[32];
	  int counter;	
};
