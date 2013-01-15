#include <vector>
#include "ofMain.h"
#include "ImgVectorField.h"
#include "ImgTexture.h"
#include "ofImage.h"

#ifndef IMAGELOADER
#define IMAGELOADER

/*
 * Loader used for parsing and creating the necessary images
 * Default textures can be any format or size!
 * Vector images need to be a 24bit color image, 8 bit for every channel, no alpha
 * Clustered images need to be a 32bit color image, 8 bit for every channel, with alpha
 */

// Simple map for the textures containing the image and clustered image
struct TextureContainer
{
	ofFile mTexture;
	ofFile mCluster;

	TextureContainer(ofFile inTexture, ofFile inCluster)
	{
		mTexture = inTexture;
		mCluster = inCluster;
	}
};

class ImageLoader
{
public:
	// Constructor
	ImageLoader();

	// Destructor
	~ImageLoader();

	// Sets the Vector Maps
	void loadVectorMaps(std::vector<ImgVectorField>& ioVectorFieldContainer);

	// Sets the texture Maps
	void loadTextureMaps(std::vector<ImgTexture>& ioTextureMaps);

	// Sets the dj Maps
	void loadDjImages(std::vector<ofImage>& ioImages);

private:
	// Holds all the names of the vector images
	std::vector<ofFile>				mVectorImages;

	// Holds all the names of the textures
	std::vector<TextureContainer>	mTextureImages;

	// Holds all the dj names
	std::vector<ofFile>				mDjImages;

	// Initializes the vector images
	static void initVectorImages(std::vector<ofFile>& inFileContainer);

	// Initializes the texture images
	static void initTextureImages(std::vector<TextureContainer>& inTextureContainer);

	// Initializes the dj images
	static void initDjImages(std::vector<ofFile>& inDjImageContainer);
};

#endif