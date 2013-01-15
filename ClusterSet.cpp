#include "ClusterSet.h"

// Constructor
ClusterSet::ClusterSet()
{}



// Destructor does nothing
ClusterSet::~ClusterSet()
{}



// Returns a random set of indices
void ClusterSet::getSelection(int inAmount, std::vector<PixelIndex>& IOIndices)
{
	int pixel_count = mPixels.size();

	// If the size encompasses all, return a copy of what we have
	if(pixel_count  <= inAmount)
	{
		IOIndices.resize(pixel_count);
		IOIndices = mPixels;
		return;
	}

	// Otherwise make a selection and return
	IOIndices.resize(inAmount);
	for(int x = 0; x<inAmount; x++)
	{
		PixelIndex temp = mPixels[ofRandom(pixel_count-1)]; 
		IOIndices[x] = temp;
	}
}

