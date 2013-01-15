#ifndef CLUSTERSET
#define CLUSTERSET

#include <vector>
#include "ofColor.h"
#include "ofMain.h"

/*
 * Simple struct for storing coordinates
 */


struct PixelIndex
{
	int x;
	int y;

	PixelIndex(int inX, int inY) 
	{
		x = inX;
		y = inY;
	}

	PixelIndex()
	{}
};

/*
 * A clusterset holds an array of a fixed size.
 * This array holds the screen space positions of the images that define a cluster
 * It also holds the color this cluster is assigned to
 */

class ClusterSet
{
public:
	// Constructor
	ClusterSet();

	// Destructor
	~ClusterSet();

	// Sets the cluster color
	inline void setColor(BYTE inColor)						{mClusterColor = inColor; }

	// Clears the pixel array
	inline void clearPixelIndices()							{ mPixels.clear(); }

	// Adds a coordinate
	inline void addPixelIndex(PixelIndex inPixelIndex)		{ mPixels.push_back(inPixelIndex); }

	// Gets the cluster color
	inline const BYTE& getClusterColor()					{return mClusterColor; }

	// Overrides all pixel indices
	inline void setIndices(std::vector<PixelIndex>& inIndices)	{mPixels = inIndices; }

	// Gets a selection of indices back
	void getSelection(int amount, std::vector<PixelIndex>& IOIndices);

private:
	// Holds all the pixels
	std::vector<PixelIndex> mPixels;

	// Holds the cluster color
	BYTE mClusterColor;
};

#endif