#include "ofButton.h"

ofButton::ofButton(int _id,ofPoint _pos,string _text, bool _image)
{
//init var
    id = _id;
    pos = _pos;
    image = _image;
    if(image) background.loadImage("images/play.png"); 
    form.x = pos.x;
    form.y = pos.y;
    form.width = 180;
    form.height = 70;
    text = _text;
    fontSize = 15;
    font.loadFont("fonts/OratorStd.otf", fontSize, true,false,false,0.3,90);
    for(int i=0; i<3;i++){
    action[i] = false;
    }
}


void ofButton::update(){
}


void ofButton::draw(){
        if(inside(ofGetMouseX(), ofGetMouseY())) {
	      buttonColor.r=200;
	      buttonColor.g=200;
	      buttonColor.b=200;
	      buttonColor.a=10;
	      }else{
	      buttonColor.r=100;
	      buttonColor.g=100;
	      buttonColor.b=100;
	      buttonColor.a=220;
        }
        ofFill();
        ofSetColor(buttonColor);
	      ofRect(form);
        ofSetColor(ofColor::white);
        if(!image)font.drawString(text, form.x+form.width/2-fontSize*2,form.y+form.height/2+fontSize/2);
        if(image) {background.draw(form.x, form.y); ofLog() << id;}
}


bool ofButton::inside(int x, int y){
      return form.inside(x,y);
}

void ofButton::_mouseReleased(int x, int y, int button){
    for(int i=0; i<3;i++){
      if(inside(x,y)) action[i] = true;; 
    }
}

