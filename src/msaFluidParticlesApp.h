#pragma once

#include "MSAFluid.h"
#include "MSATimer.h"
#include "ParticleSystem.h"

#include "ofMain.h"
#include "ofxMidi.h"
#include "MMidiListener.h"
#include "FluidControls.h"
#include "FluidMidiMapper.h"
#include "ImgVectorFieldFactory.h"
#include "ImgTextureFactory.h"
#include "ImgVectorField.h"
#include "ImgCluster.h"
#include "ImgClusterFactory.h"
#include "ImageLoader.h"
#include <vector>
#include "MSABPMTapper.h"
#include "Automator.h"
#include "AkaiAPC20Device.h"
#include "EvolutionUC16Device.h"

#define FRAME_INTERVAL 1	//< Interval used for updating image vectors

// comment this line out if you don't wanna use the GUI
// you will need ofxSimpleGuiToo, ofxMSAInteractiveObject & ofxXmlSettings
// if you don't use the GUI, you won't be able to see the fluid parameters
// #define USE_GUI		


#ifdef USE_GUI 
#include "ofxSimpleGuiToo.h"
#endif

using namespace MSA;

class msaFluidParticlesApp : public ofSimpleApp
{
public:

	// Inherited Members
	void setup();
	void update();
	void draw();
	void exit();
	
	void keyPressed(int key);
	void mouseMoved(int x, int y );
	void mouseDragged(int x, int y, int button);

	// Public methods
	void windowResized(int w, int h);

	void fadeToColor(float r, float g, float b, float speed);
	void addToFluid(Vec2f pos, Vec2f vel, bool addColor, bool addForce);
	void addClusterToFluid();

	// Midi Related
	FluidControls			mControls;

	// Image Related
	ImageLoader				mImageLoader;
	ImgVectorFieldFactory	mImageVectorFactory;
	ImgTextureFactory		mImageTextureFactory;

	std::vector<ImgVectorField> mImageVectors;
	std::vector<ImgTexture>		mImageTextures;
	std::vector<ofImage>		mDjImages;

	ImgTexture*			mSelectedImage;
	ImgVectorField*		mSelectedVectorField;

	int					mVectorIndex;
	int					mImageIndex;

	// Syncing
	Automator*			mAutomator;

	// Specific fluids
	MSA::FluidSolver	mFluidSolver;
	MSA::FluidDrawerGl	mFluidDrawer;	
	
	// Particle system
	ParticleSystem		mParticleSystem;
	
	MSA::Vec2f			pMouse;

	// Define some of the midi objects we need to interact with the application
	ofxMidiIn			mMidiIn;
	ofxMidiIn			mMidiIn2;
	ofxMidiOut			mMidiOut;
	MMidiListener		mMidiListener;
	
	int					mAPCPort;
	int					mUCPort;
	int					mAPCOutPort;

	// The midi devices
	EvolutionUC16MidiDevice*	mUCMidiController;
	AkaiAPC20MidiDevice*		mAPCMidiController;

	// Just here so I can set the channels from a selection
	MidiDevice*			mSelectedMidiDevice;

	// Some statics for controlling speed
	static float MAX_WEIGHTED;
	static float MAX_NORMALIZED;

	
#ifdef USE_GUI 
	ofxSimpleGuiToo	gui;
#endif
	
	
};

extern msaFluidParticlesApp *myApp;



