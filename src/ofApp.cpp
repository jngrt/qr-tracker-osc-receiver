#include "ofApp.h"


int ofApp::getBotIndex(int id) {
    for( int i=0; i<bots.size();i++) {
        if( Bot(bots[i]).id == id ) {
            return i;
        }
    }
    return -1;
}

//--------------------------------------------------------------
void ofApp::setup(){
	// listen on the given port
	cout << "listening for osc messages on port " << PORT << "\n";
	receiver.setup(PORT);

	current_msg_string = 0;
	mouseX = 0;
	mouseY = 0;
	mouseButtonState = "";

	//ofBackground(190,230,240);
    ofBackgroundHex(0xBFE6F2);

}

//--------------------------------------------------------------
void ofApp::update(){

	// hide old messages
	for(int i = 0; i < NUM_MSG_STRINGS; i++){
		if(timers[i] < ofGetElapsedTimef()){
			msg_strings[i] = "";
		}
	}

	// check for waiting messages
	while(receiver.hasWaitingMessages()){
		// get the next message
		ofxOscMessage m;
		receiver.getNextMessage(m);
        

        if(m.getAddress() == "/robogps") {
            int id = m.getArgAsInt(0);
            float x = m.getArgAsFloat(1);
            float y = m.getArgAsFloat(2);
            float rot = m.getArgAsFloat(3);

            int index = this->getBotIndex(id);
            if( index == -1 ) {
                bots.push_back(Bot{id,x,y,rot});
            } else {
                bots[index].x = x;
                bots[index].y = y;
                bots[index].rotation = rot;
            }
        }
		// check for mouse moved message
        else if(m.getAddress() == "/mouse/position"){
			// both the arguments are int32's
			mouseX = m.getArgAsInt32(0);
			mouseY = m.getArgAsInt32(1);
		}
		// check for mouse button message
		else if(m.getAddress() == "/mouse/button"){
			// the single argument is a string
			mouseButtonState = m.getArgAsString(0);
		}
        /*
        // check for an image being sent (note: the size of the image depends greatly on your network buffer sizes - if an image is too big the message won't come through )
        else if(m.getAddress() == "/image" ){
            ofBuffer buffer = m.getArgAsBlob(0);
            receivedImage.load(buffer);
        }
		else{
			// unrecognized message: display on the bottom of the screen
			string msg_string;
			msg_string = m.getAddress();
			msg_string += ": ";
			for(int i = 0; i < m.getNumArgs(); i++){
				// get the argument type
				msg_string += m.getArgTypeName(i);
				msg_string += ":";
				// display the argument - make sure we get the right type
				if(m.getArgType(i) == OFXOSC_TYPE_INT32){
					msg_string += ofToString(m.getArgAsInt32(i));
				}
				else if(m.getArgType(i) == OFXOSC_TYPE_FLOAT){
					msg_string += ofToString(m.getArgAsFloat(i));
				}
				else if(m.getArgType(i) == OFXOSC_TYPE_STRING){
					msg_string += m.getArgAsString(i);
				}
				else{
					msg_string += "unknown";
				}
			}
			// add to the list of strings to display
			msg_strings[current_msg_string] = msg_string;
			timers[current_msg_string] = ofGetElapsedTimef() + 5.0f;
			current_msg_string = (current_msg_string + 1) % NUM_MSG_STRINGS;
			// clear the next line
			msg_strings[current_msg_string] = "";
		}
        */

	}
}


//--------------------------------------------------------------
void ofApp::draw(){

	string buf;
	buf = "listening for osc messages on port" + ofToString(PORT);
	ofDrawBitmapString(buf, 10, 20);
    
    //if(receivedImage.getWidth() > 0){
    //    ofDrawBitmapString("Image:", 10, 160);
    //    receivedImage.draw(10, 180);
    //}


	// draw mouse state
	buf = "mouse: " + ofToString(mouseX, 4) +  " " + ofToString(mouseY, 4);
	ofDrawBitmapString(buf, 430, 20);
	ofDrawBitmapString(mouseButtonState, 580, 20);

	for(int i = 0; i < NUM_MSG_STRINGS; i++){
		ofDrawBitmapString(msg_strings[i], 10, 40 + 15 * i);
	}

    
    ofNoFill();
    ofSetHexColor(0xff0000);
    
    ofDrawBitmapString("Bots detected: " + ofToString(bots.size()),430, 50);
    for(int i=0; i < bots.size(); i++){
        ofPushMatrix();
        ofTranslate(bots[i].x * ofGetWidth(),bots[i].y * ofGetHeight());
        ofRotate(ofRadToDeg(bots[i].rotation));
        ofDrawRectangle(-50,-50,100,100);
        
        ofDrawRectangle(0,-50,10,10);
        ofPopMatrix();

        ofDrawBitmapString(bots[i].toString(), 430, 70 + i * 20);
        
    }


}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){

}
