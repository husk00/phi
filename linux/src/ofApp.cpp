#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	//ofSetOrientation(OF_ORIENTATION_90_RIGHT);
	  ofBackground(0,0,0);
    ofSetBackgroundAuto(true);
	  ofSetFrameRate(60);
    ofEnableSmoothing();  
    ofSetCircleResolution(48); 
	  ofPoint center((ofGetWidth()/2)+45,350);
    
    //timing
    elapsedTime = ofGetElapsedTimeMillis(); 
    
    //stepping
    counter = 6;
    nextStep = false; 

	  //load interface images
	  banner.loadImage("images/banner.jpg");
	  colsx.loadImage("images/colsx.jpg");
	  coldx.loadImage("images/coldx.jpg");
	  fondocentral.loadImage("images/fondocentral.jpg");
	  letra.loadImage("images/letra.jpg");

	  // crear las slices
	  for(int i=0; i<32; i++){
	  slice[i].lineTo(center);
	  slice[i].arc(center,275,275,(i*11.25),(i*11.25)+11.25, 100);
	  }
	  //color FX slice 
	  for(int i=0; i<4; i++){
      if(i == 0){
      fxColor[i].r=248;
	    fxColor[i].g=179;
	    fxColor[i].b=168;
      }
      if(i == 1){
      fxColor[i].r=184;
	    fxColor[i].g=220;
	    fxColor[i].b=159;
      }
      if(i == 2){
      fxColor[i].r=160;
	    fxColor[i].g=221;
	    fxColor[i].b=241;
      }
      if(i == 3){
      fxColor[i].r=202;
	    fxColor[i].g=170;
	    fxColor[i].b=207;
      }
    }

    //FX state inizialization
	  for(int i=0; i<32; i++){
        fxState[i] = false;   
    }
	  // crear los steps
	  for(int i=0; i<8; i++){
	  step[i].lineTo(center);
	  step[i].arc(center,175,175,(i*45),(i*45)+45, 100);
    }

	  //convertir slices en ofPath para que se puedan llenar
	  for(int j = 0; j < 8; j++){
	    for( int i = 0; i < step[j].getVertices().size(); i++) {
	        if(i == 0) {
	            stepPath[j].newSubPath();
	            stepPath[j].moveTo(step[j].getVertices()[i] );
	        } else {
	            stepPath[j].lineTo( step[j].getVertices()[i] );
	        }
	    }
	      stepPath[j].close();
	      stepPath[j].simplify();

	  }

	  //convertir steps en ofPath para que se puedan llenar
	  for(int j = 0; j < 32; j++){
	    for( int i = 0; i < slice[j].getVertices().size(); i++) {
	        if(i == 0) {
	            path[j].newSubPath();
	            path[j].moveTo(slice[j].getVertices()[i] );
	        } else {
	            path[j].lineTo( slice[j].getVertices()[i] );
	        }
	    }
	      path[j].close();
	      path[j].simplify();
      }
     
}

//--------------------------------------------------------------
void ofApp::update(){
   if(ofGetElapsedTimeMillis() - elapsedTime > 2000.0) {
      nextStep = true;
      elapsedTime = ofGetElapsedTimeMillis();
      }  
}

//--------------------------------------------------------------
void ofApp::draw(){
		//banner
		banner.draw(30,0,1024, 68);
		//left column
		colsx.draw(30,90,230, 491);
		//right column
		coldx.draw(840,90,184, 610);
		//fondo central
		fondocentral.draw(270,90,566, 546);

	//fx circle buttons
	  for(int i = 0; i < 32; i++){
	      path[i].setStrokeWidth(2);
        if(fxState[i]){
          if(i==0 || i == 4 || i == 8 ||i==12 || i == 16 ||i==20 || i == 24 ||i==28 || i == 32){
           path[i].setColor(fxColor[0]);
          }
          if(i==1 || i == 5 || i == 9 ||i==13 || i == 17 ||i==21 || i == 25 ||i==29){
           path[i].setColor(fxColor[1]);
          }
          if(i==2 || i == 6 || i == 10 ||i==14 || i == 18 ||i==22 || i == 26 ||i==30){
           path[i].setColor(fxColor[2]);
          }
          if(i==3 || i == 7 || i == 11 ||i==15 || i == 19 ||i==23 || i == 27 ||i==31){
           path[i].setColor(fxColor[3]);
          }
        }else{   
	        path[i].setColor(ofColor::black);
        }
	      path[i].setStrokeColor(ofColor::white);
	      path[i].draw();
	  }

	//steps seqencer circle
	  for(int j = 0; j < 8; j++){
        if(j == counter) {

	      sliceColor.r=250;;
	      sliceColor.g=10;;
	      sliceColor.b=10;;
	      stepPath[j].setStrokeWidth(2);
	      stepPath[j].setColor(sliceColor);
	      stepPath[j].setStrokeColor(ofColor::white);
        
        } else {
	      sliceColor.r=10;;
	      sliceColor.g=10;;
	      sliceColor.b=10;;
	      stepPath[j].setStrokeWidth(2);
	      stepPath[j].setColor(sliceColor);
	      stepPath[j].setStrokeColor(ofColor::white);
	      }
	      stepPath[j].draw();
    }
  //colorize active step
  if(nextStep == true){

      counter +=1;
      nextStep = false; 
      if(counter > 7){
        counter = 0;
      }
  }
  

	//inside circle
	ofSetColor(0,0,0);
  ofFill();
	ofCircle(557,350,70);
	ofSetColor(255,255,255);
	ofNoFill();
	ofCircle(557,350,70);
		//letra 
		letra.draw(522,315,70, 70);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
  for(int i = 0; i < 32; i++){
        //checking if over fx button
      if(slice[i].inside(x,y)){
           fxState[i] = !fxState[i];
        }
    }
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}

