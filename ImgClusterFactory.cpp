#include "ImgClusterFactory.h"
#include <assert.h>

// Constructor does nothing
ImgClusterFactory::ImgClusterFactory()
{}



// Destructor does nothing
ImgClusterFactory::~ImgClusterFactory()
{}



// The function that creates one
ImgCluster ImgClusterFactory::CreateClusteredImage(const ofFile& inFile)
{
	// Load the image
	ofImage image;
	image.loadImage(inFile);

	// Make sure the image has the right format (rgba, 8bc) and is sourced correctly
	assert(image.isAllocated());
	assert(image.type == OF_IMAGE_COLOR_ALPHA);
	assert(image.bpp == 32);

	// Now create the clustered image
	return ImgCluster(image);
}