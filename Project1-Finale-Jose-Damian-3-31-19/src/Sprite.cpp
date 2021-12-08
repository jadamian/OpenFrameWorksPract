#include "Sprite.h"



Sprite::Sprite(){
	lifespan = -1;
	velocity = ofVec3f(0,0,0);
	force = ofVec3f(0,-10,0);
	alive = true;
}


Sprite::~Sprite()
{
}

ofVec3f Sprite::getCentre(){
	return ofVec3f(position.x + (img.getWidth()/2), position.y + (img.getHeight()/ 2), 0);
}

float Sprite::getRad(){
	return (img.getWidth() / 2);
}

void Sprite::draw(){
	img.draw(position);
}

float Sprite::age(){
	return (ofGetElapsedTimeMillis() - birthtime);
}

void Sprite::setlifespan(float ls){
	lifespan = ls;
}

void Sprite::setImg(string dir){
	img.load(dir);
}

void Sprite::setBounds(float x,float y){
	bounds.set(x,y,0);
}
