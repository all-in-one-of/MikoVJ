#include "MidiDevice.h"
#include <iostream>

// Constructor does nothing
MidiDevice::MidiDevice()
{}

// Destructor does nothing
MidiDevice::~MidiDevice()
{}

void MidiDevice::onMessageReceived(const ofxMidiMessage& inMessage)
{
	// We need to create a new index out of the message and see if we can find it in the map
	MidiIndex index(inMessage.control, inMessage.channel, inMessage.pitch);

	MidiAction* action = mMidiMap.getMidiAction(index);
	
	// Make sure the action is valid
	if(action == NULL)
	{
		std::cout << "No available midi binding found...\n";
		return;
	}

	// If we have a matching action for the message, execute it
	action->doAction(mControl, mAutomator, inMessage, mMidiOut);
}