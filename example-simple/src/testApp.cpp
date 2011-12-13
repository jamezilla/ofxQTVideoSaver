#include "testApp.h"
#include <string>

//--------------------------------------------------------------
testApp::~testApp(){
	// finalize the movie and write it out to disk
	mVidSaver.finishMovie();
}


//--------------------------------------------------------------
void testApp::setup(){
	
	camWidth 		= 320;	// try to grab at this size. 
	camHeight 		= 240;
	
	vidGrabber.setVerbose(true);
	vidGrabber.initGrabber(camWidth,camHeight);
	
	videoInverted 	= new unsigned char[camWidth*camHeight*3];
	videoTexture.allocate(camWidth,camHeight, GL_RGB);
	
	// create a unique file name for this movie file
	createFileName();
	
	// initialize a timestamp which we'll use to properly
	// time the frame as they're added to the movie
	mTimestamp = ofGetElapsedTimef();
	
	// init the movie saver
    mVidSaver.setCodecQualityLevel(OF_QT_SAVER_CODEC_QUALITY_NORMAL);
    mVidSaver.setup(camWidth, camHeight, mFileName);

}


//--------------------------------------------------------------
void testApp::update(){
	
	ofBackground(100,100,100);
	
	vidGrabber.grabFrame();
	
	if (vidGrabber.isFrameNew()){
		// figure out how much time elapsed since the last frame
		float time = ofGetElapsedTimef() - mTimestamp;
		
		// add this frame to the movie
		mVidSaver.addFrame(vidGrabber.getPixels(), time);
		
		// update the timestamp to the current time
		mTimestamp = ofGetElapsedTimef();
	}

}

//--------------------------------------------------------------
void testApp::draw(){
	ofSetHexColor(0xffffff);
	
	ofPushMatrix();
	ofTranslate(20, 20);
	
	vidGrabber.draw(0,0);
	
	ofPushMatrix();
	ofTranslate(0, camHeight + 20, 0);
	
	ofDrawBitmapString("fps: " + ofToString(ofGetFrameRate()),0,0);
    ofDrawBitmapString("Press escape to quit the application.",0,20);
    ofDrawBitmapString(mFileName + " will appear in your data folder.",0,40);

	ofPopMatrix();
	ofPopMatrix();
	
}


//--------------------------------------------------------------
void testApp::keyPressed  (int key){ 
	
//	if (key==27) 
	
}

void testApp::createFileName(void)
{
    // create a uniqe file name
	ostringstream oss;
	oss << ofGetYear() << "-";
	oss << setw(2) << setfill('0') << ofGetMonth() << "-";
	oss << setw(2) << setfill('0') << ofGetDay() << "-";
	oss << setw(2) << setfill('0') << ofGetHours() << "-";
	oss << setw(2) << setfill('0') << ofGetMinutes() << "-";
	oss << setw(2) << setfill('0') << ofGetSeconds() << ".mov";
	mFileName = oss.str();	
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){ 
	
}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){
	
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){
	
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
	
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}
