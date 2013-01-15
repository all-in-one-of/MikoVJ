#ifndef MIDIACTION
#define MIDIACTION

#include "FluidControls.h"
#include "ofxMidiMessage.h"
#include <exception>
#include <string>
#include "ofxMidi.h"
#include "Automator.h"
#include <ctime>
#include "Utils.h"
#include <math.h>

/*
 * Defined this enum here, but would rather have it in the midi device,
 * But for some reason that gives me a cycling dependency
 */

/*
enum APCCOLORCODES
{
	OFF = 0,
	GREEN,
	GREENFLASH,
	RED,
	REDFLASH,
	ORANGE,
	ORANGEFLASH
};
*/

/*
 * Thrown when the action isn't implemented
 */

class ActionNotImplementedException : public std::exception
{
	virtual const char* what() const throw()
	{
		return "No Action Implemented";
	}
};

/*
 * A midi action is performed on the control that is given to the action
 * This is the abstraction, implementation should override the action method
 * The action should always be given the controls to act on and the message that was received
 */

/*
 * Abstract Action
 */

class MidiAction
{
public:
	// Constructor
	MidiAction();

	// Destructor
	~MidiAction();

	// Name of the action
	std::string mName;

	// Last time action was performed
	int mLastActionTime;

	// Performs the action, override with your own midi bound action
	virtual void doAction(FluidControls* inControls, Automator* inAutomator, const ofxMidiMessage& inMessage, ofxMidiOut& inMidiOut);

private:
	static ActionNotImplementedException mException;

protected:
	
	// Allows one to set the current action time
	void setActionTime();

	// Gets the current time for comparison
	int getCurrentTime();
};



/*
 * Concrete Action Implementations
 * These can be bound to a midi slot (MidiIndex) in a MidiMap object
 */

/*
class ActionChangeVectorField: public MidiAction
{
public:
	int mMinCount;
	int mMaxCount;

	ActionChangeVectorField()
	{
		mName = "Change Vector Field";
		mMinCount = 0;
		mMaxCount = 0;
	}

	virtual void doAction(FluidControls* inControls, Automator* inAutomator, const ofxMidiMessage& inMessage, ofxMidiOut& inMidiOut)
	{

		// The control it receives the message from maps both ways, positive and negative.
		// Where negative is =< 127. For that reason we have to construct two paths.
		// Internally a counter is used to slow the switch process down. (oop goodness right there)
		if (inMessage.value > 0 && inMessage.value < 10)
		{
			if(mMaxCount == 15)
			{
				if(inControls->getVectorIndex() + 1 == inControls->getMaxVectorFields())
				{
					inControls->setVectorIndex(0);
				}
				else
				{
					inControls->setVectorIndex(inControls->getVectorIndex() + 1);
				}
				mMaxCount = 0;
			}
			else
			{
				mMaxCount +=1;
			}
		}
		else
		{
			if(mMinCount == 15)
			{
				if(inControls->getVectorIndex() == 0)
				{
					inControls->setVectorIndex(inControls->getMaxVectorFields()-1);
				}
				else
				{
					inControls->setVectorIndex(inControls->getVectorIndex() - 1);
				}
				mMinCount = 0;
			}
			else
			{
				mMinCount +=1;
			}
		}

		std::cout << "VECTOR MAP: " << inControls->getVectorIndex() << "\n";
	}
};



// Changes the alpha of the overlay
class ActionChangeAlphaLogo : public MidiAction
{
public:
	ActionChangeAlphaLogo()			
	{
		mName = "Change Alpha Overlay";
	}


	virtual void doAction(FluidControls* inControls, Automator* inAutomator, const ofxMidiMessage& inMessage, ofxMidiOut& inMidiOut)
	{
		inControls->mAlphaLogo = ((float)inMessage.value/127.0f);
		std::cout << "ALPHA LOGO: " << inControls->mAlphaLogo << "\n";
	}
};


// Enables the overlay
class ActionEnableAlphaLogo : public MidiAction
{
public:

	ActionEnableAlphaLogo()			{ mName = "Enable Overlay"; }

	virtual void doAction(FluidControls* inControls, Automator* inAutomator,const ofxMidiMessage& inMessage, ofxMidiOut& inMidiOut)
	{
		if (inMessage.status == MIDI_NOTE_ON)
			inControls->mShowLogo = true;
		else
			inControls->mShowLogo = false;

		std::cout << "SHOW LOGO: " << inControls->mShowLogo << "\n";
	}
};



// Enables the photo image
class ActionEnableImage : public MidiAction
{
public:

	ActionEnableImage()			{ mName = "Enable Image"; }

	virtual void doAction(FluidControls* inControls, Automator* inAutomator,const ofxMidiMessage& inMessage, ofxMidiOut& inMidiOut)
	{
		if (inMessage.status == MIDI_NOTE_ON)
			inControls->mDrawImage = true;
		else
			inControls->mDrawImage = false;

		std::cout << "DRAW PHOTO IMAGE: " << inControls->mDrawImage<< "\n";
	}
};



// Enables the overlay
class ActionAlphaImage : public MidiAction
{
public:

	ActionAlphaImage()			{ mName = "Alpha Image"; }

	virtual void doAction(FluidControls* inControls, Automator* inAutomator,const ofxMidiMessage& inMessage, ofxMidiOut& inMidiOut)
	{
		inControls->mAlphaImage = ((float)inMessage.value/127.0f);;
		std::cout << "ALPHA IMAGE: " << inControls->mAlphaImage<< "\n";
	}
};



// Enables the overlay
class ActionEnableParticles : public MidiAction
{
public:

	ActionEnableParticles()			{ mName = "Enable Particles"; }

	virtual void doAction(FluidControls* inControls, Automator* inAutomator,const ofxMidiMessage& inMessage, ofxMidiOut& inMidiOut)
	{
		if (inMessage.status == MIDI_NOTE_ON)
			inControls->mDrawParticles = true;
		else
			inControls->mDrawParticles = false;

		std::cout << "DRAW PARTICLES: " << inControls->mDrawParticles<< "\n";
	}
};



// Enables the overlay
class ActionAlphaParticle : public MidiAction
{
public:

	ActionAlphaParticle()			{ mName = "Alpha Particles"; }

	virtual void doAction(FluidControls* inControls, Automator* inAutomator,const ofxMidiMessage& inMessage, ofxMidiOut& inMidiOut)
	{
		inControls->mAlphaParticles = ((float)inMessage.value/127.0f);;
		std::cout << "ALPHA PARTICLES: " << inControls->mAlphaParticles<< "\n";
	}
};



class ActionEnableFluid : public MidiAction
{
public:

	ActionEnableFluid()			{ mName = "Enable Fluid"; }

	virtual void doAction(FluidControls* inControls,Automator* inAutomator, const ofxMidiMessage& inMessage, ofxMidiOut& inMidiOut)
	{
		if (inMessage.status == MIDI_NOTE_ON)
			inControls->mDrawFluid = true;
		else
			inControls->mDrawFluid = false;

		std::cout << "DRAW FLUID: " << inControls->mDrawParticles<< "\n";
	}
};



// Enables the overlay
class ActionAlphaFluid : public MidiAction
{
public:

	ActionAlphaFluid()			{ mName = "Alpha Fluid"; }

	virtual void doAction(FluidControls* inControls,Automator* inAutomator, const ofxMidiMessage& inMessage, ofxMidiOut& inMidiOut)
	{
		inControls->mAlphaFluid = ((float)inMessage.value/127.0f);
		std::cout << "ALPHA FLUID: " << inControls->mAlphaFluid << "\n";
	}
};



class ActionEnablePartHistory : public MidiAction
{
public:

	ActionEnablePartHistory()			{ mName = "Enable Part History"; }

	virtual void doAction(FluidControls* inControls,Automator* inAutomator, const ofxMidiMessage& inMessage, ofxMidiOut& inMidiOut)
	{
		if (inMessage.status == MIDI_NOTE_ON)
			inControls->mDrawPartHist = true;
		else
			inControls->mDrawPartHist = false;

		std::cout << "DRAW HISTORY: " << inControls->mDrawPartLines << "\n";
	}
};



// Enables the overlay
class ActionPartHistoryAlpha : public MidiAction
{
public:

	ActionPartHistoryAlpha()			{ mName = "Alpha Part History"; }

	virtual void doAction(FluidControls* inControls, Automator* inAutomator,const ofxMidiMessage& inMessage, ofxMidiOut& inMidiOut)
	{
		inControls->mAlphaLines = pow((float)inMessage.value/127.0f,2);
		std::cout << "ALPHA HISTORY: " << inControls->mAlphaLines<< "\n";
	}
};



class ActionEnableLines : public MidiAction
{
public:

	ActionEnableLines()			{ mName = "Enable Part Lines"; }

	virtual void doAction(FluidControls* inControls, Automator* inAutomator,const ofxMidiMessage& inMessage, ofxMidiOut& inMidiOut)
	{
		if (inMessage.status == MIDI_NOTE_ON)
			inControls->mDrawPartLines = true;
		else
			inControls->mDrawPartLines = false;

		std::cout << "DRAW LINES: " << inControls->mDrawPartLines << "\n";
	}
};



class ActionEmit : public MidiAction
{
public:

	ActionEmit()			{ mName = "Emit Particles"; }

	virtual void doAction(FluidControls* inControls, Automator* inAutomator,const ofxMidiMessage& inMessage, ofxMidiOut& inMidiOut)
	{
		if(inMessage.status == MIDI_NOTE_OFF)
		{
			inMidiOut.sendNoteOn(1,86,APCCOLORCODES::GREENFLASH);
			return;
		}

		inControls->setEmitCluster(true);
		std::cout << "EMIT CLUSTER: " << inControls->getClusterIndex()<< "\n";
	}
};



class ActionAutomate : public MidiAction
{
public:

	ActionAutomate()			
	{ 
		mName = "Automation";
	}

	virtual void doAction(FluidControls* inControls, Automator* inAutomator, const ofxMidiMessage& inMessage, ofxMidiOut& inMidiOut)
	{
		if(inMessage.status == MIDI_NOTE_ON)
			return;

		if (!inAutomator->getIsEnabled())
		{
			inAutomator->setIsEnabled(true);
			inMidiOut.sendNoteOn(8,53,APCCOLORCODES::GREENFLASH);
		}
		else
		{
			inAutomator->setIsEnabled(false);
			inMidiOut.sendNoteOn(8,53,APCCOLORCODES::RED);
		}

		setActionTime();
		std::cout << "AUTOMATION: " << inAutomator->getIsEnabled() << "\n";
	}
};



class ActionAutomateImage : public MidiAction
{
public:

	ActionAutomateImage()			
	{ 
		mName = "Automate Image Selection";
	}

	virtual void doAction(FluidControls* inControls, Automator* inAutomator, const ofxMidiMessage& inMessage, ofxMidiOut& inMidiOut)
	{
		if(inMessage.status == MIDI_NOTE_ON)
			return;

		if (!inAutomator->mImageEnabled)
		{
			inAutomator->mImageEnabled = true;
			inMidiOut.sendNoteOn(8,54,APCCOLORCODES::GREEN);
		}
		else
		{
			inAutomator->mImageEnabled = false;
			inMidiOut.sendNoteOn(8,54,APCCOLORCODES::RED);
		}

		setActionTime();
		std::cout << "AUTO IMAGE: " << inAutomator->mImageEnabled << "\n";
	}
};



class ActionAutomateParticleSize: public MidiAction
{
public:

	ActionAutomateParticleSize()			
	{ 
		mName = "Automate Particle Size";
	}

	virtual void doAction(FluidControls* inControls, Automator* inAutomator, const ofxMidiMessage& inMessage, ofxMidiOut& inMidiOut)
	{
		if(inMessage.status == MIDI_NOTE_ON)
			return;

		if (!inAutomator->mParticleSizeEnabled)
		{
			inAutomator->mParticleSizeEnabled = true;
			inMidiOut.sendNoteOn(7,55,APCCOLORCODES::GREEN);
		}
		else
		{
			inAutomator->mParticleSizeEnabled = false;
			inMidiOut.sendNoteOn(7,55,APCCOLORCODES::RED);
		}

		setActionTime();
		std::cout << "AUTO PARTICLE SIZE: " << inAutomator->mParticleSizeEnabled << "\n";
	}
};



class ActionAutoCluster: public MidiAction
{
public:

	ActionAutoCluster()			
	{ 
		mName = "Automate Image Cluster";
	}

	virtual void doAction(FluidControls* inControls, Automator* inAutomator, const ofxMidiMessage& inMessage, ofxMidiOut& inMidiOut)
	{
		if(inMessage.status == MIDI_NOTE_ON)
			return;

		if (!inAutomator->mClusterEnabled)
		{
			inAutomator->mClusterEnabled = true;
			inMidiOut.sendNoteOn(8,55,APCCOLORCODES::GREEN);
		}
		else
		{
			inAutomator->mClusterEnabled = false;
			inMidiOut.sendNoteOn(8,55,APCCOLORCODES::RED);
		}

		setActionTime();
		std::cout << "AUTO CLUSTER: " << inAutomator->mClusterEnabled<< "\n";
	}
};



class ActionAutoVector: public MidiAction
{
public:

	ActionAutoVector()			
	{ 
		mName = "Automate Image Vectors";
	}

	virtual void doAction(FluidControls* inControls, Automator* inAutomator, const ofxMidiMessage& inMessage, ofxMidiOut& inMidiOut)
	{
		if(inMessage.status == MIDI_NOTE_ON)
			return;

		if (!inAutomator->mVectorEnabled)
		{
			inAutomator->mVectorEnabled = true;
			inMidiOut.sendNoteOn(8,56,APCCOLORCODES::GREEN);
		}
		else
		{
			inAutomator->mVectorEnabled = false;
			inMidiOut.sendNoteOn(8,56,APCCOLORCODES::RED);
		}

		setActionTime();
		std::cout << "AUTO VECTOR: " << inAutomator->mVectorEnabled<< "\n";
	}
};



class ActionSelectCluster: public MidiAction
{
public:

	ActionSelectCluster()			
	{ 
		mName = "Select Cluster";
	}

	virtual void doAction(FluidControls* inControls, Automator* inAutomator, const ofxMidiMessage& inMessage, ofxMidiOut& inMidiOut)
	{
		// Set the cluster index and return on trigger
		if(inMessage.status == MIDI_NOTE_ON)
		{
			inControls->setClusterIndex(inMessage.channel - 1);
			return;
		}

		// Set the color of all cluster leds to orange
		for(int channel = 1; channel < 9; channel++)
		{
			inMidiOut.sendNoteOn(channel, 57, APCCOLORCODES::ORANGE);
		}

		// Now set the color for the selected led
		inMidiOut.sendNoteOn(inMessage.channel, inMessage.pitch, APCCOLORCODES::GREEN);
		std::cout << "SELECTED CLUSTER: " << inControls->getClusterIndex() << "\n";
	}
};



class ActionEmitAmount: public MidiAction
{
public:

	ActionEmitAmount()			
	{ 
		mName = "Emission Amount";
	}

	virtual void doAction(FluidControls* inControls, Automator* inAutomator, const ofxMidiMessage& inMessage, ofxMidiOut& inMidiOut)
	{
		inControls->mEmitAmount = (int)(pow(((1.0f / 127.0f) * inMessage.value),3) * 100000.0f);
		inControls->mFluidAlphaScale = ofClamp(pow(1000.0f / (float)inControls->mEmitAmount, 0.85f),0.0f,2.0f);
		std::cout << "EMISSION AMOUNT: " << inControls->mEmitAmount << "\n";
	}
};



class ActionParticleDecay: public MidiAction
{
public:

	ActionParticleDecay()			
	{ 
		mName = "Particle Decay";
	}

	virtual void doAction(FluidControls* inControls, Automator* inAutomator, const ofxMidiMessage& inMessage, ofxMidiOut& inMidiOut)
	{
		float da = pow((float)inMessage.value/127.0f, 1.5f);
		inControls->mPartAlphaDecay = (1.0f-da) * (1.0f/50.0f);										//< TODO, da needs to be scaled appropiately
		std::cout << "PART ALPHA DECAY: " << inControls->mPartAlphaDecay << "\n";
	}
};



class ActionShowImageVectors: public MidiAction
{
public:

	ActionShowImageVectors()			
	{ 
		mName = "Show Image Vectors";
	}

	virtual void doAction(FluidControls* inControls, Automator* inAutomator, const ofxMidiMessage& inMessage, ofxMidiOut& inMidiOut)
	{
		if(inMessage.status == MIDI_NOTE_ON)
			inControls->mDrawImageVectors = true;
		else
			inControls->mDrawImageVectors = false;

		std::cout << "DRAW IMAGE VECTORS: " << inControls->mDrawImageVectors << "\n";
	}
};



class ActionSetParticleMult: public MidiAction
{
public:

	ActionSetParticleMult()			
	{ 
		mName = "Set Particle Size Multiplier";
	}

	virtual void doAction(FluidControls* inControls, Automator* inAutomator, const ofxMidiMessage& inMessage, ofxMidiOut& inMidiOut)
	{
		// Turn all multipliers off
		for(int i=48; i<51; i++)
		{
			inMidiOut.sendNoteOff(6,i,APCCOLORCODES::OFF);
		}

		switch (inMessage.pitch)
		{
		case 48:
			inControls->setParticleMult(2.0f);
			break;
		case 49:
			inControls->setParticleMult(5.0f);
			break;
		case 50:
			inControls->setParticleMult(10.0f);
			break;
		}

		inMidiOut.sendNoteOn(6, inMessage.pitch,APCCOLORCODES::GREEN);

		std::cout << "PARTICLE SIZE MULT: " << "\n";
	}
};


class ActionSetParticleScale: public MidiAction
{
public:

	ActionSetParticleScale()			
	{ 
		mName = "Change Particle Scale";
	}

	virtual void doAction(FluidControls* inControls, Automator* inAutomator, const ofxMidiMessage& inMessage, ofxMidiOut& inMidiOut)
	{
		inControls->setParticleScale(((float)inMessage.value/127.0f));
		std::cout << "PARTICLE SCALE: " << inControls->getParticleScale() << "\n";
	}
};



class ActionSetVelocity: public MidiAction
{
public:

	ActionSetVelocity()			
	{ 
		mName = "Change Velocity";
	}

	virtual void doAction(FluidControls* inControls, Automator* inAutomator, const ofxMidiMessage& inMessage, ofxMidiOut& inMidiOut)
	{
		inControls->mVelNormScale = pow((float)inMessage.value/127.0f,2);
		inControls->mVelWeighScale = pow(((float)inMessage.value/127.0f),2);
		inControls->mParticleSpeed = (inMessage.value / 127.0f);
		std::cout << "VEL SCALE: " << inControls->mVelWeighScale << "\n";
	}
};



class ActionSelectImage: public MidiAction
{
public:

	ActionSelectImage()			
	{ 
		mName = "Change Velocity";
	}

	virtual void doAction(FluidControls* inControls, Automator* inAutomator, const ofxMidiMessage& inMessage, ofxMidiOut& inMidiOut)
	{
		// Only Set the image, 53 is the start pitch in the matrix
		if(inMessage.status == MIDI_NOTE_ON)
		{
			int image = (inMessage.pitch - 53) * 5 + inMessage.channel - 1;
			inControls->setImageIndex(image);
			return;
		}

		// Set all the images to red
		for(int channel = 1; channel < 6; channel ++)
		{
			for (int pitch=53; pitch < 57; pitch++)
			{
				inMidiOut.sendNoteOn(channel, pitch, APCCOLORCODES::RED);
			}
		}

		// Figure out what image we want to set based on the pitch and channel
		int image = (inMessage.pitch - 53) * 5 + inMessage.channel - 1;

		std::cout << "SETTING IMAGE: " << image << "\n";

		// Now set the one we selected to green
		inMidiOut.sendNoteOn(inMessage.channel, inMessage.pitch, APCCOLORCODES::GREEN);
	}
};



class ActionResetParticles: public MidiAction
{
public:

	ActionResetParticles()			
	{ 
		mName = "Reset Particles";
	}

	virtual void doAction(FluidControls* inControls, Automator* inAutomator, const ofxMidiMessage& inMessage, ofxMidiOut& inMidiOut)
	{
		if (inMessage.status == MIDI_NOTE_ON)
		{
			inControls->setResetParticles(true);
			std::cout << "RESET PARTICLES: TRUE\n";
			return;
		}

		inMidiOut.sendNoteOn(1,83,APCCOLORCODES::GREENFLASH);
	}
};



class ActionResetFluid: public MidiAction
{
public:

	ActionResetFluid()			
	{ 
		mName = "Reset Fluid";
	}

	virtual void doAction(FluidControls* inControls, Automator* inAutomator, const ofxMidiMessage& inMessage, ofxMidiOut& inMidiOut)
	{
		if (inMessage.status == MIDI_NOTE_ON)
		{
			inControls->setResetFluid(true);
			std::cout << "RESET FLUID: TRUE\n";
			return;
		}

		inMidiOut.sendNoteOn(1,84,APCCOLORCODES::GREENFLASH);
	}
};



class ActionSelectOverlay: public MidiAction
{
public:

	ActionSelectOverlay()			
	{ 
		mName = "Select Overlay";
	}

	virtual void doAction(FluidControls* inControls, Automator* inAutomator, const ofxMidiMessage& inMessage, ofxMidiOut& inMidiOut)
	{
		inControls->setOverlayIndex(inMessage.channel-1);
		std::cout << "OVERLAY INDEX: " << inControls->getOverlayIndex() << "\n";
		return;
	}
};



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



class ActionAutoParticleSpeed: public MidiAction
{
public:
	ActionAutoParticleSpeed()
	{
		mName = "Enable Auto Particle SPeed";
	}

	virtual void doAction(FluidControls* inControls, Automator* inAutomator, const ofxMidiMessage& inMessage, ofxMidiOut& inMidiOut)
	{
		if(inMessage.status == MIDI_NOTE_ON)
			return;

		if (!inAutomator->mParticleSpeedEnabled)
		{
			inAutomator->mParticleSpeedEnabled = true;
			inMidiOut.sendNoteOn(7,54,APCCOLORCODES::GREEN);
		}
		else
		{
			inAutomator->mParticleSpeedEnabled = false;
			inMidiOut.sendNoteOn(7,54,APCCOLORCODES::RED);
		}

		setActionTime();
		std::cout << "AUTO PARTICLE SPEED: " << inAutomator->mVectorEnabled<< "\n";
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
*/



#endif