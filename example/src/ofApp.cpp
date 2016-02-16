#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofxPidee::setup();

	// Leds
	Pidee::setLedYellow( false );
	Pidee::setLedRed( false );
	Pidee::setLedGreen( false );

	// Button
	button = false;
	ofxPidee::onButton( [this] () {
		button = ofxPidee::getButton();
	});

	// Dip
	dipColor[ 0 ] = ofColor( 255, 72, 176 );
	dipColor[ 1 ] = ofColor( 255, 0, 0 );
	dipColor[ 2 ] = ofColor( 255, 154, 0 );
	dipColor[ 3 ] = ofColor( 255, 255, 0 );
	dipColor[ 4 ] = ofColor( 0, 128, 0 );
	dipColor[ 5 ] = ofColor( 0, 229, 206 );
	dipColor[ 6 ] = ofColor( 14, 0, 255 );
	dipColor[ 7 ] = ofColor( 171, 0, 211 );

	for ( int i = 0; i < 8; i++ ) {
		dip[ i ] = ofxPidee::getDip( i );
	}

	ofxPidee::onDip( [this] ( string name ) {
		for ( int i = 0; i < 8; i++ ) {
			string dipName = "dip." + ofToString( i + 1 );		
			if ( name == dipName ) {
				bool value = ofxPidee::getDip( i );
				ofLogNotice () << name << " did change to " << value;
			    dip[ i ] = value;
			}
		}
	});

}

//--------------------------------------------------------------
void ofApp::update(){
	ofxPidee::update();
}

//--------------------------------------------------------------
void ofApp::draw(){

	// Leds

	static float lastUpdateTime = 0.0f;
	static int ledSequence = 0;

	if ( ofGetElapsedTimef() - lastUpdateTime > 0.5f ) {
		if ( ++ledSequence > 3 ) {
			ledSequence = 0;
		}
		Pidee::setLedYellow( ledSequence == 0 );
		Pidee::setLedRed( ledSequence == 1 );
		Pidee::setLedGreen( ledSequence == 2 );
		lastUpdateTime = ofGetElapsedTimef();
	}

	// Button (background)

	if ( button ) {
		ofClear( 0, 0, 0 );
	} else {
		ofClear( 255, 255, 255 );
	}

	// Dip boxes

	float borderHeight = ofGetHeight() * 0.2;
	float borderWidth = ofGetWidth() * 0.1;
	float boxWidth = ( ofGetWidth() - ( borderWidth * 2 ) ) / 8;
	float boxHeight = ofGetHeight() - ( borderHeight * 2 );

	for ( int i = 0; i < 8; i++ ) {

		ofPushStyle();
		if ( dip[ i ] ) {
			ofSetColor( dipColor[ i ] );
		} else {
			ofSetColor( 0, 0, 0 );
		}
		ofDrawRectangle( borderWidth + ( boxWidth * i ), borderHeight, boxWidth, boxHeight );
		ofPopStyle();

	}

}