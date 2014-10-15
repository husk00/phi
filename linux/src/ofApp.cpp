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
    
    //OSC
    // open an outgoing connection to HOST:PORT
    M8sender.setup(M8HOST, M8PORT);
    liveSender.setup(LIVEHOST, LIVEPORT);

    //timing
    elapsedTime = ofGetElapsedTimeMillis(); 
    last = ofGetElapsedTimeMillis();  
    activeStep = 33;

    //paging
    page = 1;
    currentPage = 1;
    font.loadFont("fonts/Inconsolata.otf", 15, true,false,false,0.3,90);
    rightBover = false;
    leftBover = false;
    fadeUp = false;
    fadeDown = false;
    cc = 80;
    pause = false;
    
    //stepping
    counter = 5;
    nextStep = false; 
    //step state inizialization
	  for(int i=0; i<8; i++){
      stepOver[i] = false;
    }

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
	  
    //inizialize steps
    myStep = new ofStep*[8];
        for(int j = 0; j < 8; j++){
           myStep[j] = new ofStep(j, center);
        }  
        
        //inizialize buttons
        myButton = new ofButton*[3];
        //reset
        ofPoint myPos(840, (ofGetHeight()-((ofGetHeight()/100)*38)));
        myButton[0] = new ofButton(0,myPos, "RESET", false );
        //random
        myPos.y += myButton[0]->form.height+10; 
        myButton[1] = new ofButton(1,myPos, "RANDOM", false );
        //masterplay
        ofPoint myPos2(45, (ofGetHeight()-((ofGetHeight()/100)*21)));
        myButton[2] = new ofButton(2,myPos2, "PLAY/STOP", false );
        
    /*
        myButton[1] = new ofButton(1,myPos, "RANDOM" );
      */ 
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

        //inizialize patterns
        pattern = new myPattern*[32];
        for(int j = 0; j < 32; j++){
           pattern[j] = new myPattern(j+1);
        }  

    }

    //--------------------------------------------------------------
    void ofApp::update(){
      //sequencing time
      if(!pause){
       if(ofGetElapsedTimeMillis() - elapsedTime > 3000.0) {
          nextStep = true;
          elapsedTime = ofGetElapsedTimeMillis();
          enviado = false;
          }  
    }
    /*
        //fading
        //UP
        if(fadeUp){
            if(ofGetElapsedTimeMillis() - last > 45)  
        {  
          for(int j = (page-1)*8; j < page*8; j++){
                  pattern[j]->color.a = cc % 256;
            }
            cc -=5;  
            last = ofGetElapsedTimeMillis();  
        }
        if(cc <= 0){
          cc = 80;
          fadeUp = false;
          page++;
           if(page >= 5) page =1;
          for(int j = (page-1)*8; j < page*8; j++){
                  if(!pattern[j]->onStep)pattern[j]->color.a = cc;
            }
          }
        }
        if(fadeDown){
            if(ofGetElapsedTimeMillis() - last > 45)  
    {  
	    for(int j = (page-1)*8; j < page*8; j++){
              if(!pattern[j]->onStep)pattern[j]->color.a = cc % 256;
        }
        cc -=5;  
        last = ofGetElapsedTimeMillis();  
    }
    if(cc <= 0){
      cc = 80;
      fadeDown = false;
      page--;
       if(page <= 0) page =4;
	    for(int j = (page-1)*8; j < page*8; j++){
              if(pattern[j]->onStep) pattern[j]->color.a = cc;
        }
      }
    }
    */
  //active step 
  for(int i=0;i < 8; i++){
      if(myStep[i]->inside(ofGetMouseX(), ofGetMouseY())){ 
      whichStep =  i;
      }
    }

  //activeStep
  for(int i=0;i <8; i++){
      if(myStep[i]->active) activeStep = myStep[i]->id;
  }
  // send fx 
  int fxCollection[4];
  for(int i=0;i <4; i++){
    fxCollection[i] = fxState[(activeStep*4)+i];
    }
  sendFX(fxCollection); 
  
  //colorize active step
  if(nextStep == true){
      counter +=1;
      nextStep = false; 
      if(counter > 7){
        counter = 0;
      }
  }
	  for(int j = 0; j < 32; j++){
              pattern[j]->update();
              if(pattern[j]->isSelected) movingPattern = pattern[j]->id-1;
        }
  for(int i=0;i < 8; i++){
      myStep[i]->update(counter); 
    }
  //chacking buttons state 
  if(myButton[0]->action[0] == true){
      reset();
      myButton[0]->action[0] = false;
   }
    
  if(myButton[1]->action[1] == true){
      random();
      myButton[1]->action[1] = false;
   }
  if(myButton[2]->action[2] == true){
      sendStatus();
      myButton[2]->action[2] = false;
   }
        
}

//--------------------------------------------------------------
void ofApp::draw(){
		//banner
		banner.draw(30,0,1024, 68);
		//left column
		colsx.draw(30,90,230, 491);
		//right column
		coldx.draw(840,90,184, 410);
		//fondo central
		fondocentral.draw(270,90,566, 646);
    //paging buttons
    /*//right
    ofRectangle rightButton;
    rightButton.x = 990;
    rightButton.y = 95;
    rightButton.width = 20;
    rightButton.height = 20;
    if(rightBover){
    ofSetColor(200,210,210, 80);
    ofFill();
    } else {
    ofSetColor(200,210,210);
    ofFill();
    }
    ofRectRounded( rightButton, 10 );
    ofSetColor(0,0,0);
    font.drawString(">", 997,110);
    //left 
    ofRectangle leftButton;
    leftButton.x = 865;
    leftButton.y = 95;
    leftButton.width = 20;
    leftButton.height = 20;
    if(leftBover){
    ofSetColor(200,210,210, 80);
    ofFill();
    } else {
    ofSetColor(200,210,210);
    ofFill();
    }
    ofRectRounded( leftButton, 10 );
    ofSetColor(0,0,0);
    font.drawString("<", 870,110);
    */
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
        myStep[j]->draw();
    }

	//button e
	  for(int j = 0; j < 3; j++){
        myButton[j]->draw();
    }


   //myButton[0]->draw();
	//inside circle
	ofSetColor(0,0,0);
  ofFill();
	ofCircle(557,350,70);
	ofSetColor(255,255,255);
	ofNoFill();
	ofCircle(557,350,70);
	//letra 
	letra.draw(522,315,70, 70);
  
  //patterns
	 for(int j = 0; j < 32; j++){
              pattern[j]->draw();
    }

}
//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
    if(x > 990 && x < 1010 && y > 95 && y < 115){
        rightBover = true;
      } else {
        rightBover = false;
    }
    if(x > 865 && x < 885 && y > 95 && y < 115){
        leftBover = true;
      } else {
        leftBover = false;
    }
    //patterns
	  for(int j = 0; j < 32; j++){
              pattern[j]->_mouseMoved(x,y);
    }
}

void ofApp::reset(){
    for(int j = 0; j <32; j++){
      // reset pattern
      pattern[j]->pos.set(pattern[j]->startPos.x+pattern[j]->f,pattern[j]->startPos.y+(pattern[j]->l*40));
      pattern[j]->isDragging = false;
      pattern[j]->isOver = false;
      pattern[j]->isSelected = false;
      //reset fx
      fxState[j] = false;
    }
    for(int j = 0; j <8; j++){
      myStep[j]->hasPattern = false; 
      myStep[j]->over = false; 
     }

}
void ofApp::random(){
    reset();
    int randomStep = ofRandom(0,8); 
    for(int i=0; i<randomStep;i++){
                  int randomPattern = ofRandom(0,31); 
                  int randomLoopStep = ofRandom(0,8);  
                  if(!myStep[randomLoopStep]->hasPattern){
                  myStep[randomLoopStep]->getCenter();
                  pattern[randomPattern]->pos.set(myStep[randomLoopStep]->myCenter.x, myStep[randomLoopStep]->myCenter.y);
                  myStep[randomLoopStep]->hasPattern=true;
                  myStep[randomLoopStep]->numPattern=randomPattern+1;
                  pattern[randomLoopStep]->onStep = randomLoopStep;
                  pattern[randomLoopStep]->isSelected = false;
          }
     }
    //fx random
    for(int i=0; i<32;i++){
        int fxRandom = ofRandom(0,2); 
        fxState[i] = fxRandom;
    }
}
//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
  for(int i=0;i < 8; i++){
     myStep[i]->insideOver(x,y);
  }

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
/*
  //right page button
  if(rightBover){
     fadeUp = true; 
   }
  if(leftBover){
     fadeDown = true;
   }
*/
  for(int i = 0; i < 32; i++){
        //checking if over fx button
      
    int l = i % 8;
    if(l==0) l=8;
    //if(!myStep[l]->over){
      if(slice[i].inside(x,y)){
           fxState[i] = !fxState[i];
        }
     //   l++;
      //}
    }
    //patterns
	for(int j = 0; j < 32; j++){
              pattern[j]->_mousePressed(x,y, button);
    }
}


//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
        ofLog() << pattern[movingPattern]->isSelected;
           if(myStep[0]->inside(pattern[movingPattern]->pos.x, pattern[movingPattern]->pos.y) || myStep[1]->inside(pattern[movingPattern]->pos.x, pattern[movingPattern]->pos.y) || myStep[2]->inside(pattern[movingPattern]->pos.x, pattern[movingPattern]->pos.y)|| myStep[3]->inside(pattern[movingPattern]->pos.x, pattern[movingPattern]->pos.y) || myStep[4]->inside(pattern[movingPattern]->pos.x, pattern[movingPattern]->pos.y) || myStep[5]->inside(pattern[movingPattern]->pos.x, pattern[movingPattern]->pos.y) || myStep[6]->inside(pattern[movingPattern]->pos.x, pattern[movingPattern]->pos.y) || myStep[7]->inside(pattern[movingPattern]->pos.x, pattern[movingPattern]->pos.y)&& !myStep[whichStep]->hasPattern && pattern[movingPattern]->isSelected) { 
                  ofLog() << "dentro " << whichStep; 
                  myStep[whichStep]->getCenter();
                  pattern[movingPattern]->pos.set(myStep[whichStep]->myCenter.x, myStep[whichStep]->myCenter.y);
                  myStep[whichStep]->hasPattern=true;
                  myStep[whichStep]->numPattern=movingPattern+1;
                  pattern[movingPattern]->onStep = whichStep;
                  pattern[movingPattern]->isSelected = false;
                  } else{
                  ofLog() << "fuori "; 
                  pattern[movingPattern]->isSelected = false;
                  myStep[whichStep]->hasPattern=false;
                  myStep[whichStep]->numPattern=-1;
                  pattern[movingPattern]->onStep = -1;
                  pattern[movingPattern]->pos.set(pattern[movingPattern]->startPos.x+pattern[movingPattern]->f,pattern[movingPattern]->startPos.y+(pattern[movingPattern]->l*40));
                  }
    
  for(int i = 0; i <3; i++){
      myButton[i]->_mouseReleased(x,y, button);
    }
}

//--------------------------------------------------------------
void ofApp::sendFX(int effect[4]){
          ofxOscMessage live;
          ofxOscMessage autoColor;
          ofxOscMessage autoRotate;
          ofxOscMessage transformer;
          ofxOscMessage type;
          ofxOscMessage autoScale;
          live.setAddress("/live/fx");
          for(int i = 0; i < 4; i++){
            int val = effect[i];
            live.addIntArg(val);
          }
          liveSender.sendMessage(live);
          autoColor.setAddress("/md8key/ctrl_layer_auto_colorOn/0");
                 autoColor.addIntArg(effect[0]);
          autoRotate.setAddress("/md8key/ctrl_layer_auto_rotateOn/0");
                 autoRotate.addIntArg(effect[1]);
          type.setAddress("/md8key/ctrl_layer_traformer_type/0");
          transformer.setAddress("/md8key/ctrl_layer_transformer_on/0");
                 transformer.addIntArg(effect[2]);
          autoScale.setAddress("/md8key/ctrl_layer_auto_scaleOn/0");
                 autoScale.addIntArg(effect[3]);
          M8sender.sendMessage(autoColor);
          M8sender.sendMessage(autoRotate);
                 type.addIntArg(0);
          M8sender.sendMessage(type);
          M8sender.sendMessage(transformer);
          M8sender.sendMessage(autoScale);
    
}

void ofApp::sendStatus(){
      int val =0;
      float valfloat = 0.5;
      pause = !pause;
      ofxOscMessage pd;
      ofxOscMessage fxToM8;
      pd.setAddress("/live/play");
      fxToM8.setAddress("/md8key/ctrl_master_speed/0");
      if(pause){
      pd.addIntArg(val);
      fxToM8.addIntArg(val);
      }else {
      pd.addFloatArg(valfloat);
      fxToM8.addFloatArg(valfloat);
      
      }
      ofLog() << val;
      liveSender.sendMessage(pd);
          M8sender.sendMessage(fxToM8);


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

