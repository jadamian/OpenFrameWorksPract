#pragma once
#include "ofMain.h"
class Sprite : public ofBaseApp{
public:
	Sprite();
	~Sprite();
	ofImage img;
	float health;
	ofVec3f position;
	ofVec3f getCentre();
	float getRad();
	void draw();
	float age();
	float birthtime;
	float lifespan;
	bool alive;
	ofVec3f velocity;
	ofVec3f force;
	void setlifespan(float ls);
	void setImg(string dir);
	ofVec3f bounds;
	void setBounds(float x, float y);
};

