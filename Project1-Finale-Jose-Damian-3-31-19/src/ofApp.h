#pragma once

#include "ofMain.h"
#include "SpriteSystem.h"
#include "Sprite.h"
#include "Emitter.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
		
		SpriteSystem sys;
		Emitter emit;
		Sprite fire;
		Sprite fish;
		Emitter enemit;
		float time;
		bool start = false;
		void enem();

		int level;

		bool gameOver = false;
		bool missionOver = false;

		float rate;

		float spacehit;
		float emitrate;
		bool allow;
		float score;
		void newLevel(int level);

		void checkCollision();
		void down();

		string gameStart = "Press Space To Start";
		string gameStop = "Game Over";
		string Levelmessage = "Level: ";
		ofSoundPlayer bgsong;
		ofImage background;

		void levelOver();
};
