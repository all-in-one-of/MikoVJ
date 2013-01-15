#ifndef IMG_CLUSTER
#define IMG_CLUSTER

#include "ofImage.h"
#include "ofColor.h"
#include <vector>

/*
 * Defines the image that is split in to clusters
 * It will hold the clustered image as well
 */

class ImgCluster
{
public:
	// Constructor
	ImgCluster(ofImage inImage);

	// Destructor
	~ImgCluster();

	// Returns the image
	const ofImage* getImage()				{return &mResizedImage; }

	// Returns the original clustered image
	const ofImage* getOriginalImage()		{return &mOriginalImage; }

	// Updates the clustered image based on new screen size
	void updateClusters(const int inScreenWidth, const int inScreenHeight);

	// Draw the cluster image
	void draw();

private:
	ofImage mOriginalImage;
	ofImage mResizedImage;
};

#endif