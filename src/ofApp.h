
#pragma once

#include "ofMain.h"
#include "ofxAssimpModelLoader.h"
#include "ofxGui.h"

class ofApp : public ofBaseApp{
    
public:
    void setup();
    void draw();
    
    
    //this is our model we'll draw
    ofxAssimpModelLoader model;
    
     //for our light
    ofLight light;
    
    //draws our model and our mesh
    void drawWithModel();
    void drawWithMesh();
    
        bool bHide;
    
    
        ofxColorSlider color; //color slider variable
        ofxPanel gui; //allows us to use the GUI
    

};