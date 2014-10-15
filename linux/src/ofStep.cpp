#include "ofStep.h"

ofStep::ofStep(int _id,ofPoint _center)
{
//init var
    id = _id;
    over = false;
    active = false;
    hasPattern = false;
    send = false;
    center = _center;
    numPattern = 0;

    //OSC
    // open an outgoing connection to HOST:PORT
    M8sender.setup(M8HOST, M8PORT);
    liveSender.setup(LIVEHOST, LIVEPORT);
	  // crear los steps
	  step.lineTo(center);
	  step.arc(center,175,175,(id*45),(id*45)+45, 100);

	  //convertir slices en ofPath para que se puedan llenar
	    for( int i = 0; i < step.getVertices().size(); i++) {
	        if(i == 0) {
	            stepPath.newSubPath();
	            stepPath.moveTo(step.getVertices()[i] );
	        } else {
	            stepPath.lineTo( step.getVertices()[i] );
	        }
	    }
	      stepPath.close();
	      stepPath.simplify();

}


void ofStep::update(int counter){
    if(counter == id){
          active = true;
        } else {
          active=false;
          send = false;
    };
    if(active && hasPattern && !send){
            sendToM8();
            sendToLive();
            send = true;
            }
}


void ofStep::draw(){
	//steps seqencer circle
	  for(int j = 0; j < 8; j++){
        if(active) {
	      sliceColor.r=250;
	      sliceColor.g=10;
	      sliceColor.b=10;
	      stepPath.setStrokeWidth(2);
	      stepPath.setColor(sliceColor);
	      stepPath.setStrokeColor(ofColor::white);
        
        } 
        
        if(!active) {
	      sliceColor.r=10;
	      sliceColor.g=10;
	      sliceColor.b=10;
	      stepPath.setStrokeWidth(2);
	      stepPath.setColor(sliceColor);
	      stepPath.setStrokeColor(ofColor::white);
	      }
        if(over && !hasPattern) {
	      sliceColor.r=10;
	      sliceColor.g=250;
	      sliceColor.b=10;
	      stepPath.setStrokeWidth(2);
	      stepPath.setColor(sliceColor);
	      stepPath.setStrokeColor(ofColor::white);
	      }
	      stepPath.draw();
    }
}

void ofStep::_mouseMoved(int x, int y){
}

bool ofStep::inside(int x, int y){
      return step.inside(x,y);
}
void ofStep::insideOver(int x, int y){
  if(step.inside(x,y)){
      over = true;
    } else {
      over = false;
    }
}
void ofStep::getCenter(){
     myCenter.x = step.getCentroid2D().x;
     myCenter.y = step.getCentroid2D().y;
    
}
void ofStep::sendToM8(){
          ofLog() <<  "step id " << id <<  " enviado pattern " << numPattern;
          int val = numPattern;
          if(val == 0) val =33;
          ofxOscMessage videoM8;
          videoM8.setAddress("/md8key/ctrl_layer_media/0/");
          videoM8.addIntArg(val);
          M8sender.sendMessage(videoM8);
}

void ofStep::sendToLive(){
          int val = numPattern;
          int track = 1;
          if(val == 0) val =33;
          /*if(val < 8 ) track = 1;
          if(val > 8 && val < 17) track = 2;
          if(val > 16 && val < 25) track = 3;
          if(val > 24 && val < 33) track = 4;
          int l = val % 8;
          if(l==0) l=8;*/
          ofxOscMessage live;
          live.setAddress("/live/play/clip");
          //live.setAddress("/play");
          live.addIntArg(track);
          live.addIntArg(val);
          liveSender.sendMessage(live);
}
void ofStep::_mousePressed(int x, int y, int button){

}
void ofStep::_mouseReleased(int x, int y, int button ){
}

void ofStep::_mouseDragged(int x, int y, int button){
}

