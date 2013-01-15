#include "MMidiListener.h"
#include <iostream>

#ifndef MMIDI_LISTENER
#define MMIDI_LISTENER

// Constructor
MMidiListener::MMidiListener()
{
	mNewMessageReceived = false;
}



// Destructor
MMidiListener::~MMidiListener()
{}



// Adds a midi device
void MMidiListener::addMidiDeviceListener(MidiDevice* inMidiDevice)
{
	mMidiDevices.push_back(inMidiDevice);
}



// Midi message override
void MMidiListener::newMidiMessage(ofxMidiMessage& msg)
{
	// See if it's not a midi sensing message
	if (msg.status == MIDI_ACTIVE_SENSING)
		return;

	// make a copy of the latest message
	mMidiMessage = msg;

	// Notify all customers
	std::vector<MidiDevice*>::iterator it = mMidiDevices.begin();
	for (it; it!=mMidiDevices.end(); it++)
	{
		if((*it)->mBoundMidiPort == msg.portNum)
			(*it)->onMessageReceived(msg);
	}

	// for backwards compatibility
	mNewMessageReceived = true;
}



// Get the midi message, the moment they get it it's not new anymore
// We could add observers to dispatch this automatically but we only use if for one app
ofxMidiMessage MMidiListener::getMidiMessage()
{
	mNewMessageReceived = false;
	return mMidiMessage;
}

#endif
