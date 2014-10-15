#include "myPatternDyn.h"

myPatternDyn::myPatternDyn(int _id)
{
//init var
    this->isOver = false;
    this->isSelected = false;
    this->isDragging = false;
    this->id = _id;
    this->page = 0;
    this->font.loadFont("fonts/Inconsolata.otf", 15, true,false,false,0.3,90);
    this->color.r = 200;
    this->color.g = 200;
    this->color.b = 200;
    this->color.a = 80;
    this->l = id % 8;
    this->f = 0;
    pos.set(ofGetMouseX(),ofGetMouseY());
    if(l==0) l=8;
    if(id > 8 && id < 17) f = 72;
    if(id > 16 && id < 25) f = 144;
    if(id > 24 && id < 33) f = 216;
    this->radius = 35;
    this->onStep = 0;
    this->destroy = false;

}


void myPatternDyn::update(){

		if(isSelected) this->pos.set(ofGetMouseX(),ofGetMouseY());

    }


void myPatternDyn::draw(){
    ofSetCircleResolution(250); 
    ofSetColor(255,255,255,255);
    ofNoFill();
    ofCircle(pos.x,pos.y,radius);
    ofSetColor(color);
    ofFill();
    ofCircle(pos.x,pos.y,radius);
    ofSetColor(255,255,255);
    ofRectangle rect = font.getStringBoundingBox(ofToString(id),pos.x-15, pos.y+8);
    font.drawString(ofToString(id), pos.x-(rect.width/2),pos.y+8);
}

void myPatternDyn::_touchMoved(int x, int y){


}
void myPatternDyn::_touchDown(int x, int y, int button){

    if(x > this->pos.x - (this->radius) && x < (this->pos.x+radius) && y > this->pos.y - (radius) && y < this->pos.y+(radius) ){
    	this->isOver = true;
        ofLog() << " io sono Over " << isOver;
    } else{
        this->isOver = false;
        ofLog() << "fuori";
    }
    if(this->isOver){
        this->isSelected =true;
    }


}
void myPatternDyn::_touchUp(int x, int y, int button){
    if(this->isOver){
        this->isSelected =false;
    }

        
}



