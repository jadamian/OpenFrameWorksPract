#include "Emitter.h"



Emitter::Emitter() {
	shot.load("sounds/fireball.mp3");
}


Emitter::~Emitter()
{
}

void Emitter::draw(){
	cover.draw();
	emitsys.draw();
}

void Emitter::deadCover(){
	if (!cover.alive) {
		cover.force.set(0,-9.50,0);
	}
}
