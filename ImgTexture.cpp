#include "ImgTexture.h"
#include "ofMain.h"
#include "Utils.h"
#include <assert.h>
#include <iostream>

// Constructor parses the image
ImgTexture::ImgTexture(const ofImage& inImage, const ofPixels& inClusteredImage, int inAmountOfClusters, std::vector<BYTE> inClusterColors)
{
	// Make sure amount of clusets is same size as amount of colors
	assert(inAmountOfClusters == inClusterColors.size());

	// Now set the data
	mOriginalPixels = inImage;
	mOriginalClusteredImage = inClusteredImage;
	mClusterAmount = inAmountOfClusters;

	// Set the cluster colors
	mClusterColors = inClusterColors;
	mClusterColors.resize(inAmountOfClusters);

	// Initializes the cluster sets
	initClusterSets();

	// Update our images
	updateImage(ofGetWidth(), ofGetHeight());
	updateClusters(ofGetWidth(), ofGetHeight());

	// Unbind the clustered image
	mResizedClusteredImage.unbind();
}



// Destructor does nothing
ImgTexture::~ImgTexture()
{}



// Resizes the parent image
void ImgTexture::updateImage(const int inScreenWidth, const int inScreenHeight)
{
	// First make sure the resized one is set to the original
	mResizedImage = mOriginalPixels;

	// The resized image is necessary for screen space color lookups
	mResizedImage.resize(inScreenWidth, inScreenHeight);
}



// Updates the associated clusters
void ImgTexture::updateClusters(const int inScreenWidth, const int inScreenHeight)
{	
	mOriginalClusteredImage.resize(inScreenWidth, inScreenHeight, OF_INTERPOLATE_NEAREST_NEIGHBOR);
	mResizedClusteredImage.setFromPixels(mOriginalClusteredImage);

	//Now the clustered image is resized, update the cluster sets
	updateClusterSets();
}



// Resamples the clusters based on the clustered image
// TODO: Instead of using pixel x, y values, maybe use direct indices (faster)
void ImgTexture::updateClusterSets()
{
	// Clear current clustersets, keep iterator
	std::vector<ClusterSet>::iterator cit;
	for(cit = mClusterSets.begin(); cit != mClusterSets.end(); cit++)
	{
		cit->clearPixelIndices();
	}

	// Sample the resized pixels
	BYTE* pixels = mResizedClusteredImage.getPixels();
	int cur_width = mResizedClusteredImage.getWidth();
	int cur_height = mResizedClusteredImage.getHeight();

	// Iterate over all the pixels and see to what cluster the pixel belongs...
	int counter = 0;
	for (int x=0; x < cur_width; x++)
	{
		for (int y=0; y < cur_height; y++)
		{
			// The index in the pixel array
			int read_pos = ((y*cur_width)+ x) * 4;

			// A pixel that has no alpha should not belong to a cluster
			if(pixels[read_pos + 3] < 2)
				continue;

			// Now see to what cluster the pixel belongs and add it
			BYTE sample_color = pixels[read_pos];
			for(cit = mClusterSets.begin(); cit != mClusterSets.end(); cit++)
			{
				BYTE cluster_color = cit->getClusterColor();
				if(sample_color == cluster_color)
				{
					cit->addPixelIndex(PixelIndex(x, y));
					break;
				}
			}
		}
	}
}



// Get's the color at a certain value
ofColor ImgTexture::getColor(int inX, int inY)
{
	iClamp(1, mResizedImage.width-1, inX);
	iClamp(1, mResizedImage.height-1, inY);

	return mResizedImage.getColor(inX, inY);;
}



// Get's the color relative to screen
ofColor ImgTexture::getRelColor(float inX, float inY)
{
	int x = (int)((float)ofGetWindowHeight() *inY);
	int y = (int)((float)ofGetWindowWidth()  *inX);
	return mResizedImage.getColor(x, y);
}




// Draws the damn thing to screen
void ImgTexture::drawImage(float inAlpha)
{
	ofEnableAlphaBlending();	
	glColor4f(1.0f, 1.0f, 1.0f, inAlpha);
	mOriginalPixels.draw(0.0f, 0.0f, mResizedImage.width, mResizedImage.height);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	ofDisableAlphaBlending();
}



// Creates the cluster sets
void ImgTexture::initClusterSets()
{
	// Make sure the cluster set has the right size
	mClusterSets.resize(mClusterAmount);

	// Now iterate over all the colors and add a new clusterset
	for(int i=0; i<mClusterAmount; i++)
	{
		ClusterSet nset;
		nset.setColor(mClusterColors[i]);
		mClusterSets[i] = nset;
	}
}



// Returns an array of indices, correpsonding to a cluster in memory
void ImgTexture::getClusterIndices(int inClusterIndex, int inAmount, std::vector<PixelIndex>& IOPixelIndices)
{
	//Make sure that cluster exists
	if(mClusterSets.size()-1 < inClusterIndex)
	{
		IOPixelIndices.resize(0);
		std::cout << "\nCluster out of range\n: " << inClusterIndex << "";
		return;
	}

	mClusterSets[inClusterIndex].getSelection(inAmount,IOPixelIndices);
}


