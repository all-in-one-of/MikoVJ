#ifndef IMG_TEXTURE_FACTORY
#define IMG_TEXTURE_FACTORY

#include "ImgTexture.h"
#include "ofFileUtils.h"

class ImgTextureFactory
{
	/*
	 * Can only create image textures
	 * Holds only one method that returns one
	 */

public:
	ImgTextureFactory();
	~ImgTextureFactory();

	// The function that creates an image texture out of a file name
	ImgTexture CreateImage(const ofFile& inFile, const ofFile& inClusterFile);

private:
	static int CLUSTER_SAMPLE_WIDTH;
	static int MIN_CLUSTER_PIXEL_COUNT;

};

#endif