#include <vector>

#ifndef FLUID_MIDI_BINDINGS
#define FLUID_MIDI_BINDINGS

enum MidiControls									//< Holds all the midi contols 
{
	FLUIDCELLS = 80,
	RESIZEFLUID = 72,
	DRAWFLUID = 68,
	DRAWPARTICLES = 66,
	DRAWIMAGEVECTORS = 71,
	DRAWIMAGE = 65,
	SELECTIMAGE = 43,
	SELECTVECTOR = 44,
	SELECTCLUSTER = 1,
	ALPHAFLUID = 49,
	ALPHAPARTICLE = 47,
	ALPHALINES = 48,
	ALPHAIMAGE = 46,
	VELNORMSCALE = 12,
	VELWEIGHSCALE = 13,
	PARTALPHADECAY = 32,
	EMITCLUSTER = 107,
	RESET = 108,
	DRAWPARTPOINTS = 73,
	DRAWPARTHISTORY = 74,
	DRAWPARTILINES = 75,
	LINEWIDTH = 4,
	TRAILLENGTH = 3,
	PARTICLESIZE = 5,
	EMITAMOUNT = 39,
	AUTOMATION = 105,
	AUTOEMITSPEED = 40,
	AUTOIMAGESPEED = 35,
	AUTOVECTORSPEED = 36,
	AUTOCLUSTERSPEED = 37,
	AUTOIMAGEENABLE = 78,
	AUTOVECTORENABLE = 79,
	AUTOCLUSTERENABLE = 81,
	ALPHALOGO = 51,
	ENABLEALPHALOGO = 70,
	OVERLAYSELECT = 8, 
	NONE = 0,
};

class MidiBindings
{
	/*
	 * Simple Midi Bindings Singleton used for storing and retrieving all the midi controls.
	 * These can be mapped back on to the system control variables.
	 */

public:
	static MidiBindings*	GetInstance();
	const MidiControls&		getMidiControl(int inNumber);
	const std::vector<MidiControls>& getMidiControls()		{return mBindingsDictionary;}

private:
	MidiBindings();											//< Private Constructor
	~MidiBindings();										//< Private Destructor
	static MidiBindings*		mInstance;					//< Instance
	std::vector<MidiControls>	mBindingsDictionary;

	void setMidiControls();									//< Sets all the midi controls in the dictionary
};


#endif