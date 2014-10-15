#include "myPattern.h"

myPattern::myPattern(int _id)
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
    this->startPos.set(870,100);
    this->l = id % 8;
    this->f = 0;
    if(l==0) l=8;
    if(id > 8 && id < 17) f = 40;
    if(id > 16 && id < 25) f = 80;
    if(id > 24 && id < 33) f = 120;
    this->pos.set(startPos.x+f,startPos.y+(l*40));
    this->radius = 15;
    this->onStep = 0;
    this->occupied = false;

}


void myPattern::update(){
      if(this->isSelected){
        this->pos.set(ofGetMouseX(),ofGetMouseY());  
        }
    }


void myPattern::draw(){
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

void myPattern::_mouseMoved(int x, int y){
    if(x > this->pos.x - (this->radius) && x < (this->pos.x+radius) && y > this->pos.y - (radius) && y < this->pos.y+(radius) ){
        this->isOver = true;
    } else{
        this->isOver = false;
    }
}
void myPattern::_mousePressed(int x, int y, int button){
    if(this->isOver){
        this->isSelected =true;
    }

}
void myPattern::_mouseReleased(int x, int y, int button){
    if(this->isOver){
        this->isSelected =false;
    }

        
}

void myPattern::_mouseDragged(int x, int y, int button){

}

void myPattern::_keyPressed(int key){
}

