#pragma once
#include "ofMain.h"
#include "Sprite.h"
#include "SpriteSystem.h"
class Emitter : public ofBaseApp{
public:
	Emitter();
	~Emitter();
	SpriteSystem emitsys;
	Sprite cover;
	ofSoundPlayer shot;
	void update() {
		cover.position = cover.position + cover.velocity;
		cover.velocity = cover.velocity + cover.force + emitsys.grav;
		emitsys.update();
	}
	void draw();
	void deadCover();
};

