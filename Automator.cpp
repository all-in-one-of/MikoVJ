#include "Automator.h"
#include <math.h>

// Constructor
Automator::Automator(FluidControls* inFLuidControls)
{
	mFluidController = inFLuidControls;
	mIsEnabled = false;
	int mPreviousTime = 0;

	// The Cycle intervals
	mImageRotInterval =			256;
	mVectorRotInterval =		12;
	mClusterRotInterval =		4;
	mEmitInterval =				4;
	mParticleSpeedRotInterval = 4;
	mParticleSizeRotInterval =	4;

	mMaxParticleSteps = 24;

	mMinRandParticleSteps = 10;
	mMaxRandParticleSteps = 15;

	// If that part is automated
	mVectorEnabled =		true;
	mImageEnabled =			true;
	mClusterEnabled =		true;
	mParticleSpeedEnabled = true;
	mParticleSizeEnabled =	true;
}



// Destructor is empty
Automator::~Automator()
{};



// Updates the controls
void Automator::update()
{
	// First update the bpm device
	mBPMDevice.update();

	// Return if we don't have to do something
	if (!mIsEnabled)
		return;

	// Current Beat time rounded
	int ctime = (int)mBPMDevice.beatTime();

	// Make sure time has changed (obviously)
	bool diff_time = ctime != mPreviousTime;

	// Automate emission
	if(diff_time && ctime % mEmitInterval == 0)
	{
		mFluidController->setEmitCluster(true);
	}

	// Automate image rotation
	if(mImageEnabled && diff_time && ctime % mImageRotInterval == 0)
	{
		mFluidController->setImageIndex(ofRandom(0,mFluidController->getMaxImages()));
		std::cout << "SWITCHING IMAGE" << mFluidController->getImageIndex() <<"\n";
	}

	// Automate cluster rotation
	if(mClusterEnabled && diff_time && ctime % mClusterRotInterval == 0)
	{
		mFluidController->setClusterIndex(ofRandom(0, mFluidController->getMaxClusters()));
				std::cout << "SWITCHING CLUSTER: " << mFluidController->getClusterIndex() << "\n";
	}

	// Automate vector rotation
	if(mVectorEnabled && diff_time && ctime % mVectorRotInterval == 0)
	{
		mFluidController->setVectorIndex(ofRandom(0, mFluidController->getMaxVectorFields()));
		std::cout << "SWITCHING VECTOR FIELD: " << mFluidController->getVectorIndex() << "\n";
	}

	// Automate particle speed rotations
	if(mParticleSpeedEnabled && diff_time && ctime % mParticleSpeedRotInterval == 0)
	{
		float val = ofRandom(0.0f,1.0f);
		val -= fmod(val, 0.2f);
		val += 0.2;
		mFluidController->mParticleSpeed = val;

		std::cout << "SWITCHING PARTICLE SPEED: " << mFluidController->mParticleSpeed << "\n";
	}

	if(mParticleSizeEnabled && diff_time && ctime % mParticleSizeRotInterval == 0)
	{
		// Get a new particle size
		float to_val = ofRandom(0.0f, 1.0f);
		to_val -= fmod(to_val, 0.1f);
		mToParticleSize = to_val + 0.1;

		// Calculate the difference with the current one
		float diff = mToParticleSize - mFluidController->getParticleScale();

		// Set the stepping
		mMaxParticleSteps = ofRandom(mMinRandParticleSteps,mMinRandParticleSteps);
		mParticleStepSize = diff / (float)mMaxParticleSteps;

		// Reset the steps
		mCurrentParticleStep = 0;

		std::cout << "NEW PARTICLE SIZE: " << mToParticleSize << " WITH STEP: " << mParticleStepSize << "\n";
	}
	// See if we need to adjust the particle size based on the steps
	if(mParticleSizeEnabled && mCurrentParticleStep < mMaxParticleSteps)
	{
		mCurrentParticleStep += 1;
		mFluidController->setParticleScale(mFluidController->getParticleScale() + mParticleStepSize);
	}

	mPreviousTime = ctime;
}