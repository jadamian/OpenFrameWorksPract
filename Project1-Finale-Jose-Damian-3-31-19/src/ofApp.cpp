#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	
	time = 0;
	level = 1;
	spacehit = 0;
	score = 0;
	background.load("images/bg.png");
}

//--------------------------------------------------------------
void ofApp::update() {
	if(start){
	emit.update();
	checkCollision();
	enemit.update();

	spacehit += 1;
	if (spacehit == emitrate & emit.cover.alive) {
		allow = true;
		spacehit = 0;
	}
	
	time += 1;
	if (time == rate & enemit.cover.alive) {
		fish.position = enemit.cover.position;
		enemit.emitsys.add(fish);
		time = 0;
	}
	enem();
	//levelOver();
	}

	if (emit.cover.position.y > 800) {
		levelOver();
		level = 1;
		start = false;
	}

	if (enemit.cover.position.y > 1000) {
		levelOver();
		
		start = false;
	}
}

//--------------------------------------------------------------
void ofApp::draw(){
	background.draw(-1,-1);
	if (start) {
		emit.draw();
		enemit.draw();
		ofDrawBitmapString(score, 700,50);
	}
	if (!start) {

		if (missionOver) {
			ofDrawBitmapString("Level Done", 700, 350);
			ofDrawBitmapString("Score:", 700, 375);
			ofDrawBitmapString(score, 750, 375);
			if (level == 1)
				ofDrawBitmapString("Game Over, Press Space for New Game", 700, 300);
		}

		if (!emit.cover.alive) {
			
			ofDrawBitmapString(gameStop,700,325);
			ofDrawBitmapString(score, 700, 350);
		}
		ofDrawBitmapString(gameStart, 700, 400);
		
	}
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	switch (key) {
	case OF_KEY_RIGHT:
		emit.cover.velocity.x = 1;
		break;
	case OF_KEY_LEFT:
		emit.cover.velocity.x = -1;
		break;
	case OF_KEY_UP:
		emit.cover.velocity.y = -1;
		break;
	case OF_KEY_DOWN:
		emit.cover.velocity.y = 1;
		break;
	case 'a':
		start = false;
		break;
	case ' ':
		if (start & allow) {
			allow = false;
			emit.shot.play();
			fire.force.set(0,-9.99,0);
			fire.position = emit.cover.position + ofVec3f(50, 50, 0);
			fire.velocity.set(5, 0, 0);
			fire.lifespan = 200;
			emit.emitsys.add(fire);
		}
		//start = true;
		if (!start) {
			newLevel(level);
			bgsong.load("sounds/bgmusic.mp3");
			bgsong.play();
			level++;
			if (level == 4) {
				level = 1;
			}
		}
			
		break;
	}
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
	switch (key) {
	case OF_KEY_RIGHT:
		emit.cover.velocity.x = 0;
		break;
	case OF_KEY_LEFT:
		emit.cover.velocity.x = 0;
		break;
	case OF_KEY_UP:
		emit.cover.velocity.y = 0;
		break;
	case OF_KEY_DOWN:
		emit.cover.velocity.y = 0;
		break;
	}
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

void ofApp::enem() {
	if (enemit.cover.alive) {
	if (enemit.cover.position.y > 500) {
		enemit.cover.velocity = -enemit.cover.velocity;
	}
	if (enemit.cover.position.y < 100) {
		enemit.cover.velocity = -enemit.cover.velocity;
	}
	}
}

void ofApp::newLevel(int lev){
	Sprite rin;
	rin.position = glm::vec3(100, 100, 0);
	rin.setImg("images/rinchan1.png");
	emit.cover = rin;
	fire.setImg("images/fire1.png");
	fire.velocity = ofVec3f(5, 0, 0);
	fire.lifespan = 200;
	fire.alive = true;
	emit.emitsys = sys;
	Sprite fishman;
	fishman.setImg("images/aquaman.png");
	fishman.position.set(1000, 300, 0);
	fishman.velocity.set(0, 4* lev, 0);
	fishman.alive = true;
	
	enemit.cover = fishman;
	fish.setImg("images/fish.png");
	fish.velocity.set(-lev, 0, 0);
	fish.alive = true;
	fish.lifespan = 800;
	emit.emitsys.sprites.clear();
	enemit.emitsys.sprites.clear();
	switch (lev) {
	case 1:
		score = 0;
		rate = 100;
		emitrate = 10;
		enemit.cover.health = 10;
		break;
	case 2:
		rate = 50;
		emitrate = 50;
		enemit.cover.health = 20;
		break;
	case 3:
		rate = 25;
		emitrate = 50;
		enemit.cover.health = 50;
		break;
	}
	time = 0;
	spacehit = 0;
	start = true;
}

void ofApp::checkCollision(){
	float dist;
	ofVec3f pos;
	ofVec3f enempos;
	for (int i = 0; i < emit.emitsys.sprites.size(); i++) {
		pos = emit.emitsys.sprites[i].getCentre();
		dist = ((pos.x - enemit.cover.getCentre().x) * (pos.x - enemit.cover.getCentre().x))
			+ ((pos.y - enemit.cover.getCentre().y) * (pos.y - enemit.cover.getCentre().y));
		if (dist < ((emit.emitsys.sprites[i].getRad() + enemit.cover.getRad()) * (emit.emitsys.sprites[i].getRad() + enemit.cover.getRad()))) {
			if (emit.emitsys.sprites[i].alive = true)
				enemit.cover.health = enemit.cover.health - 10;
			emit.emitsys.sprites[i].alive = false;
			cout << enemit.cover.health << endl;
			if (enemit.cover.health <= 0 ) {
				score += 500;
				enemit.cover.alive = false;
				enemit.deadCover();
				bgsong.stop();
			}
			down();
		}
		for (int j = 0; j < enemit.emitsys.sprites.size(); j++) {
			enempos = enemit.emitsys.sprites[j].getCentre();
			dist = ((pos.x - enempos.x) * (pos.x - enempos.x))
				+ ((pos.y - enempos.y) * (pos.y - enempos.y));
			if (dist < ((emit.emitsys.sprites[i].getRad() + enemit.emitsys.sprites[j].getRad()) * (emit.emitsys.sprites[i].getRad() + enemit.emitsys.sprites[j].getRad()))) {
				emit.emitsys.sprites[i].position.set(0,800,0);
				enemit.emitsys.sprites[j].velocity.set(0,5,0);
				enemit.emitsys.sprites[j].lifespan = 800;
				score += 25;
			}
		}
	}

	pos = emit.cover.getCentre();
	for (int i = 0; i < enemit.emitsys.sprites.size(); i++) {
		enempos = enemit.emitsys.sprites[i].getCentre();
		dist = ((pos.x - enempos.x) * (pos.x - enempos.x))
			+ ((pos.y - enempos.y) * (pos.y - enempos.y));
		if (dist < ((enemit.emitsys.sprites[i].getRad() + emit.cover.getRad()) * (enemit.emitsys.sprites[i].getRad() + emit.cover.getRad()))) {
			emit.cover.velocity.set(0,20,0);
			emit.cover.force.set(0,-9.75,0);
			emit.cover.alive = false;
			score = 0;
			bgsong.stop();
		}
	}
	
}



void ofApp::down(){
	fire.position = enemit.cover.getCentre();
	fire.force.set(0,-9,0);
	fire.lifespan = 30;
	fire.velocity.set(5,5,0);
	enemit.emitsys.addDeath(fire);
	fire.velocity.set(5, -5, 0);
	enemit.emitsys.addDeath(fire);
	fire.velocity.set(-5, 5, 0);
	enemit.emitsys.addDeath(fire);
	fire.velocity.set(-5, -5, 0);
	enemit.emitsys.addDeath(fire);

}

void ofApp::levelOver(){
	if (!emit.cover.alive) {
		cout << "you died" << endl;
		gameOver = true;
	}
	if (!enemit.cover.alive) {
		cout << "mission complete" << endl;
		missionOver = true;
		
	}
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
