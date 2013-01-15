#include "MidiAction.h"
#include <iostream>
#include <assert.h>

/*
 * The default midi action
 */

// Constructor is empty
MidiAction::MidiAction()
{
	setActionTime();
}



// Destructor is empty
MidiAction::~MidiAction()
{}



// The exception thrown when no action is defined
ActionNotImplementedException MidiAction::mException = ActionNotImplementedException();




// Throws exception when not declared in a derived class
void MidiAction::doAction(FluidControls* inControls, Automator* inAutomator, const ofxMidiMessage& inMessage, ofxMidiOut& inMidiOut)
{
	throw mException;
}



// Sets the last action time based on current time
void MidiAction::setActionTime()
{
	time_t t = time(0);
	mLastActionTime = localtime(&t)->tm_sec;
}



// Gets the current time in seconds
int MidiAction::getCurrentTime()
{
	time_t t = time(0);
	return localtime(&t)->tm_sec;
}
