#pragma once

#include "ofMain.h"
#include "ofxGui.h"
struct pingPongBuffer {
public:
    void allocate( int _width, int _height, int _internalformat = GL_RGBA, int _numColorBuffers = 1) {
        // Allocate
        ofFbo::Settings fboSettings;
        fboSettings.width = _width;
        fboSettings.height = _height;
        fboSettings.numColorbuffers = _numColorBuffers;
        fboSettings.useDepth = false;
        fboSettings.internalformat = _internalformat;
        fboSettings.wrapModeHorizontal = GL_CLAMP_TO_EDGE;
        fboSettings.wrapModeVertical = GL_CLAMP_TO_EDGE;
        fboSettings.minFilter = GL_NEAREST;
        fboSettings.maxFilter = GL_NEAREST;
        for(int i = 0; i < 2; i++) {
            FBOs[i].allocate(fboSettings);
        }
        
        // Assign
//        src = &FBOs[0];
//        dst = &FBOs[1];
        
        // Clean
        clear();
        
        flag = 0;
        swap();
        flag = 0;
    }
    
    void swap() {
        src = &(FBOs[(flag) % 2]);
        dst = &(FBOs[++(flag) % 2]);
    }
    
    void clear() {
        for(int i = 0; i < 2; i++) {
            FBOs[i].begin();
            ofClear(0, 255);
            FBOs[i].end();
        }
    }
    
    ofFbo& operator[](int n){ return FBOs[n]; }
    ofFbo *src;
    ofFbo *dst;
    
private:
    ofFbo FBOs[2];
    int flag;
};
class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
    ofShader updatePos;
    ofShader updateRender;
    
    pingPongBuffer posPingPong;
    
    ofFbo renderFBO;
    
    ofEasyCam cam;
    
    ofVec2f m; // mousePos
    bool mouseFrag; // is mouse dragged
    float time;
    int width, height;
    int numParticle;
    int textureRes;
    
    // Attractor
    ofVec3f attractor;
    
    // Sound
    float *fftSmoothed;
    float *volume;
    int nBandsToGet;
    ofSoundPlayer sound;
    
    // Mesh
    ofVboMesh mesh;
    
    // Parametor
    ofxPanel gui;
    ofParameter<float> strength;
    ofParameter<float> centerX;
    ofParameter<float> centerY;
    ofParameter<float> centerZ;
    ofxToggle isAttract;
    
};
