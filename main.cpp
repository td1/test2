#include "ofMain.h"
#include "picoApp.h"
//#include "ofGLProgrammableRenderer.h"

int main(int argc, char *argv[])
{
    if (argc != 2) {
    	ofLog(OF_LOG_ERROR,"Usage: %s myID\n", argv[0]);
        return 1;
    }
    myboardID = atoi(argv[1]); /* convert strings to integer */
    ofLog(OF_LOG_NOTICE,"myID = %d\n", myboardID);
    
	ofSetLogLevel(OF_LOG_VERBOSE);
    //ofSetLogLevel(OF_LOG_WARNING);
	//ofSetCurrentRenderer(ofGLProgrammableRenderer::TYPE);
	
    /* for res1280x960 measuring ofSetupOpenGL(1280, 960, OF_WINDOW); */
    /* change when measure the HDMI 720p output mode, otherwise segmentation fault */ 
    // ofSetupOpenGL(1280, 720, OF_WINDOW);
     
     
#if DEBUG_HOMOGRAPHY
	ofSetupOpenGL(1280, 720, OF_WINDOW); // HUNG set 1280x720 for camera
    // ofSetupOpenGL(640, 480, OF_WINDOW); // testpatttern 640x480
    // ofSetupOpenGL(640, 360, OF_WINDOW); // testpattern 640x360
#else
    // Normal operation 640x480
    // ofSetupOpenGL(WIDTH, HEIGHT, OF_WINDOW); // video 640x480
	ofSetupOpenGL(1280, 720, OF_WINDOW); // HUNG set 1280x720 for camera
#endif
    
	ofRunApp( new picoApp());
        
}
