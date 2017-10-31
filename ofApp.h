#pragma once

#include "ofMain.h"
#include "ofxOpenCv.h"
#include "ofxCvHaarFinder.h"

class ofApp : public ofBaseApp {

public:
	void setup();
	void update();
	void draw();

	void keyPressed(int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y);
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void mouseEntered(int x, int y);
	void mouseExited(int x, int y);
	void windowResized(int w, int h);
	void dragEvent(ofDragInfo dragInfo);
	void gotMessage(ofMessage msg);
	void PlaySound(ofSoundPlayer sound);

	int camWidth, camHeight, eye;
	bool eyeClose;
	ofVideoGrabber vidGrabber;

	ofxCvHaarFinder finder;

	ofxCvColorImage rgb, hsb;
	ofxCvGrayscaleImage hue, sat, bri, filter1, filter2, finalImage;
	ofSoundPlayer mehNoise;
	ofSoundPlayer happyNoise;
	ofSoundPlayer angryNoise;
	ofSoundPlayer staticNoise;
	ofSoundPlayer discontentNoise; 
	ofImage meh;
	ofImage happy;
	ofImage discontent;
	ofImage anger; 
	ofImage confuse;
	ofImage blank;
	ofImage expression;
	ofColor backgroundColor;
	ofxCvContourFinder   contours;
	int findHue, findSat;
	int biggestFaceWidth;
	ofRectangle biggestFace; 
	float MehStartTime; 
	string previousEmotion;
	string currentEmotion;
	float angryStartTime;
	float shutdownStartTime;
	bool okToRun;

};