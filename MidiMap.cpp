#include "MidiMap.h"
#include <iostream>

/*
 * Base Class Midi Map Implementation
 */

// Construct the map when initialized
MidiMap::MidiMap()
{}



// Destructor clears all the values pointed by the map
MidiMap::~MidiMap()
{
	// TODO: COMMENTED OUT BECAUSE OF MULTIPLE DECONSTRUCTOR CALLS
	// MOST LIKELY BECAUSE OF A WORKING COPY OP
	// FIX IN FUTURE

	/*
	if (mMidiMap.size() == 0)
		return;

	std::map<MidiIndex*, MidiAction*>::iterator it;

	for(it = mMidiMap.begin(); it!=mMidiMap.end(); it++)
	{
		MidiIndex* first = (it->first);
		MidiAction* sec = (it->second);

		delete first;
		delete sec;
	}
	*/
};



void MidiMap::constructMap()
{
	throw mMapConstructionException;
}



MidiAction* MidiMap::getMidiAction(const MidiIndex& inIndex)
{
	// Iterate over our keys and find the matching action
	std::map<MidiIndex, MidiAction*>::iterator it;
	for(it = mMidiMap.begin(); it!=mMidiMap.end(); it++)
	{
		if (it->first == inIndex)
		{
			return it->second;
		}
	}
	return NULL;
}