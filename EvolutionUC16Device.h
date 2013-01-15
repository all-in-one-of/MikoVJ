#ifndef EVOUC16MAP
#define EVOUC16MAP

#include "MidiMap.h"
#include "FluidControls.h"
#include "ofxMidiMessage.h"
#include <exception>
#include <string>
#include "ofxMidi.h"
#include "Automator.h"
#include <ctime>
#include "Utils.h"
#include <math.h>
#include "MidiDevice.h"

// The UC 16 Midi Device
class EvolutionUC16MidiDevice : public MidiDevice
{
	// Only has it's own constructor to set up the member variables
public:
	EvolutionUC16MidiDevice (int inMidiPort, int inOutMidiPort, FluidControls* inControls, Automator* inAutomator);
};




class EvolutionUC16MidiMap : public MidiMap
{
public:
	// Constructor calls the map constructor
	EvolutionUC16MidiMap ();

protected:
	// Builds the midi map
	virtual void constructMap();
};



/*
 * The UC16 Actions
 */

class ActionSetAutoEmitSpeed : public MidiAction
{
public:
	ActionSetAutoEmitSpeed()
	{
		mName = "Set Auto Emission Rate";
	}

	virtual void doAction(FluidControls* inControls, Automator* inAutomator, const ofxMidiMessage& inMessage, ofxMidiOut& inMidiOut)
	{
		// Sample Range
		float val = (float)inMessage.value + 1.0f;
		val /= 8.0f;

		// Get the remainder
		float remain = fmod(val, 2.0f);
		val -=remain;

		// Clamp to 1
		fClamp(1.0f,16.0f,val);

		// Scale the particle decay rate by the rotation interval		
		float df = pow(1.0f/val, 1.75f);
		df *= 0.02;

		inControls->mPartAlphaDecay = df;
		std::cout << "ALPHA DECAY RATE: " << inControls->mPartAlphaDecay << "\n";

		inAutomator->mEmitInterval = val;
		inAutomator->mClusterRotInterval = val;
		std::cout << "EMIT INTERVAL: " << inAutomator->mEmitInterval << "\n";
	}
};



class ActionSetAutoImageSpeed : public MidiAction
{
public:
	ActionSetAutoImageSpeed()
	{
		mName = "Set Auto Image Rate";
	}

	virtual void doAction(FluidControls* inControls, Automator* inAutomator, const ofxMidiMessage& inMessage, ofxMidiOut& inMidiOut)
	{
		// Sample Range
		float val = (float)inMessage.value + 1.0f;
		val *= 8.0f;

		// Get the remainder
		float remain = fmod(val, 4.0f);
		val -=remain;

		// Clamp to 1
		fClamp(1.0f,128.0f*8.0f,val);
		inAutomator->mImageRotInterval = val;
		std::cout << "IMAGE INTERVAL: " << inAutomator->mImageRotInterval << "\n";
	}
};



class ActionSetAutoClusterSpeed : public MidiAction
{
public:
	ActionSetAutoClusterSpeed()
	{
		mName = "Set Auto Cluster Rate";
	}

	virtual void doAction(FluidControls* inControls, Automator* inAutomator, const ofxMidiMessage& inMessage, ofxMidiOut& inMidiOut)
	{
		// Sample Range
		float val = (float)inMessage.value + 1.0f;
		val /= 8.0f;

		// Get the remainder
		float remain = fmod(val, 2.0f);
		val -=remain;

		// Clamp to 1
		fClamp(1.0f,16.0f,val);

		inAutomator->mClusterRotInterval = val;
		std::cout << "CLUSTER INTERVAL: " << inAutomator->mClusterRotInterval << "\n";
	}
};



class ActionSetAutoVectorSpeed : public MidiAction
{
public:
	ActionSetAutoVectorSpeed()
	{
		mName = "Set Auto Vector Rate";
	}

	virtual void doAction(FluidControls* inControls, Automator* inAutomator, const ofxMidiMessage& inMessage, ofxMidiOut& inMidiOut)
	{
		// Sample Range
		float val = (float)inMessage.value + 1.0f;
		val /= 2.0f;

		// Get the remainder
		float remain = fmod(val, 2.0f);
		val -=remain;

		// Clamp to 1
		fClamp(1.0f,64.0f,val);
		inAutomator->mVectorRotInterval = val;
		std::cout << "VECTOR INTERVAL: " << inAutomator->mVectorRotInterval << "\n";
	}
};



class ActionSetAutoParticleSpeed : public MidiAction
{
public:
	ActionSetAutoParticleSpeed()
	{
		mName = "Set Auto Particle Rate";
	}

	virtual void doAction(FluidControls* inControls, Automator* inAutomator, const ofxMidiMessage& inMessage, ofxMidiOut& inMidiOut)
	{
		// Sample Range
		float val = (float)inMessage.value + 1.0f;
		val /= 16.0f;

		// Get the remainder
		float remain = fmod(val, 2.0f);
		val -=remain;

		// Clamp to 1
		fClamp(1.0f,8.0f,val);

		inAutomator->mParticleSpeedRotInterval = val;
		std::cout << "PARTICLE SPEED INTERVAL: " << inAutomator->mParticleSpeedRotInterval << "\n";
	}
};



class ActionSetAutoParticleSize : public MidiAction
{
public:
	ActionSetAutoParticleSize()
	{
		mName = "Set Auto Particle Size";
	}

	virtual void doAction(FluidControls* inControls, Automator* inAutomator, const ofxMidiMessage& inMessage, ofxMidiOut& inMidiOut)
	{
		// Sample Range
		float val = (float)inMessage.value + 1.0f;
		val /= 8.0f;

		// Get the remainder
		float remain = fmod(val, 2.0f);
		val -=remain;

		// Clamp to 1
		fClamp(1.0f,16.0f,val);

		// Set the intervals
		switch ((int)val)
		{
		case 1:
			{
				inAutomator->mMaxRandParticleSteps = 7;
				inAutomator->mMinRandParticleSteps = 4;
			}
			break;
		case 2:
			{
				inAutomator->mMaxRandParticleSteps = 12;
				inAutomator->mMinRandParticleSteps = 7;
			}
			break;
		default:
			{
				inAutomator->mMinRandParticleSteps = 12;
				inAutomator->mMaxRandParticleSteps = 20;
			}
			break;
		}

		inAutomator->mParticleSizeRotInterval = val;
		std::cout << "PARTICLE SIZE INTERVAL: " << inAutomator->mParticleSizeRotInterval << "\n";
	}
};


#endif