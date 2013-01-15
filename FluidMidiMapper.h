#ifndef FLUID_MIDI_MAPPER
#define FLUID_MIDI_MAPPER

#include "ofxMidi.h"
#include "FluidControls.h"
#include "MidiBindings.h"
#include "Automator.h"

#define MINIMUM_MIDI_VALUE 0
#define MAXIMUM_MIDI_VALUE 127

/*
 * Maps the fluid controls to midi based on messages and a lookup table
 */

class FluidMidiMapper{

public:
	// Constructor
	FluidMidiMapper(FluidControls* inControls, Automator* inAutomator);

	// Destructor
	~FluidMidiMapper();
	
	// Updates the controls
	void updateFluidControls(const ofxMidiMessage& inMidiMessage);

	// Get the Midibinding based on an incoming message
	MidiControls getMidiBinding(const ofxMidiMessage& inMidiMessage);


private:
	// The controls
	FluidControls*	mControls;

	// The automator
	Automator*		mAutomator;

	// Some convenience functions
	bool valueToBool(const int& inValue);
};

#endif