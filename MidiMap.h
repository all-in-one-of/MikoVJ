#ifndef MIDIMAP
#define MIDIMAP

#include <exception>
#include <map>
#include "MidiAction.h"

/*
 * The midi index struct is used to define a key to a midi action
 */

struct MidiIndex
{
	int mControl;
	int mChannel;
	int mPitch;
	int mAccum;			//< Unique lookup based on the values combined in rank
	
	MidiIndex(int inControl, int inChannel, int inPitch)
	{
		mControl = inControl;
		mChannel = inChannel;
		mPitch = inPitch;
		mAccum = (inChannel*10000) + (inControl * 100) + inPitch;
	}

	// Used for defining map order
	bool operator < (const MidiIndex& o) const
	{
		return 
			(this->mAccum < o.mAccum);
	}

	// Used for finding same element
	bool operator == (const MidiIndex& o) const
	{
		return ( this->mAccum == o.mAccum);
	}
};



/*
 * Thrown when the map construction method isn't implemented
 */

class MapConstructionNotImplemented : public std::exception
{
	virtual const char* what() const throw()
	{
		return "No Map Constructor Implemented";
	}
};



/*
 * The MidiMap represents a binding interface for the various midi devices
 * Every map entry responds to a key that is bound to a specific midi action
 */

class MidiMap
{
public:

	// Constructor
	MidiMap();
	
	// Destructor
	~MidiMap();

	// Tries to find the action in the map based on the index given
	MidiAction* getMidiAction(const MidiIndex& inIndex);

protected:
	// The actual midi map it holds
	std::map<MidiIndex, MidiAction*> mMidiMap;

	// Constructs the map, needs to be implemented by derived maps
	virtual void constructMap();

private:
	// Thrown when there is no map constructor implemented
	MapConstructionNotImplemented mMapConstructionException;
};

#endif