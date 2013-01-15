#ifndef AUTOMATOR
#define AUTOMATOR

#include "FluidControls.h"
#include "MSABPMTapper.h"

/*
 * The automator automates the fluid controls,
 * Which are referenced throughout the system
 */

class Automator{

public:
	// Constructor
	Automator(FluidControls* inFLuidControls);

	// Destructor
	~Automator();

	inline	void setIsEnabled(bool inValue)			{ mIsEnabled = inValue; }
	inline	bool getIsEnabled()						{ return mIsEnabled; }
	inline	MSA::BPMTapper* getBPMDevice()			{ return &mBPMDevice; }

	// Some values that can be set
	int		mImageRotInterval;
	int		mVectorRotInterval;
	int		mClusterRotInterval;
	int		mParticleSpeedRotInterval;
	int		mParticleSizeRotInterval;
	int		mEmitInterval;

	bool	mVectorEnabled;
	bool	mImageEnabled;
	bool	mClusterEnabled;
	bool	mParticleSpeedEnabled;
	bool	mParticleSizeEnabled;

	int mMinRandParticleSteps;					//< The min cycles it should take to change size
	int mMaxRandParticleSteps;					//< The max cycles it should take to change size

	void	update();

private:
	FluidControls*	mFluidController;
	bool			mIsEnabled;
	MSA::BPMTapper	mBPMDevice;

	// Members for controlling particle size
	float mToParticleSize;
	float mMaxParticleSteps;
	float mParticleStepSize;
	float mCurrentParticleStep;


	// Some members to check the mod op to
	int mPreviousTime;
};

#endif