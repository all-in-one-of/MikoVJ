#include "FluidControls.h"
#include "Utils.h"

// Constructor, set all the controls as a start
// By default only one image is allowed
FluidControls::FluidControls()
{
	// DEFAULTS! Should be sync with midi device
	mFluidCellsX = 100;
	mResizeFluid = true;
	mDrawFluid = true;
	mDrawParticles = true;
	mDrawImageVectors = false;
	mDrawImage = 1;
	mSelectedImage = 0;
	mSelectedVectorField = 0;
	mSelectedCluster = 0;
	mAlphaFluid  = 1.0f;
	mAlphaParticles = 1.0f;
	mAlphaLines = 0.15f;
	mAlphaImage = 1.0f;
	mVelNormScale = 0.25f;
	mVelWeighScale = 0.25f;
	mPartAlphaDecay = 0.0025;
	mReset = false;
	mEmitCluster = false;
	mDrawPartLines = true;
	mDrawPartHist = true;
	mDrawPartPoints = true;
	mLineWidth = 1.0f;
	mTrailLength = 10.0f;
	mParticleSize = 1.0f;
	mParticleSpeed = 1.0f;
	mParticleMult = 10.0f;
	mParticleScale = 1.0f;
	mEmitAmount = 1000;
	mFluidAlphaScale = 0.6f;
	mAlphaLogo = 0.0f;
	mShowLogo = true;
	mSelectedOverlay = 0;

	mMaxImages = 1;
	mMaxClusters = 1; 
}



// Destructor
FluidControls::~FluidControls()
{}



// Helper methods, clamping values based on local max
void FluidControls::setImageIndex(int inIndex)
{
	iClamp(0, mMaxImages-1, inIndex);
	mSelectedImage = inIndex;
}

void FluidControls::setVectorIndex(int inIndex)
{
	iClamp(0, mMaxVectorFields-1, inIndex);
	mSelectedVectorField = inIndex;
}

void FluidControls::setOverlayIndex(int inIndex)
{
	iClamp(0, mMaxOverlays-1, inIndex);
	mSelectedOverlay = inIndex;
}

void FluidControls::setClusterIndex(int inIndex)
{
	iClamp(0, mMaxClusters-1, inIndex);
	mSelectedCluster = inIndex;
}

// Returns if the cluster should be emitted
bool FluidControls::getEmitCluster()
{
	if(mEmitCluster)
	{
		mEmitCluster = false;
		return true;
	}
	return mEmitCluster;
}

// Returns if the sim should be reset
bool FluidControls::getResetParticles()
{
	if(mReset)
	{
		mReset = false;
		return true;
	}
	return mReset;
}


// Returns if the sim needs to be reset
bool FluidControls::getResetFluid()
{
	if(mResizeFluid)
	{
		mResizeFluid = false;
		return true;
	}
	return mResizeFluid;
}






