#ifndef IMG_TEXTURE
#define IMG_TEXTURE

#include "ofImage.h"
#include "ofColor.h"
#include "ClusterSet.h"
#include <vector>

/*
 * Defines an image that is split in to clusters
 * It will hold the orignal image
 * And the clusters that are part of it
 */

class ImgTexture
{
public:
	// Constructor
	ImgTexture(const ofImage& inImage, const ofPixels& inClusteredImage, int inAmountOfClusters, std::vector<BYTE> inClusterColors);

	// Destructor
	~ImgTexture();

	// Returns the image
	const ofImage* getImage()					{return &mResizedImage;	}

	// Returns the original image
	const ofImage* getOriginalImage()			{return &mOriginalPixels; }

	const ofImage* getResizedImage()			{return &mResizedImage; }

	// Returns the amount of clusters
	inline int getClusterCount()				{return mClusterAmount; }

	// Resizes the image
	void updateImage(const int inScreenWidth, const int inScreenHeight);

	// Resizes and updates the associated clusters
	void updateClusters(const int inScreenWidth, const int inScreenHeight);

	// Draws the damn thing
	void drawImage(float inAlpha);

	// Gets the color at a certain index
	ofColor getColor(int inX, int inY);
	ofColor getRelColor(float inX, float inY);

	// Gets a set of cluster indices
	void getClusterIndices(int inClusterNumber, int inAmount, std::vector<PixelIndex>& IOPixelIndices);

private:
	ofImage mOriginalPixels;
	ofImage mResizedImage;

	ofPixels mOriginalClusteredImage;
	ofImage	 mResizedClusteredImage;

	std::vector<BYTE>		mClusterColors;
	std::vector<ClusterSet>	mClusterSets;
	int						mClusterAmount;

	void updateClusterSets();
	void initClusterSets();
};

#endif