#pragma once

#include "ofMain.h"
#include "ofxOsc.h"

// listen on port 12345
#define PORT 12345
#define NUM_MSG_STRINGS 20

struct Bot {
    int id;
    float x;
    float y;
    float rotation;
    string toString(){
        return ofToString(id) + " - x:" +ofToString(x) + " y:"+ofToString(y) + " r:"+ ofToString(rotation);
    }
};


//class Bot {
//public:
//    Bot( int id, float x, float y, float rotation) : id(int id), x(float x), y(float y), rotation(float rotation);
//    int id;
//    float x;
//    float y;
//    float rotation;
//};

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
        int getBotIndex(int id);

		ofTrueTypeFont font;
		ofxOscReceiver receiver;

		int current_msg_string;
		string msg_strings[NUM_MSG_STRINGS];
		float timers[NUM_MSG_STRINGS];

		int mouseX, mouseY;
		string mouseButtonState;
    
        ofImage receivedImage;

        vector<Bot> bots;
};
