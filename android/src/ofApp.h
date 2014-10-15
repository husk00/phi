#pragma once

#include "ofMain.h"
#include "ofxAndroid.h"
#include "myPattern.h"
#include "ofStep.h"
#include "ofButton.h"


class ofApp : public ofxAndroidApp {
	
public:
	void setup();
	void update();
	void draw();

	void keyPressed(int key);
	void keyReleased(int key);
	void windowResized(int w, int h);

	void touchDown(int x, int y, int id);
	void touchMoved(int x, int y, int id);
	void touchUp(int x, int y, int id);
	void touchDoubleTap(int x, int y, int id);
	void touchCancelled(int x, int y, int id);
	void swipe(ofxAndroidSwipeDir swipeDir, int id);

	void pause();
	void stop();
	void resume();
	void reloadTextures();

	bool backPressed();
	void okPressed();
	void cancelPressed();
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
    bool pausa, nextStep,enviado, fxState[32], rightBover, leftBover, fadeUp, fadeDown, stepOver[8];
	int counter,page, currentPage, cc,movingPattern, whichPattern, whichStep, activeStep, lastRandomStep;
    unsigned long last;
    ofxOscSender M8sender;
    ofxOscSender liveSender;

private:
	myPattern** pattern;
	ofStep** myStep;
	ofButton** myButton;



};
