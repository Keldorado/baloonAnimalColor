/**
 *
 * OFDevCon Example Code Sprint
 * Model Distort Example
 *
 * This example loads a model and distorts it using noise
 *
 * The model is the open source and freely licensed balloon dog by Rob Myers, commissioned by furtherfield:
 * http://www.furtherfield.org/projects/balloon-dog-rob-myers
 *
 * Created by James George for openFrameworks workshop at Waves Festival Vienna sponsored by Lichterloh and Pratersauna
 * Adapted during ofDevCon on 2/23/2012
 */

#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    ofSetFrameRate(60); //caps the frame rate
    ofSetVerticalSync(true); //"syncs the refresh-rate with your video-cards refresh-rate, thus fast moving stuff will be looking more akkurate" (from the documentation  --> just wanted to show you that I did my research :] )
    ofBackground(50, 50, 50, 0); //sets the color of the background
     
    
    gui.setup(); //sets up the gui
    gui.add(color.setup("color",ofColor(100,100,140),ofColor(0,0),ofColor(255,255))); //sliders for the color
    
    //we need to call this for textures to work on models
    ofDisableArbTex();
    
    //this makes sure that the back of the model doesn't show through the front
    ofEnableDepthTest();
    
    //now we load our model
    model.loadModel("dog/dog.3ds"); //our model
    model.setPosition(ofGetWidth()*.5, ofGetHeight() * 0.75, 0); //sets the position of the model
    
    light.enable();
    light.setAmbientColor(ofColor(100)); //sets the color of the model
    light.setDiffuseColor(ofColor(100)); //sets the light that is difusing around the model
    light.setSpecularColor(ofColor(100)); //sets the light that is shining back directly into our eyes
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    light.enable(); //enables light
    ofEnableDepthTest(); //this function prevents the back of the model from shinning through the front
    drawWithMesh(); //draws the mesh
    ofDisableDepthTest(); //turns off the depth test
    light.disable(); //turns off the light
    ofSetColor(255); //sets the color of the text in the GUI
    gui.draw(); //draws the gui
    ofSetColor(color); //sets the color
    
}

void ofApp::drawWithMesh(){
    
    //get the model attributes we need
    ofVec3f scale = model.getScale(); //gets the scale of the model
    ofVec3f position = model.getPosition(); //gets the position of the model
    float normalizedScale = model.getNormalizedScale(); //Normalizes the scale
    ofVboMesh mesh = model.getMesh(0); //gets the mesh
    ofTexture texture; //variabel for the texture
    ofxAssimpMeshHelper& meshHelper = model.getMeshHelper( 0 ); //gets the mesh helper
    bool bHasTexture = meshHelper.hasTexture(); //boolean to provide the model with texture
    if( bHasTexture ) {
        texture = model.getTextureForMesh(0); //applies the texture
    }
    
    ofMaterial material = model.getMaterialForMesh(0); //gets the material for the mesh
    
    ofPushMatrix(); //pushes the martrix
    
    //translate and scale based on the positioning.
    ofTranslate(position);
    ofRotate(-ofGetMouseX()*4, 0, 1, 0);
    ofRotate(90,1,0,0);
    ofScale(normalizedScale, normalizedScale, normalizedScale);
    ofScale(scale.x,scale.y,scale.z);
    
    //modifies the mesh with some noise
    float liquidness = 5;
    float amplitude = mouseY/100.0;
    float speedDampen = 5;
    vector<ofVec3f>& verts = mesh.getVertices();
    for(unsigned int i = 0; i < verts.size(); i++){
        verts[i].x += ofSignedNoise(verts[i].x/liquidness, verts[i].y/liquidness,verts[i].z/liquidness, ofGetElapsedTimef()/speedDampen)*amplitude;
        verts[i].y += ofSignedNoise(verts[i].z/liquidness, verts[i].x/liquidness,verts[i].y/liquidness, ofGetElapsedTimef()/speedDampen)*amplitude;
        verts[i].z += ofSignedNoise(verts[i].y/liquidness, verts[i].z/liquidness,verts[i].x/liquidness, ofGetElapsedTimef()/speedDampen)*amplitude;
    }
    
    //draw the model manually
    if(bHasTexture) texture.bind();
    material.begin(); //begins the matiral
    mesh.drawWireframe(); //adds wire frame
    mesh.drawFaces(); //draws the faces
    material.end(); //stops drawing the matiral
    if(bHasTexture) texture.unbind(); //unbinds the texture
    
    ofPopMatrix(); //pops the matrix
    
}
