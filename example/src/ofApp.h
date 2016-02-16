#pragma once

#include "ofMain.h"
#include "ofxPidee.h"

class ofApp : public ofBaseApp{
	public:
		void setup();
		void update();
		void draw();

        bool button;
        ofColor dipColor[ 8 ];
        bool dip[ 8 ];
};
