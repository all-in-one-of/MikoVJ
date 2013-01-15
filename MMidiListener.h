#include "ofxMidi.h"
#include <vector>
#include "MidiDevice.h"

/*
 * Simple listener that implements the listener interface from the ofxMidi plugin
 */

class MMidiListener : public ofxMidiListener {  

public:  
	// Constructor
	MMidiListener();

	// Destructor
	~MMidiListener();

	// Called when a new midi message is received
	void newMidiMessage(ofxMidiMessage& eventArgs);

	// Get's the latest midi message
	ofxMidiMessage getMidiMessage();

	// Adds a midi device listener 
	void addMidiDeviceListener(MidiDevice* inMidiDevice);

	// Member that can tell the outside world if a new message has been received
	bool mNewMessageReceived;
	
private:
	// Where the midi data will be stored
	ofxMidiMessage mMidiMessage;

	// List of midi devices that get called when a message is received
	std::vector<MidiDevice*> mMidiDevices;
};