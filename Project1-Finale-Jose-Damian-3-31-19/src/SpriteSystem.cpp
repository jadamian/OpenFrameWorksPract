#include "SpriteSystem.h"



SpriteSystem::SpriteSystem(){
	grav.set(0,10,0);
}


SpriteSystem::~SpriteSystem()
{
}

void SpriteSystem::move(){
	for (int i = 0; i < sprites.size(); i++) {
		sprites[i].position = sprites[i].velocity + sprites[i].position;
		sprites[i].velocity = sprites[i].velocity + sprites[i].force + grav;
		sprites[i].birthtime += 1;
	}

	for (int i = 0; i < deathsprite.size(); i++) {
		deathsprite[i].position = deathsprite[i].velocity + deathsprite[i].position;
		deathsprite[i].velocity = deathsprite[i].velocity + deathsprite[i].force + grav;
		deathsprite[i].birthtime += 1;
	}

}

void SpriteSystem::update(){
	for (int i = 0; i < sprites.size(); i++) {
		if (sprites[i].birthtime > sprites[i].lifespan || !sprites[i].alive) {
			sprites.erase(sprites.begin() + i);
		}
	}
	for (int i = 0; i < deathsprite.size(); i++) {
		if (deathsprite[i].birthtime > deathsprite[i].lifespan ) {
			deathsprite.erase(deathsprite.begin() + i);
		}
	}
	move();

}

void SpriteSystem::addDeath(Sprite s){
	deathsprite.push_back(s);
}

void SpriteSystem::add(Sprite s){
	sprites.push_back(s);
}


void SpriteSystem::draw(){
	for (int i = 0; i < sprites.size(); i++) {
		sprites[i].draw();
	}
	for (int i = 0; i < deathsprite.size(); i++) {
		deathsprite[i].draw();
	}
}




