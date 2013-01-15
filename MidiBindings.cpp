#include "MidiBindings.h"
#include <iostream>

MidiBindings* MidiBindings::mInstance;


MidiBindings::MidiBindings()
{
	setMidiControls();
}



MidiBindings::~MidiBindings()
{}


// Sets up the midi controls
void MidiBindings::setMidiControls()
{
	mBindingsDictionary.push_back(FLUIDCELLS);
	mBindingsDictionary.push_back(RESIZEFLUID);
	mBindingsDictionary.push_back(DRAWFLUID);
	mBindingsDictionary.push_back(DRAWPARTICLES);
	mBindingsDictionary.push_back(DRAWIMAGEVECTORS);
	mBindingsDictionary.push_back(SELECTIMAGE);
	mBindingsDictionary.push_back(SELECTVECTOR);
	mBindingsDictionary.push_back(SELECTCLUSTER);
	mBindingsDictionary.push_back(DRAWIMAGE);
	mBindingsDictionary.push_back(ALPHAIMAGE);
	mBindingsDictionary.push_back(ALPHAPARTICLE);
	mBindingsDictionary.push_back(ALPHALINES);
	mBindingsDictionary.push_back(ALPHAFLUID);
	mBindingsDictionary.push_back(VELNORMSCALE);
	mBindingsDictionary.push_back(VELWEIGHSCALE);
	mBindingsDictionary.push_back(PARTALPHADECAY);
	mBindingsDictionary.push_back(RESET);
	mBindingsDictionary.push_back(EMITCLUSTER);
	mBindingsDictionary.push_back(DRAWPARTPOINTS);
	mBindingsDictionary.push_back(DRAWPARTHISTORY);
	mBindingsDictionary.push_back(DRAWPARTILINES);
	mBindingsDictionary.push_back(LINEWIDTH);
	mBindingsDictionary.push_back(TRAILLENGTH);
	mBindingsDictionary.push_back(PARTICLESIZE);
	mBindingsDictionary.push_back(NONE);
	mBindingsDictionary.push_back(EMITAMOUNT);
	mBindingsDictionary.push_back(AUTOMATION);
	mBindingsDictionary.push_back(AUTOCLUSTERSPEED);
	mBindingsDictionary.push_back(AUTOVECTORSPEED);
	mBindingsDictionary.push_back(AUTOIMAGESPEED);
	mBindingsDictionary.push_back(AUTOIMAGEENABLE);
	mBindingsDictionary.push_back(AUTOVECTORENABLE);
	mBindingsDictionary.push_back(AUTOCLUSTERENABLE);
	mBindingsDictionary.push_back(AUTOEMITSPEED);
	mBindingsDictionary.push_back(ENABLEALPHALOGO);
	mBindingsDictionary.push_back(ALPHALOGO);
	mBindingsDictionary.push_back(OVERLAYSELECT);
}



const MidiControls& MidiBindings::getMidiControl(int inNumber)
{
	// Iterate over all our bindings, see if we find a match.
	// Return our choice

	std::vector<MidiControls>::iterator  it;
	for(it = mBindingsDictionary.begin(); it < mBindingsDictionary.end(); ++it)
	{
		MidiControls control = *it;
		if (inNumber == control)
			return control;
	}
	return NONE;
}



MidiBindings* MidiBindings::GetInstance()
{
	if (!mInstance)
	{
		mInstance = new MidiBindings();
	}
	return mInstance;
}