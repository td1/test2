#pragma once

#include "ofMain.h"
#include "ofxOMXPlayer.h"
#include "myID.h"
#include "ConsoleListener.h"
#include "ofxOpenCv.h"

extern "C" {
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <fcntl.h>
// #include <linux/fb.h>
#include <sys/mman.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <pthread.h>
#include <sys/ioctl.h>
    
#include "fb.h"

}

/* COMPILING SWITCH MODIFICATION */
//#define HOMOGRAPHY_TRANSFORM_ENABLE     1
//#define ENABLE_BLENDING                 1
//#define RESYNC_ENABLE                     1
//#define GENERATE_BLOBS					  1
#define TEST_RESYNC_HOMOGRAPHY				1
#define TEST_RESYNC_CAPTURE					1

/* DEBUG/TEST SWITCH */
//#define DEBUG_HOMOGRAPHY                1
//#define OUTPUT_RES_1280_720             1
//#define OUTPUT_RES_1280_960             1

//#define OFFSET_16_9                     1 /* comment out to support 640x480 4:3 aspect */
#define USE_COMMON_HOMOGRAPHY           1

#define ID_TD1              1
#define ID_TD2              2
#define ID_TD3              3
#define ID_TD4              4

#define MAX_PICO_SET        4   // Four PICO sets
#define NUMBER_OF_QRCODE    8   // getHomography - screenCapture two QRs code each set, x98 and x99
                                // syncVideo - screenShot two QRs code sequentially send, x01, x02...x99
                                // 4 sets, total QRs = 8

#define WAIT_AFTER_DONE_GET_HOMOGRAPHY  50 // 5 HUNG TEST extended waiting time after done getHomography
#define MIN_FRAME_DELAY     20

#define MAX_FRAMES          90  // 99
#define BAR_WIDTH           5	// pixels
#define BAR_HEIGHT          200	// pixels
#define BAR_DISTANCE        20	// pixels
#define UPPERLEFT_X         120 // pixels
#define UPPERLEFT_Y         140 // pixels
#define CAPTURE_RATE        1	// seconds

#define HOVL                600
#define VOVL                440

#define NUMBER_OF_POINTS    8
#define NROW                16
#define NCOL                9

#define NR_END              1
#define FREE_ARG char*
#define SIGN(a,b) ((b) >= 0.0 ? fabs(a) : -fabs(a))
static double dmaxarg1,dmaxarg2;
#define DMAX(a,b) (dmaxarg1=(a),dmaxarg2=(b),(dmaxarg1) > (dmaxarg2) ?\
(dmaxarg1) : (dmaxarg2))
static int iminarg1,iminarg2;
#define IMIN(a,b) (iminarg1=(a),iminarg2=(b),(iminarg1) < (iminarg2) ?\
(iminarg1) : (iminarg2))

static int myboardID;

#if OUTPUT_RES_1280_720        
        static const int WIDTH = 1280; // 1280; FOR TEST 720p
        static const int HEIGHT = 720; 
#elif OUTPUT_RES_1280_960
        static const int WIDTH = 1280; // FOR TEST 1280x960
        static const int HEIGHT = 960;  
#else
        static const int WIDTH = 640;  // Normal operation 640x480
        static const int HEIGHT = 480;  
#endif

class picoApp : public ofBaseApp, public SSHKeyListener{
	
public:
	
	void setup();
	void update();
	void draw();
	
	void keyPressed(int key);
	void mousePressed(int x, int y, int button);

	ofxOMXPlayer omxPlayer;
	bool doSaveImage;
	
	ConsoleListener consoleListener;
	void onCharacterReceived(SSHKeyListenerEventData& e);

	void readMatrix(char* filename);
	void readMatrix2(char* filename);

	int  getRightX(int y);
	int  getLeftX(int y);
	int getTopY(int x);
	int getBottomY(int x);
	double getXFade(int x, int y);
	double getYFade(int x, int y);
	void calFading(void);

	int syncVideo(int boardID);
	int getHomography(int boardID);
	int loadQR(int qrnum);

	ofTexture 				pixelOutput;
        
#if RESYNC | TEST_RESYNC_CAPTURE
	ofVideoGrabber 			captureVid;
	ofxCvColorImage 		captureImg;
	ofxCvGrayscaleImage 	grayCaptureImg;
	ofxCvGrayscaleImage 	grayBackground;
	ofxCvGrayscaleImage 	grayDiff;
	ofxCvContourFinder 		contourFinder;

	int 					threshold;
	bool					bUpdateBackground;
#endif

	bool doUpdatePixels;
	bool startPlayVideo;

	int width, height;
	char matrixFN[30];
	int boardID;
	unsigned char fadeRight,fadeDown;

	int xoffset,yoffset;
	double htlx,htly,htrx,htry,hblx,hbly,hbrx,hbry;
	double vtlx,vtly,vtrx,vtry,vblx,vbly,vbrx,vbry;
	double topSlope,bottomSlope,leftSlope,rightSlope,leftSlopeInv,rightSlopeInv;

	// move WIDTH/HEIGHT out of this class

	int yOverlapTop[WIDTH];
	int yOverlapBottom[WIDTH];
	int xOverlapLeft[HEIGHT];
	int xOverlapRight[HEIGHT];
	unsigned char xfadeMat[HEIGHT][WIDTH];
	unsigned char yfadeMat[HEIGHT][WIDTH];
	float matrix[3][3];

	double h1[9];
	double h1inv[9];
	double h2[9];
	double h2inv[9];

	// double **dmatrix(int, int, int, int);
	// double *dvector(int, int);
	// void svdcmp(double **, int, int, double *, double **);
	// END WORKING HERE

	pthread_mutex_t mutex;
	double barRate;
	double framePeriod;

	float myMatrix[16];
	float resyncMatrix[16];
	ofPoint src[4];
	ofPoint dst[4];
	int nClick;
	int setPositionByMouse;

	unsigned char qr_frame[230*230*3];
};

