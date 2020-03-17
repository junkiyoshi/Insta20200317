#pragma once
#include "ofMain.h"
#include "ofxBox2d.h"

class dCharacter {

public:

	dCharacter() {};
	void update(vector<string>& words);

	shared_ptr<ofxBox2dRect> rect;
	int index = 0;
};

class ofApp : public ofBaseApp {

public:
	void setup();
	void update();
	void draw();

	void keyPressed(int key) {};
	void keyReleased(int key) {};
	void mouseMoved(int x, int y) {};
	void mouseDragged(int x, int y, int button) {};
	void mousePressed(int x, int y, int button) {};
	void mouseReleased(int x, int y, int button) {};
	void windowResized(int w, int h) {};
	void dragEvent(ofDragInfo dragInfo) {};
	void gotMessage(ofMessage msg) {};

	int font_size;
	ofTrueTypeFont font;
	vector<string> words;

	ofxBox2d box2d;
	vector<dCharacter> drop_char_list;
};