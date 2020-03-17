#include "ofApp.h"

//--------------------------------------------------------------
void dCharacter::update(vector<string>& words) {

	if (ofGetFrameNum() % 5 && this->rect->getVelocity().length() > 1.5) {

		this->index = ofRandom(words.size());
	}
}

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openframeworks");

	ofBackground(0);

	this->font_size = 25;
	ofTrueTypeFontSettings font_settings("fonts/msgothic.ttc", this->font_size);
	font_settings.antialiased = true;
	font_settings.addRanges(ofAlphabet::Japanese);
	this->font.load(font_settings);

	this->words = {

		u8"!", u8"#", u8"$", u8"%", u8"&",
		u8"'", u8"(", u8")", u8"*", u8"+",
		u8",", u8"-", u8".", u8"/", u8"0",
		u8"1", u8"2", u8"3", u8"4", u8"5",
		u8"6", u8"7", u8"8", u8"9", u8"0",
		u8":", u8";", u8"<", u8"=", u8">",
		u8"?", u8"@",

		u8"A", u8"B", u8"C", u8"D", u8"E",
		u8"F", u8"G", u8"H", u8"I", u8"J",
		u8"K", u8"L", u8"M", u8"N", u8"O",
		u8"P", u8"Q", u8"R", u8"S", u8"T",
		u8"U", u8"V", u8"W", u8"X", u8"Y", u8"Z",

		u8"a", u8"b", u8"c", u8"d", u8"e",
		u8"f", u8"g", u8"h", u8"i", u8"j",
		u8"k", u8"l", u8"m", u8"n", u8"o",
		u8"p", u8"q", u8"r", u8"s", u8"t",
		u8"u", u8"v", u8"w", u8"x", u8"y", u8"z",

		u8"ｱ", u8"ｲ", u8"ｳ", u8"ｴ", u8"ｵ",
		u8"ｶ", u8"ｷ", u8"ｸ", u8"ｹ", u8"ｺ",
		u8"ｻ", u8"ｼ", u8"ｽ", u8"ｾ", u8"ｿ",
		u8"ﾀ", u8"ﾁ", u8"ﾂ", u8"ﾃ", u8"ﾄ",
		u8"ﾅ", u8"ﾆ", u8"ﾇ", u8"ﾈ", u8"ﾉ",
		u8"ﾊ", u8"ﾋ", u8"ﾌ", u8"ﾍ", u8"ﾎ",
		u8"ﾏ", u8"ﾐ", u8"ﾑ", u8"ﾒ", u8"ﾓ",
		u8"ﾔ", u8"ﾕ", u8"ﾖ",
		u8"ﾗ", u8"ﾘ", u8"ﾙ", u8"ﾚ", u8"ﾛ",
		u8"ﾜ", u8"ｦ", u8"ﾝ",
	};

	this->box2d.init();
	this->box2d.setGravity(0, 0);
	this->box2d.createBounds();
	this->box2d.setFPS(60);
	this->box2d.registerGrabbing();

	for (int i = 0; i < 135; i++) {

		auto rect = make_shared<ofxBox2dRect>();
		rect->setPhysics(1.0, 0.63, 0.1);
		rect->setup(this->box2d.getWorld(), ofRandom(ofGetWidth()), ofRandom(ofGetHeight()), this->font_size, this->font_size);

		auto drop_char = dCharacter();
		drop_char.rect = rect;
		drop_char.index = ofRandom(this->words.size());

		this->drop_char_list.push_back(drop_char);
	}
}

//--------------------------------------------------------------
void ofApp::update() {

	for (int i = 0; i < this->drop_char_list.size(); i++) {

		for (int k = i + 1; k < this->drop_char_list.size(); k++) {

			float distance = this->drop_char_list[i].rect->getPosition().distance(this->drop_char_list[k].rect->getPosition());
			if (distance < 30) {

				this->drop_char_list[i].rect->addForce(this->drop_char_list[i].rect->getPosition() - this->drop_char_list[k].rect->getPosition(), 2.5);
				this->drop_char_list[k].rect->addForce(this->drop_char_list[k].rect->getPosition() - this->drop_char_list[i].rect->getPosition(), 2.5);
			}
		}
	}

	for (auto& drop_char : this->drop_char_list) {

		drop_char.update(this->words);
	}

	this->box2d.update();
}

//--------------------------------------------------------------
void ofApp::draw() {

	for (auto& drop_char : this->drop_char_list) {

		ofPushMatrix();
		ofTranslate(drop_char.rect->getPosition().x, drop_char.rect->getPosition().y);
		ofRotate(drop_char.rect->getRotation());

		drop_char.rect->getVelocity().length() > 1.5 ? ofSetColor(239) : ofSetColor(89, 239, 89);
		this->font.drawString(this->words[drop_char.index], -10.5, 10);

		ofPopMatrix();
	}
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}