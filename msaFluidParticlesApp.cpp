#include "msaFluidParticlesApp.h"
#include "ImgVectorField.h"
#include "ImgTexture.h"
#include "ImgVectorFieldFactory.h"
#include "ofImage.h"
#include <iostream>
#include <vector>

using namespace MSA;
using namespace std;

char sz[] = "";

float msaFluidParticlesApp::MAX_WEIGHTED = 0.0002f / 5.0f;
float msaFluidParticlesApp::MAX_NORMALIZED = 0.00001f / 5.0f;


//--------------------------------------------------------------

void msaFluidParticlesApp::setup() 
{
	cout << "\n\nInitializing Miko, have fun!\n\n";

	mAPCOutPort = 1;
	mAPCPort = 0;
	mUCPort  = 1;

	mMidiIn.listPorts();

	std::cout << "\nSelect APC Input Port: ";
	std::cin >> mAPCPort;

	std::cout << "Select UC16 Input Port: ";
	std::cin >> mUCPort;

	std::cout << "Select APC Output Port, usually the APC port + 1: ";
	std::cin >> mAPCOutPort;

	mMidiIn.openPort(mAPCPort);
	mMidiIn.addListener(&mMidiListener);
	mMidiIn.setVerbose(false);
	mMidiIn.ignoreTypes(false, false, false);

	mMidiIn2.openPort(mUCPort);
	mMidiIn2.addListener(&mMidiListener);
	mMidiIn2.setVerbose(false);
	mMidiIn2.ignoreTypes(false, false, false);


	// Load all of our maps in memory!
	mImageLoader.loadTextureMaps(mImageTextures);
	mImageLoader.loadVectorMaps(mImageVectors);
	mImageLoader.loadDjImages(mDjImages);

	// Initialize the first image and set maximums
	mControls.setMaxImages(mImageTextures.size());
	mControls.setMaxVectorFields(mImageVectors.size());
	mControls.setMaxOverlays(mDjImages.size());
	
	mSelectedVectorField = &(mImageVectors[mControls.getVectorIndex()]);
	mSelectedImage = &(mImageTextures[mControls.getImageIndex()]);
	mControls.setMaxClusters(mSelectedImage->getClusterCount());

	// setup open frameworks stuff
	ofEnableAlphaBlending();
	ofSetBackgroundAuto(true);
	ofSetFrameRate(60);
	ofBackground(0, 0, 0);
	ofSetVerticalSync(true);

	// setup fluid stuff
	mFluidSolver.setup(500, 500); // FADE SPEED WAS 0.02!!
	mFluidSolver.enableRGB(true).setFadeSpeed(0.002).setDeltaT(0.5).setVisc(0.00015).setColorDiffusion(0);
	//mFluidSolver.enableVorticityConfinement(true);
	mFluidDrawer.setup( &mFluidSolver );
	mFluidSolver.setWrap(true, true);
	mParticleSystem.setFluidSolver( &mFluidSolver);
	mParticleSystem.setControls(&mControls);

	pMouse = getWindowCenter();

	// Setup the automator
	mAutomator = new Automator(&mControls);
	mAutomator->getBPMDevice()->startFresh();

	// Create the APC 20 device
	mAPCMidiController = new AkaiAPC20MidiDevice(mAPCPort, mAPCOutPort, &mControls, mAutomator);
	mMidiListener.addMidiDeviceListener(mAPCMidiController);

	// Create the UPC 16 device
	mUCMidiController = new EvolutionUC16MidiDevice(mUCPort, mAPCOutPort+1, &mControls, mAutomator);
	mMidiListener.addMidiDeviceListener(mUCMidiController);

	// Force a resize
	windowResized(ofGetWidth(), ofGetHeight());

//TODO: CLONE THESE CONTROLS IN OUR OWN CONTROLS FACTORY
#ifdef USE_GUI 
	gui.addSlider("fluidCellsX", mControls.mFluidCellsX, 20, 400);
	gui.addButton("resizeFluid", mControls.mResizeFluid);
	gui.addSlider("fs.viscocity", mFluidSolver.viscocity, 0.0, 0.01); 
	gui.addSlider("fs.colorDiffusion", mFluidSolver.colorDiffusion, 0.0, 0.0003); 
	gui.addSlider("fs.fadeSpeed", mFluidSolver.fadeSpeed, 0.0, 0.1); 
	gui.addSlider("fs.solverIterations", mFluidSolver.solverIterations, 1, 50); 
	gui.addSlider("fs.deltaT", mFluidSolver.deltaT, 0.1, 5);
	gui.addComboBox("fd.drawMode", (int&)mFluidDrawer.drawMode, kFluidDrawCount, (string*)FluidDrawerGl::drawOptionTitles);
	gui.addToggle("fs.doRGB", mFluidSolver.doRGB); 
	gui.addToggle("fs.doVorticityConfinement", mFluidSolver.doVorticityConfinement); 
	gui.addToggle("drawFluid", mControls.mDrawFluid); 
	gui.addToggle("drawParticles", mControls.mDrawParticles); 
	gui.addToggle("fs.wrapX", mFluidSolver.wrap_x); 
	gui.addToggle("fs.wrapY", mFluidSolver.wrap_y);
	gui.setDefaultKeys(true);
	gui.currentPage().setXMLName("MSAFluidDemo.xml");
	gui.setAutoSave(false);
	gui.show();
#endif
}



void msaFluidParticlesApp::exit()
{
	mMidiIn.closePort();
	mMidiIn2.closePort();
	mMidiIn.removeListener(&mMidiListener);
	mMidiIn2.removeListener(&mMidiListener);
}



void msaFluidParticlesApp::fadeToColor(float r, float g, float b, float speed) {
	glColor4f(r, g, b, speed);
	ofRect(0, 0, ofGetWidth(), ofGetHeight());
}



// add force and dye to fluid, and create particles
void msaFluidParticlesApp::addToFluid( Vec2f pos, Vec2f vel, bool addColor, bool addForce ) {
	float speed = vel.x * vel.x  + vel.y * vel.y * getWindowAspectRatio() * getWindowAspectRatio();    // balance the x and y components of speed with the screen aspect ratio
	if(speed > 0) 
	{
		pos.x = constrain(pos.x, 0.0f, 1.0f);
		pos.y = constrain(pos.y, 0.0f, 1.0f);

		const float colorMult = 0.1 * mControls.mAlphaFluid;
		const float velocityMult = 30;

		int index = mFluidSolver.getIndexForPos(pos);

		if(addColor) 
		{
			// Add new particles and fluid
			if( mControls.mDrawParticles)
			{
				for (int i=0; i<40; i++)
				{
					Vec2f new_pos = pos*Vec2f(getWindowSize()) + Rand::randVec2f() * 50;
					ofColor color = mSelectedImage->getColor(new_pos.x, new_pos.y);
					mParticleSystem.addParticle(new_pos, color);

					Color drawColor(
						((float)color.r / 255.0f), 
						((float)color.g / 255.0f), 
						((float)color.b / 255.0f));
					mFluidSolver.addColorAtIndex(index, drawColor * colorMult);
				}
			}
		}

		if(addForce)
			mFluidSolver.addForceAtIndex(index, vel * 25);

	}
}



// Adds the currently selected cluster to the fluid sim
void msaFluidParticlesApp::addClusterToFluid()
{
	int cluster = mControls.getClusterIndex();
	vector<PixelIndex> indices;
	mSelectedImage->getClusterIndices(cluster, mControls.mEmitAmount, indices);

	// Signal that we are starting to receive a batch
	mParticleSystem.setIsReceivingCluster(true);

	float fluid_alpha = mControls.mAlphaFluid;

	// Iterate over all the Pixel Indices and add
	for(vector<PixelIndex>::iterator it = indices.begin(); it != indices.end(); it++)
	{
		// Calculate relative values
		float rx = (float)it->x / (float)getWindowSize().x;
		float ry = (float)it->y / (float)getWindowSize().y;

		// Get fluid solver index
		Vec2f rel_pos(rx, ry);
		Vec2f scr_pos(it->x, it->y);

		// get fluid index
		int index = mFluidSolver.getIndexForPos(rel_pos);

		// Get the color
		ofColor color = mSelectedImage->getColor(it->x, it->y);

		// Create a drawcolor
		Color drawColor(
			((float)color.r / 255.0f), 
			((float)color.g / 255.0f), 
			((float)color.b / 255.0f));

		// Add the particle
		mParticleSystem.addParticle(scr_pos, color);

		// Add the color
		mFluidSolver.addColorAtIndex(index, drawColor *  mControls.mFluidAlphaScale * mControls.mAlphaFluid);
	}

	// Signal that we are done receiving
	mParticleSystem.setIsReceivingCluster(false);
}



void msaFluidParticlesApp::update()
{
	// Set the correct image and vector map, storting the current one
	if (mVectorIndex != mControls.getVectorIndex())
	{
		mSelectedVectorField = &(mImageVectors[mControls.getVectorIndex()]);
		mVectorIndex = mControls.getVectorIndex();
	}
	
	if (mImageIndex != mControls.getImageIndex())
	{
		mSelectedImage = &(mImageTextures[mControls.getImageIndex()]);
		mControls.setMaxClusters(mSelectedImage->getClusterCount());
		mImageIndex = mControls.getImageIndex();
	}

	// See if the fluid needs to resized
	if(mControls.getResetFluid()) 	
	{
		mFluidSolver.setSize(mControls.mFluidCellsX, mControls.mFluidCellsX / getWindowAspectRatio() );
		mFluidDrawer.setup(&mFluidSolver);
	}

	// See if the particles need to be reset
	if(mControls.getResetParticles())
		mParticleSystem.reset();


	// Update the bpm tapper
	mAutomator->update();


	// Emit a cluster if so
	if(mControls.getEmitCluster())
		addClusterToFluid();

	//--------------------------------------------------------------------
	
	// Only add vectors once in a while..
	if(ofGetFrameNum() % FRAME_INTERVAL == 0)
	{
		float x, y;
		const ofVec2f* vec;
		Vec2f current_position;
		const std::vector<ofVec2f>* vectors = mSelectedVectorField->getVectors();

		// Get deltax and deltay
		float dn = mControls.mVelNormScale  * MAX_NORMALIZED;
		float dw = mControls.mVelWeighScale * MAX_WEIGHTED;

		for(int i=0; i < vectors->size(); i++)
		{
			vec = mSelectedVectorField->getValueAt(i);

			// Get the current color
			mSelectedVectorField->vectorToScreen(i, x, y);
			current_position = Vec2f(x,y);
			float density(mFluidSolver.getColorAtPos(current_position).length());

			// Calculate update
			float x = vec->x * (dn + (dw*density));
			float y = vec->y * (dn + (dw*density));

			addToFluid(current_position, Vec2f(x, y),false, true);
		}
	}

	// Update the fluid solver step
	mFluidSolver.update();
}



void msaFluidParticlesApp::draw()
{

	// Draw the image
	if(mControls.mDrawImage)
		mSelectedImage->drawImage(mControls.mAlphaImage);

	// Draws the particles
	if( mControls.mDrawParticles)
		mParticleSystem.updateAndDraw( mControls.mDrawFluid);

	// Draw the fluid
	glColor4f(1.0f,1.0f,1.0f,1.0f);
	if( mControls.mDrawFluid) 
	{
		mFluidDrawer.draw(0, 0, getWindowWidth(), getWindowHeight());
	}

	// Draws the image vectors
	if (mControls.mDrawImageVectors)
		mSelectedVectorField->draw();

	
	// Draws the overlay
	if(mControls.mShowLogo)
	{
		// Draw the nachtwerk overlay
		ofEnableAlphaBlending();	
		glColor4f(1.0f, 1.0f, 1.0f, mControls.mAlphaLogo);
		mDjImages[mControls.getOverlayIndex()].draw(0,0,getWindowWidth(),getWindowHeight());
		glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
		ofDisableAlphaBlending();
	}

#ifdef USE_GUI 
	gui.draw();
#endif
}



void msaFluidParticlesApp::windowResized(int w, int h) 
{
	
	// Set the new window size for our particle system
	mParticleSystem.setWindowSize( Vec2f( w, h ) );
	
	// Recreate all the images
	std::cout << "\nUpdating Images and Clusters!\n";
	for(std::vector<ImgTexture>::iterator it = mImageTextures.begin(); it != mImageTextures.end(); ++it)
	{
		it->updateImage(w,h);
		it->updateClusters(w,h);
	}

	// Recreate all the vector image data
	std::cout << "\nUpdating Vector Fields...!\n";
	for(std::vector<ImgVectorField>::iterator it = mImageVectors.begin(); it != mImageVectors.end(); ++it)
		it->createPolyMesh(w, h);
}



void msaFluidParticlesApp::keyPressed  (int key)
{ 
	// Sets the midi port
	if ((key >= 48) && (key <= 57))
	{
		// Figure out the number that got pressed
		int channel = key - 48;
		std::cout << "\nSwitching to channel: " << channel << "\n";
		
		// If the device that it points to is either the UC or APC, change the midi input channel
		// If there is no device it points to, assume its the output port for the APC (hackish)
		if(mSelectedMidiDevice == mAPCMidiController)
		{
			mAPCPort = channel;
			mMidiIn.closePort();
			mMidiIn.openPort(mAPCPort);
			mAPCMidiController->mBoundMidiPort = mAPCPort;
			cout << "SELECTED PORT: " << channel << " FOR DEVICE: " << mSelectedMidiDevice->mDeviceName << "\n";
		}
		else if(mSelectedMidiDevice == mUCMidiController)
		{
			mUCPort = channel;
			mMidiIn2.closePort();
			mMidiIn2.openPort(mUCPort);
			mUCMidiController->mBoundMidiPort = mUCPort;
			cout << "SELECTED PORT: " << channel << " FOR DEVICE: " << mSelectedMidiDevice->mDeviceName << "\n";
		}
		else if(mSelectedMidiDevice == NULL)
		{
			mAPCOutPort = channel;
			mAPCMidiController->setOutMidiPort(channel);
		}
	}

	switch(key) 
	{
		// Toggle full screen!
		case 'f':
			ofToggleFullscreen();
			break;
		// Get iterations
		case 'b':
			{
				Timer timer;
				const int ITERS = 3000;
				timer.start();
				for( int i = 0; i < ITERS; ++i ) mFluidSolver.update();
				timer.stop();
				cout << ITERS << " iterations took " << timer.getSeconds() << " seconds." << std::endl;
			}
			break;
		// Update bpm counter
		case 32:
			{
				mAutomator->getBPMDevice()->tap();
			}
			break;
		// Select the upc 16
		case 'u':
			{
				mSelectedMidiDevice = mUCMidiController;
				cout << "SELECTED MIDI DEVICE: " << mSelectedMidiDevice->mDeviceName << "\n";
			}
			break;
		// Select the apc 20 midi device
		case 'a':
			{
				mSelectedMidiDevice = mAPCMidiController;
				cout << "SELECTED MIDI DEVICE: " << mSelectedMidiDevice->mDeviceName << "\n";
			}
			break;
		// When there is no device assigned, the output on the APC will be set (quick hack)
		case 'o':
			{
				mSelectedMidiDevice = NULL;
				cout << "SELECTED OUTPUT DEVICE: TRUE\n";
			}
			break;
	}
}


//--------------------------------------------------------------
void msaFluidParticlesApp::mouseMoved(int x, int y ){
	Vec2f eventPos = Vec2f(x, y);
	Vec2f mouseNorm = Vec2f( eventPos) / getWindowSize();
	Vec2f mouseVel = Vec2f( eventPos - pMouse ) / (getWindowSize()*25);
	addToFluid( mouseNorm, mouseVel, true, true );
	pMouse = eventPos;
}

void msaFluidParticlesApp::mouseDragged(int x, int y, int button) {
	Vec2f eventPos = Vec2f(x, y);
	Vec2f mouseNorm = Vec2f( eventPos ) / getWindowSize();
	Vec2f mouseVel = Vec2f( eventPos - pMouse ) / getWindowSize();
	addToFluid( mouseNorm, mouseVel, false, true );
	pMouse = eventPos;
}