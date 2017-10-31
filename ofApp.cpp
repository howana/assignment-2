#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
	eyeClose = false;
	camWidth = 320;
	camHeight = 240;
	eye = 200;
	okToRun = true;
	backgroundColor = ofColor::white;
	vidGrabber.setDeviceID(0);
	biggestFaceWidth = 0;
	meh.load("meh.png");
	discontent.load("discontent.png");
	anger.load("angry.png");
	happy.load("happy.png"); 
	blank.load("blank.png");
	expression = meh;
	expression.setAnchorPoint(meh.getWidth() / 2, meh.getHeight() / 2);
	mehNoise.load("blip3.wav");
	happyNoise.load("blip3.wav");
	angryNoise.load("blip4.wav");
	discontentNoise.load("blip2.wav");
	staticNoise.load("static.mp3");
	vidGrabber.initGrabber(camWidth, camHeight);

	finder.setup("haarcascade_frontalface_default.xml");
	
	//rgb.allocate(camWidth, camHeight);
	//hsb.allocate(camWidth, camHeight);
	//hue.allocate(camWidth, camHeight);
	//sat.allocate(camWidth, camHeight);
	//bri.allocate(camWidth, camHeight);
	//filter1.allocate(camWidth, camHeight);
	//filter2.allocate(camWidth, camHeight);
	finalImage.allocate(camWidth, camHeight);

}

//--------------------------------------------------------------
void ofApp::update() {
	vidGrabber.update();
	if (vidGrabber.isFrameNew())
		
	{
		
		//rgb.setFromPixels(vidGrabber.getPixels());
		//hsb = rgb;
		//hsb.convertRgbToHsv();
		//hsb.convertToGrayscalePlanarImages(hue, sat, bri);

		//int hueRange = 10;
		//for (int i = 0; i < camWidth * camHeight; ++i) {
			//filter1.getPixels()[i] = ofInRange(hue.getPixels()[i],
				//findHue - hueRange,
				//findHue + hueRange) ? 255 : 0;
	
		//}
		finder.findHaarObjects(vidGrabber.getPixels());
	}

	if (ofGetElapsedTimef() > shutdownStartTime + 5) {
		okToRun = true;
		ofSoundStopAll();

	}
	if (okToRun) {
		backgroundColor = ofColor::white;
		if (finder.blobs.size() == 0) {
			if (currentEmotion != "happy") { //If the current emotion isn't happy, and there are no faces on screen
				expression = meh; //set our current displayed face to meh
				previousEmotion = currentEmotion; //save off our current emotion into a variable so we can check it later
				currentEmotion = "meh"; //say that we're currently feeling meh
				mehNoise.setSpeed(ofRandom(0.5, 1.0));
				mehNoise.setVolume(0.1f);
				mehNoise.play();
				if (currentEmotion != previousEmotion) { //if we've changed from being something else to meh
					MehStartTime = ofGetElapsedTimef();
				}
				if (ofGetElapsedTimef() > MehStartTime + 3.0) { //if we've stayed at meh for 3 seconds
					expression = happy;
					currentEmotion = "happy";//change us to happy 
					//happyNoise.play();
				}
				
			}
			if (currentEmotion == "happy") {
				happyNoise.setSpeed(ofRandom(1.2, 2.0));
				happyNoise.setVolume(0.01f);
				happyNoise.play();
			}
		}

		for (int i = 0; i < finder.blobs.size(); ++i) {
			if (finder.blobs[i].boundingRect.width > biggestFaceWidth) {
				biggestFace = finder.blobs[i].boundingRect;
			}
			if ((biggestFace.getHeight()) <= 115) {// formerly finder.blobs[i].boundingRect.width
				expression = discontent;
				previousEmotion = currentEmotion;
				currentEmotion = "discontent";
				discontentNoise.setSpeed(ofRandom(1.1, 1.3));
				discontentNoise.setVolume(0.20);
				discontentNoise.play();
			}
			//ofDrawRectangle(finder.blobs[i].boundingRect);
			if ((120 < biggestFace.getHeight())) { //formerly 65 < finder.blobs[i].boundingRect.width
				expression = anger;
				previousEmotion = currentEmotion;
				currentEmotion = "angry";
				angryNoise.setSpeed(ofRandom(0.2, 2.0));
				angryNoise.setVolume(1.5f);
				angryNoise.play();
				if (currentEmotion != previousEmotion) { //if we've changed from some other emotion to being angry
					angryStartTime = ofGetElapsedTimef();
				}
				if (ofGetElapsedTimef() > angryStartTime + 2) { //If i'm angry for 2 seconds, turn me off
					expression = blank;
					angryNoise.stop();
					//currentEmotion = "shutdown";
					shutdownStartTime = ofGetElapsedTimef();//as soon as I've been turned off, start counting
					ofSoundStopAll();
					backgroundColor = ofColor::black;
					okToRun = false; 
					PlaySound(staticNoise);
				}
			}


		}
	}
}

//--------------------------------------------------------------
void ofApp::draw() {
	ofSetBackgroundColor(backgroundColor);
	ofSetColor(ofColor::black);
	//vidGrabber.draw(0, 0, camWidth, camHeight);
	//ofDrawEllipse((ofGetScreenWidth() / 2 + 70), (ofGetScreenHeight() / 2 - 100), 100, eye);
	//ofDrawEllipse((ofGetScreenWidth()/2 -300), (ofGetScreenHeight()/2-100), 100, eye);
	for (int i = 0; i < finder.blobs.size(); ++i) {
		//ofDrawRectangle(finder.blobs[i].boundingRect);
		//ofDrawRectangle(biggestFace);
	}

		
	expression.draw(ofGetWidth() / 2, ofGetHeight() / 2);
	ofFill();

}
//void PlaySound(ofSoundPlayer sound) {
	//sound.setLoop(true);
	//sound.play();
//}
//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
	switch (key) {
		case 'f':
		ofToggleFullscreen();
		break;
	}
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h) {

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg) {

}

void ofApp::PlaySound(ofSoundPlayer sound)
{
	sound.setLoop(true);
	sound.play();
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo) {

}

