#include "ImgCluster.h"
#include "ofMain.h"

ImgCluster::ImgCluster(ofImage inImage)
{
	mOriginalImage = inImage;
	updateClusters(ofGetWidth(), ofGetHeight());
}



// Destructor does nothing
ImgCluster::~ImgCluster()
{}



void ImgCluster::updateClusters(const int inScreenWidth, const int inScreenHeight)
{
	// First reset
	mResizedImage = mOriginalImage;

	// Now resize based on new screen coordinates
	mResizedImage.resize(inScreenWidth, inScreenHeight);
}



// Draws the clustered image to screen
void ImgCluster::draw()
{
	glColor3f(1.0f, 1.0f, 1.0f);
	mResizedImage.draw(0, 0, mResizedImage.width, mResizedImage.height);
}
