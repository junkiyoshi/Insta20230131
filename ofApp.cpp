#include "ofApp.h"	

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(30);
	ofSetWindowTitle("openFrameworks");

	ofBackground(0);
	ofEnableBlendMode(ofBlendMode::OF_BLENDMODE_ADD);

	this->font.loadFont("fonts/Kazesawa-Bold.ttf", 25, true, true, true);
	this->word = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

	vector<glm::vec2> location_list;
	ofColor color;
	for (int x = -300 - 15; x <= 300 - 15; x += 30) {

		for (int y = -300 + 15; y <= 300 + 15; y += 30) {
			
			this->location_list.push_back(glm::vec2(x + 15, y - 15));
			color.setHsb(ofRandom(255), 100, 255);
			this->color_list.push_back(color);
			this->index_list.push_back(ofRandom(this->word.size()));
			this->flag_list.push_back(false);
		}
	}
}

//--------------------------------------------------------------
void ofApp::update() {

	ofColor color;
	for (int i = 0; i < this->location_list.size(); i++) {

		auto y = ofMap(ofNoise(this->location_list[i].x * 0.003 + ofGetFrameNum() * 0.02), 0, 1, -460, 460);
		this->flag_list[i] = false;

		if (abs(this->location_list[i].y - y) < 60) {

			color.setHsb(ofRandom(255), 100, 255);
			this->color_list[i] = color;
			this->index_list[i] = (ofRandom(this->word.size()));
			this->flag_list[i] = true;
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	ofTranslate(ofGetWindowSize() * 0.5);

	for (int i = 0; i < this->location_list.size(); i++) {

		ofPushMatrix();
		ofTranslate(this->location_list[i]);

		ofPath chara_path = this->font.getCharacterAsPoints(this->word[this->index_list[i]], true, false);
		vector<ofPolyline> outline = chara_path.getOutline();

		if (flag_list[i]) {

			ofFill();
			ofSetColor(this->color_list[i], 200);
			ofBeginShape();
			for (int outline_index = 0; outline_index < outline.size(); outline_index++) {

				ofNextContour(true);

				auto vertices = outline[outline_index].getVertices();
				for (auto& vertex : vertices) {

					ofVertex(vertex + glm::vec2(-8, 15));
				}
			}
			ofEndShape(true);
		}

		ofNoFill();
		ofSetColor(this->color_list[i]);
		ofBeginShape();
		for (int outline_index = 0; outline_index < outline.size(); outline_index++) {

			ofNextContour(true);

			auto vertices = outline[outline_index].getVertices();
			for (auto& vertex : vertices) {

				ofVertex(vertex + glm::vec2(-8, 15));
			}
		}
		ofEndShape(true);

		ofPopMatrix();
	}
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}