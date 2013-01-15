#include "FluidMidiMapper.h"
#include "MidiBindings.h"
#include <iostream>
#include "ofMath.h"
#include <math.h>
#include "Utils.h"

// Constructor
FluidMidiMapper::FluidMidiMapper(FluidControls* inControls, Automator* inAutomator)
{
	mControls = inControls;
	mAutomator = inAutomator;
}



// Destructor
FluidMidiMapper::~FluidMidiMapper()
{}



// Called when we need to update the controls
void FluidMidiMapper::updateFluidControls(const ofxMidiMessage& inMidiMessage)
{
	// First get our midi control and see if it's assigned
	MidiControls control = getMidiBinding(inMidiMessage);
	if (control == NONE)
	{
		//std::cout<< "Unmapped Control tapped: " << inMidiMessage.control << "\n";
		return;
	}

	// Now act on what we got
	switch (control)
	{
		case RESIZEFLUID:
			mControls->setResetFluid(bool(inMidiMessage.value));
			std::cout << "RESIZE FLUID: TRUE"; 
			break;

		case FLUIDCELLS:
			mControls->mFluidCellsX = inMidiMessage.value;
			std::cout << "FLUID CELLS: " << mControls->mFluidCellsX << "\n";
			break;

		case DRAWFLUID:
			mControls->mDrawFluid = valueToBool(inMidiMessage.value);
			std::cout << "DRAW FLUID: " << mControls->mDrawFluid << "\n";
			break;

		case DRAWPARTICLES:
			mControls->mDrawParticles = inMidiMessage.value;
			std::cout << "DRAW PARTICLES: " << mControls->mDrawParticles << "\n";
			break;

		case DRAWIMAGEVECTORS:
			mControls->mDrawImageVectors = inMidiMessage.value;
			std::cout << "DRAW IMAGE VECTORS: " << mControls->mDrawImageVectors << "\n";
			break;

		case SELECTIMAGE:
			mControls->setImageIndex(inMidiMessage.value);
			std::cout << "SELECTED IMAGE: " << mControls->getImageIndex() << "\n";
			break;

		case SELECTCLUSTER:
			mControls->setClusterIndex(inMidiMessage.value);
			std::cout << "SELECTED CLUSTER: " << mControls->getClusterIndex()<< "\n";
			break;

		case SELECTVECTOR:
			mControls->setVectorIndex(inMidiMessage.value);
			std::cout << "SELECTED VECTOR MAP: " << mControls->getVectorIndex() << "\n";
			break;

		case DRAWIMAGE:
			mControls->mDrawImage = valueToBool(inMidiMessage.value);
			std::cout << "DRAW PHOTO IMAGE: " << mControls->mDrawImage << "\n";
			break;

		case ALPHAIMAGE:
			mControls->mAlphaImage = pow((float)inMidiMessage.value/127.0f, 2);
			std::cout << "ALPHA IMAGE: " << mControls->mAlphaImage << "\n";
			break;

		case ALPHAPARTICLE:
			mControls->mAlphaParticles = pow((float)inMidiMessage.value/127.0f, 3);
			std::cout << "ALPHA PARTICLES: " << mControls->mAlphaParticles << "\n";
			break;

		case ALPHAFLUID:
			mControls->mAlphaFluid = pow((float)inMidiMessage.value/127.0f,2);
			std::cout << "ALPHA FLUID: " << mControls->mAlphaFluid << "\n";
			break;

		case ALPHALINES:
			mControls->mAlphaLines = pow((float)inMidiMessage.value/127.0f,2);
			std::cout << "ALPHA LINES: " << mControls->mAlphaLines << "\n";
			break;

		case VELNORMSCALE:
			mControls->mVelNormScale = pow((float)inMidiMessage.value/127.0f,2);
			std::cout << "VEL NORM SCALE: " << mControls->mVelNormScale << "\n";
			break;

		//case VELWEIGHSCALE:
		//	mControls->mVelWeighScale = pow(((float)inMidiMessage.value/127.0f),2);
		//	std::cout << "VEL WEIGTED SCALE: " << mControls->mVelWeighScale << "\n";
		//	break;

		case PARTALPHADECAY:
			{
				float da = pow((float)inMidiMessage.value/127.0f,2);
				mControls->mPartAlphaDecay = (1.0f-da) * (1.0f/200.0f);										//< TODO, da needs to be scaled appropiately
				std::cout << "PART ALPHA DECAY: " << mControls->mPartAlphaDecay << "\n";
				break;
			}
		
		case EMITCLUSTER:
			mControls->setEmitCluster((bool)inMidiMessage.value);
			std::cout << "EMIT CLUSTER: " << mControls->getClusterIndex() << "\n";
			break;
		
		case RESET:
			mControls->setResetParticles((bool)inMidiMessage.value);
			std::cout << "RESET PARTICLES: TRUE" << "\n";
			break;

		case DRAWPARTILINES:
			mControls->mDrawPartLines = (bool)inMidiMessage.value;
			std::cout << "DRAW PARTICLE LINES: " << mControls->mDrawPartLines << "\n";
			break;

		case DRAWPARTPOINTS:
			mControls->mDrawPartPoints = (bool)inMidiMessage.value;
			std::cout << "DRAW PARTICLE POINTS: " << mControls->mDrawPartPoints << "\n";
			break;

		case DRAWPARTHISTORY:
			mControls->mDrawPartHist = (bool)inMidiMessage.value;
			std::cout << "DRAW PARTICLE HISTORY: " << mControls->mDrawPartHist << "\n";
			break;

		case LINEWIDTH:
			mControls->mLineWidth = ((float)inMidiMessage.value/127.0f) * 10;
			std::cout << "LINE WIDTH: " << mControls->mLineWidth << "\n";
			break;

		case TRAILLENGTH:
			mControls->mTrailLength = ((float)inMidiMessage.value/127.0f) * 40;
			std::cout << "TRAIL LENGTH: " << mControls->mTrailLength << "\n";
			break;

		case PARTICLESIZE:
			mControls->mParticleSize = ((float)inMidiMessage.value/127.0f) * 10;
			std::cout << "PARTICLE SIZE: " << mControls->mParticleSize << "\n";
			break;

		case EMITAMOUNT:
			mControls->mEmitAmount = (int)(pow(((1.0f / 127.0f) * inMidiMessage.value),3) * 100000.0f);
			mControls->mFluidAlphaScale = ofClamp(pow(1000.0f / (float)mControls->mEmitAmount, 0.85f),0.0f,2.0f);
			std::cout << "EMISSION AMOUNT: " << mControls->mEmitAmount << "\n";
			std::cout << "FLUID ALPHA SCALE: " << mControls->mFluidAlphaScale << "\n";
			break;

		case AUTOMATION:
			mAutomator->setIsEnabled((bool)inMidiMessage.value);
			std::cout << "AUTOMATION: " << mAutomator->getIsEnabled() << "\n";
			break;

		case AUTOIMAGESPEED:
			{
				int val = (inMidiMessage.value+1) * 8;
				iClamp(4,128*10, val);
				mAutomator->mImageRotInterval = val;
				std::cout << "IMAGE INTERVAL: " << mAutomator->mImageRotInterval << "\n";
				break;
			}

		case AUTOVECTORSPEED:
			{
				int val = inMidiMessage.value;
				iClamp(0, 48, val);
				mAutomator->mVectorRotInterval = val;
				std::cout << "VECTOR INTERVAL: " << mAutomator->mVectorRotInterval << "\n";
				break;
			}

		case AUTOCLUSTERSPEED:
			{
				int val = inMidiMessage.value;
				iClamp(1, 24, val);
				mAutomator->mClusterRotInterval = val;
				std::cout << "CLUSTER INTERVAL: " << mAutomator->mClusterRotInterval << "\n";
				break;
			}

		case AUTOIMAGEENABLE:
			mAutomator->mImageEnabled = (bool)inMidiMessage.value;
			std::cout << "AUTO IMAGE: " << mAutomator->mImageEnabled << "\n";
			break;

		case AUTOVECTORENABLE:
			mAutomator->mVectorEnabled = (bool)inMidiMessage.value;
			std::cout << "AUTO VECTOR: " << mAutomator->mVectorEnabled << "\n";
			break;

		case AUTOCLUSTERENABLE:
			mAutomator->mClusterEnabled = (bool)inMidiMessage.value;
			std::cout << "AUTO CLUSTER: " << mAutomator->mClusterEnabled << "\n";
			break;

		case AUTOEMITSPEED:
			{
				int val = inMidiMessage.value;
				iClamp(1,127, val);
				mAutomator->mEmitInterval = val;
				std::cout << "EMIT INTERVAL: " << mAutomator->mEmitInterval << "\n";
				break;
			}

		case ALPHALOGO:
			mControls->mAlphaLogo = ((float)inMidiMessage.value/127.0f);
			std::cout << "ALPHA LOGO: " << mControls->mAlphaLogo << "\n";
			break;

		case ENABLEALPHALOGO:
			mControls->mShowLogo = (bool)inMidiMessage.value;
			std::cout << "SHOW LOGO: " << mControls->mShowLogo << "\n";
			break;

		case OVERLAYSELECT:
			mControls->setOverlayIndex((int)inMidiMessage.value);
			std::cout << "SELECTED OVERLAY: " << mControls->getOverlayIndex() << "\n";
			break;
	}
}



bool FluidMidiMapper::valueToBool(const int& inValue)
{
	return (inValue > MINIMUM_MIDI_VALUE);
}



// Returns the midi map based on the midi message
MidiControls FluidMidiMapper::getMidiBinding(const ofxMidiMessage& inMidiMessage)
{
	MidiControls control = MidiBindings::GetInstance()->getMidiControl(inMidiMessage.control);
	return control;
}