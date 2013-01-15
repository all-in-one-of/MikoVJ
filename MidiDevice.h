#ifndef MIDIDEVICE
#define MIDIDEVICE

#include "MidiMap.h"
#include "ofxMidiMessage.h"
#include <string>
#include "FluidControls.h"
#include "Automator.h"
#include "ofxMidi.h"

/*
 * The midi device is the base class for all hooked up midi devices
 * It receives messages from the midi listener and basically executes the action assigned
 */

class MidiDevice
{
public:
	// Constructor
	MidiDevice();

	// Destructor
	~MidiDevice();

	// Sets the midi map
	void setMidiMap(MidiMap inMap)		{ mMidiMap = inMap; }

	// Returns the associated midi map
	const MidiMap& getMidiMap()			{ return mMidiMap; }

	// When a message is received
	void onMessageReceived(const ofxMidiMessage& inMessage);

	// Sets the outbound midi port
	void setOutMidiPort(int inPortNumber)	
	{
		mOutPort = inPortNumber;
		mMidiOut.closePort();
		mMidiOut.openPort(mOutPort);
	}

	// Holds the midi port this operator is bound to
	int mBoundMidiPort;

	// The name of the device
	std::string mDeviceName;

protected:
	// The map that holds all the midi actions
	MidiMap mMidiMap;

	// Pointer to the control it works on
	FluidControls* mControl;

	// Pointer to the automation device
	Automator* mAutomator;

	// The output of the device
	ofxMidiOut mMidiOut;

	// The output port
	int mOutPort;
};

#endif