#pragma once
#include "ofMain.h"
#include "Sprite.h"
class SpriteSystem : public ofBaseApp {
public:
	SpriteSystem();
	~SpriteSystem();
	ofVec3f grav;
	ofVec3f netForce;
	void move();
	void update();
	vector<Sprite> sprites;
	vector<Sprite> deathsprite;
	void addDeath(Sprite s);
	void add(Sprite s);
	void draw();
};

