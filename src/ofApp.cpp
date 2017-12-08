#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(255,255,255);
    ofSetVerticalSync(true);
	ofLog(OF_LOG_NOTICE,"hello");

	//load the IP addresses for the network adapter and artnet device
	vector < string > linesOfTheFile;
	ofBuffer buffer = ofBufferFromFile("config.txt");
	for (auto line : buffer.getLines()) {
		linesOfTheFile.push_back(line);
		ofLog(OF_LOG_NOTICE,"a:"+line);
	}
	localIP = linesOfTheFile[1];
	deviceIP = linesOfTheFile[2];
    
    myMovie.load("movies/kwallencombined.mov");
    myMovie.setLoopState(OF_LOOP_NORMAL);
    myMovie.play();
    
    //artnet.setup("10.85.37.111"); //this is the IP on the port on the host machine that you will be connecting from
	artnet.setup(localIP.c_str());
    testImage.allocate(512,1,OF_IMAGE_COLOR);
}

//--------------------------------------------------------------
void ofApp::update(){
    myMovie.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofSetHexColor(0xFFFFFF);
    //draw the movie
    myMovie.draw(20,20,100,100);
    ofSetHexColor(0x000000);
    //get the movie pixels
    ofPixels & pixels = myMovie.getPixels();
    
    //not used but useful
    int vidWidth = pixels.getWidth();
    int vidHeight = pixels.getHeight();
    int nChannels = pixels.getNumChannels();
    
    //get the color of the first pixel value
    float rVal,gVal,bVal;
    ofColor myColor = pixels.getColor(0);
    ofColor myColor2 = pixels.getColor(myMovie.getWidth()*0.5,0);
    //draw the pixel value
    ofSetColor(myColor);
    ofDrawCircle(40,140,20);
    ofSetColor(myColor2);
    ofDrawCircle(80,140,20);
    
    //draw the individual pixel rgb values
    rVal = myColor.r;
    gVal = myColor.g;
    bVal = myColor.b;
    
    testImage.getPixels()[0]= myColor.r;
    testImage.getPixels()[1]= myColor.g;
    testImage.getPixels()[2]= myColor.b;
    testImage.getPixels()[3]= myColor2.r;
    testImage.getPixels()[4]= myColor2.g;
    testImage.getPixels()[5]= myColor2.b;
    

    //artnet.sendDmx("10.85.37.24", testImage.getPixels().getData(), 512);
	artnet.sendDmx(deviceIP.c_str(), testImage.getPixels().getData(), 512);
    
    ofSetColor(255,0,0);
    ofDrawRectangle(20,220,20,rVal);
    ofSetColor(0,255,0);
    ofDrawRectangle(40,220,20,gVal);
    ofSetColor(0,0,255);
    ofDrawRectangle(60,220,20,bVal);
    
    ofSetColor(255,0,0);
    ofDrawRectangle(100,220,20,myColor2.r);
    ofSetColor(0,255,0);
    ofDrawRectangle(120,220,20,myColor2.g);
    ofSetColor(0,0,255);
    ofDrawRectangle(140,220,20,myColor2.b);
    ofSetColor(0,0,0);
    string myString = "val: " + ofToString(rVal) + "," + ofToString(gVal) + "," + ofToString(bVal);
    
    //movie info
    ofDrawBitmapString(myString,20,200);
    ofDrawBitmapString("frame: " + ofToString(myMovie.getCurrentFrame()) + "/"+ofToString(myMovie.getTotalNumFrames()),140,30);
    ofDrawBitmapString("duration: " + ofToString(myMovie.getPosition()*myMovie.getDuration(),2) + "/"+ofToString(myMovie.getDuration(),2),140,50);
    
    if(myMovie.getIsMovieDone()){
        ofSetHexColor(0xFF0000);
        ofDrawBitmapString("end of movie",20,440);
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

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

void ofApp::exit(){
    for(int i =0; i<testImage.getPixels().size();i++){
        testImage.getPixels()[i] = 0;
    }
    artnet.sendDmx("10.85.37.24", testImage.getPixels().getData(), 512);
}
