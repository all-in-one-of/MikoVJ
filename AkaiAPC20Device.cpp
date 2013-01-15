#include "AkaiAPC20Device.h"

// THE AKAI APC20 DEVICE
AkaiAPC20MidiDevice::AkaiAPC20MidiDevice(int inMidiPort, int inOutMidiPort, FluidControls* inControls, Automator* inAutomator)
{
	// Assign midi port
	mBoundMidiPort = inMidiPort;

	// Set device name
	mDeviceName = std::string("Akai APC 20");

	// Assign a midi map
	mMidiMap = AkaiAPCMidiMap();

	// Get the bound controls
	mControl = inControls;
	mAutomator = inAutomator;

	// Open the midi output port
	mMidiOut.openPort(inOutMidiPort);
}




// Has it's own constructor that is used to initialize the map
AkaiAPCMidiMap::AkaiAPCMidiMap()
{
	// Construct our map
	constructMap();
}



// Builds the midi map
void AkaiAPCMidiMap::constructMap()
{
	mMidiMap[MidiIndex(16,1,0)] =	new ActionSelectOverlay();
	mMidiMap[MidiIndex(16,2,0)] =	new ActionSelectOverlay();
	mMidiMap[MidiIndex(16,3,0)] =	new ActionSelectOverlay();
	mMidiMap[MidiIndex(16,4,0)] =	new ActionSelectOverlay();
	mMidiMap[MidiIndex(16,5,0)] =	new ActionSelectOverlay();
	mMidiMap[MidiIndex(16,6,0)] =	new ActionSelectOverlay();

	mMidiMap[MidiIndex(7,5,0)] =	new ActionChangeAlphaLogo();
	mMidiMap[MidiIndex(0,5,48)] =	new ActionEnableAlphaLogo();

	mMidiMap[MidiIndex(7,1,0)] =	new ActionAlphaImage();
	mMidiMap[MidiIndex(0,1,48)] =	new ActionEnableImage();

	mMidiMap[MidiIndex(7,2,0)] =	new ActionAlphaParticle();
	mMidiMap[MidiIndex(0,2,48)] =	new ActionEnableParticles();

	mMidiMap[MidiIndex(7,4,0)] =	new ActionAlphaFluid();
	mMidiMap[MidiIndex(0,4,48)] =	new ActionEnableFluid();

	mMidiMap[MidiIndex(7,3,0)] =	new ActionPartHistoryAlpha();
	mMidiMap[MidiIndex(0,3,48)] =	new ActionEnablePartHistory();
	mMidiMap[MidiIndex(0,3,49)] =	new ActionEnableLines();

	mMidiMap[MidiIndex(0,1,86)] =	new ActionEmit();

	mMidiMap[MidiIndex(0,8,53)] =	new ActionAutomate();
	mMidiMap[MidiIndex(0,8,54)] =	new ActionAutomateImage();
	mMidiMap[MidiIndex(0,8,55)] =	new ActionAutoCluster();
	mMidiMap[MidiIndex(0,8,56)] =	new ActionAutoVector();
	mMidiMap[MidiIndex(0,7,54)] =	new ActionAutoParticleSpeed();
	mMidiMap[MidiIndex(0,7,55)] =	new ActionAutomateParticleSize();

	mMidiMap[MidiIndex(0,1,57)] =	new ActionSelectCluster();
	mMidiMap[MidiIndex(0,2,57)] =	new ActionSelectCluster();
	mMidiMap[MidiIndex(0,3,57)] =	new ActionSelectCluster();
	mMidiMap[MidiIndex(0,4,57)] =	new ActionSelectCluster();
	mMidiMap[MidiIndex(0,5,57)] =	new ActionSelectCluster();
	mMidiMap[MidiIndex(0,6,57)] =	new ActionSelectCluster();
	mMidiMap[MidiIndex(0,7,57)] =	new ActionSelectCluster();
	mMidiMap[MidiIndex(0,8,57)] =	new ActionSelectCluster();

	mMidiMap[MidiIndex(14,1,0)] =	new ActionEmitAmount();
	mMidiMap[MidiIndex(7,7,0)] =	new ActionParticleDecay();

	mMidiMap[MidiIndex(0,1,49)] =	new ActionShowImageVectors();

	mMidiMap[MidiIndex(0,6,48)] =	new ActionSetParticleMult();
	mMidiMap[MidiIndex(0,6,49)] =	new ActionSetParticleMult();
	mMidiMap[MidiIndex(0,6,50)] =	new ActionSetParticleMult();
	mMidiMap[MidiIndex(7,6,0)]  =	new ActionSetParticleScale();

	mMidiMap[MidiIndex(7,8,0)]  =	new ActionSetVelocity();

	mMidiMap[MidiIndex(0,1,53)] =	new ActionSelectImage();
	mMidiMap[MidiIndex(0,2,53)] =	new ActionSelectImage();
	mMidiMap[MidiIndex(0,3,53)] =	new ActionSelectImage();
	mMidiMap[MidiIndex(0,4,53)] =	new ActionSelectImage();
	mMidiMap[MidiIndex(0,5,53)] =	new ActionSelectImage();
	mMidiMap[MidiIndex(0,1,54)] =	new ActionSelectImage();
	mMidiMap[MidiIndex(0,2,54)] =	new ActionSelectImage();
	mMidiMap[MidiIndex(0,3,54)] =	new ActionSelectImage();
	mMidiMap[MidiIndex(0,4,54)] =	new ActionSelectImage();
	mMidiMap[MidiIndex(0,5,54)] =	new ActionSelectImage();
	mMidiMap[MidiIndex(0,1,55)] =	new ActionSelectImage();
	mMidiMap[MidiIndex(0,2,55)] =	new ActionSelectImage();
	mMidiMap[MidiIndex(0,3,55)] =	new ActionSelectImage();
	mMidiMap[MidiIndex(0,4,55)] =	new ActionSelectImage();
	mMidiMap[MidiIndex(0,5,55)] =	new ActionSelectImage();
	mMidiMap[MidiIndex(0,1,56)] =	new ActionSelectImage();
	mMidiMap[MidiIndex(0,2,56)] =	new ActionSelectImage();
	mMidiMap[MidiIndex(0,3,56)] =	new ActionSelectImage();
	mMidiMap[MidiIndex(0,4,56)] =	new ActionSelectImage();
	mMidiMap[MidiIndex(0,5,56)] =	new ActionSelectImage();

	mMidiMap[MidiIndex(0,1,83)] =	new ActionResetParticles();
	mMidiMap[MidiIndex(0,1,84)] =	new ActionResetFluid();

	mMidiMap[MidiIndex(47,1,0)] =	new ActionChangeVectorField();
}