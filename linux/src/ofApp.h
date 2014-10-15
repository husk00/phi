#pragma once

#include "ofMain.h"
#include "myPattern.h"
#include "ofStep.h"
#include "ofButton.h"


//#define LIVEHOST "192.168.0.123"

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
		void sendFX(int effect[4]);
		void reset();
		void random();
		void sendStatus();
    

    ofPolyline slice[32], step[8];
    ofPath path[32], stepPath[8];
    ofPoint center;
    ofColor sliceColor;
    ofColor fxColor[4];
    ofImage banner, colsx, coldx, fondocentral, letra;
    ofTrueTypeFont font;
    float elapsedTime;
    bool pause, nextStep,enviado, fxState[32], rightBover, leftBover, fadeUp, fadeDown, stepOver[8];
	  int counter,page, currentPage, cc,movingPattern, whichPattern, whichStep, activeStep, lastRandomStep;	
    unsigned long last; 
    ofxOscSender M8sender;
    ofxOscSender liveSender;
  
    private:
    myPattern** pattern;
    ofStep** myStep;
    ofButton** myButton;

};
