#include "EvolutionUC16Device.h"

// THE EVOLUTION 16 DEVICE
EvolutionUC16MidiDevice ::EvolutionUC16MidiDevice(int inMidiPort, int inOutMidiPort, FluidControls* inControls, Automator* inAutomator)
{
	// Assign midi port
	mBoundMidiPort = inMidiPort;

	// Set device name
	mDeviceName = std::string("Evolution UC 16");

	// Assign a midi map
	mMidiMap = EvolutionUC16MidiMap();

	// Get the bound controls
	mControl = inControls;
	mAutomator = inAutomator;

	// Open the midi output port
	mMidiOut.openPort(inOutMidiPort);
}



EvolutionUC16MidiMap::EvolutionUC16MidiMap()
{
	// Construct our uc16 midi map on creation
	constructMap();
}



void EvolutionUC16MidiMap::constructMap()
{
	std::cout << "Constructing UC16 map...\n";

	mMidiMap[MidiIndex(16,10,0)] =	new ActionSetAutoEmitSpeed();
	mMidiMap[MidiIndex(15,10,0)] =	new ActionSetAutoImageSpeed();
	mMidiMap[MidiIndex(14,10,0)] =	new ActionSetAutoClusterSpeed();
	mMidiMap[MidiIndex(13,10,0)] =	new ActionSetAutoVectorSpeed();
	mMidiMap[MidiIndex(8,10,0)] =	new ActionSetAutoParticleSpeed();
	mMidiMap[MidiIndex(7,10,0)] =	new ActionSetAutoParticleSize();
}


