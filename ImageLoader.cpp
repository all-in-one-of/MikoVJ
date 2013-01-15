#include "ImageLoader.h"
#include "ImgTextureFactory.h"
#include "ImgVectorFieldFactory.h"


// Binds all the names to the incoming object
// Adding new ones here will make the textures available to the system later on
void ImageLoader::initTextureImages(std::vector<TextureContainer>& ioTextureContainer)
{
	ioTextureContainer.push_back(TextureContainer(
		ofFile("blauw.jpg"), ofFile("blauw_clustered.png")));

	/* UNCOMMENT TO LOAD IN MORE RESOURCES
	ioTextureContainer.push_back(TextureContainer(
		ofFile("blauwraam.jpg"), ofFile("blauwraam_clustered.png")));

	ioTextureContainer.push_back(TextureContainer(
		ofFile("breda.jpg"), ofFile("breda_clustered.png")));

	ioTextureContainer.push_back(TextureContainer(
		ofFile("canada.jpg"), ofFile("canada_clustered.png")));

	ioTextureContainer.push_back(TextureContainer(
		ofFile("grafitti.jpg"), ofFile("grafitti_clustered.png")));

	ioTextureContainer.push_back(TextureContainer(
		ofFile("haven.jpg"), ofFile("haven_clustered.png")));

	ioTextureContainer.push_back(TextureContainer(
		ofFile("horizon.jpg"), ofFile("horizon_clustered.png")));

	ioTextureContainer.push_back(TextureContainer(
		ofFile("kassa.jpg"), ofFile("kassa_clustered.png")));

	ioTextureContainer.push_back(TextureContainer(
		ofFile("kraan.jpg"), ofFile("kraan_clustered.png")));

	ioTextureContainer.push_back(TextureContainer(
		ofFile("lantaarn.jpg"), ofFile("lantaarn_clustered.png")));

	ioTextureContainer.push_back(TextureContainer(
		ofFile("loods.jpg"), ofFile("loods_clustered.png")));

	ioTextureContainer.push_back(TextureContainer(
		ofFile("metro.jpg"), ofFile("metro_clustered.png")));

	ioTextureContainer.push_back(TextureContainer(
		ofFile("raam.jpg"), ofFile("raam_clustered.png")));

	ioTextureContainer.push_back(TextureContainer(
		ofFile("scheef.jpg"), ofFile("scheef_clustered.png")));

	ioTextureContainer.push_back(TextureContainer(
		ofFile("sloterdijk.jpg"), ofFile("sloterdijk_clustered.png")));

	ioTextureContainer.push_back(TextureContainer(
		ofFile("spoor.jpg"), ofFile("spoor_clustered.png")));

	ioTextureContainer.push_back(TextureContainer(
		ofFile("straat.jpg"), ofFile("straat_clustered.png")));

	ioTextureContainer.push_back(TextureContainer(
		ofFile("tram.jpg"), ofFile("tram_clustered.png")));

	ioTextureContainer.push_back(TextureContainer(
		ofFile("vuilnis.jpg"), ofFile("vuilnis_clustered.png")));

	ioTextureContainer.push_back(TextureContainer(
		ofFile("yellow.jpg"), ofFile("yellow_clustered.png")));

	ioTextureContainer.push_back(TextureContainer(
		ofFile("zuidas.jpg"), ofFile("zuidas_clustered.png")));
	*/
}



// Binds all the names to the vector file name contianer.
// Adding new names here makes tham available to the system later on
void ImageLoader::initVectorImages(std::vector<ofFile>& ioFileContainer)
{
	ioFileContainer.push_back(ofFile("blauw_vector.jpg"));
	
	/* UNCOMMENT TO LOAD IN MORE RESOURCES
	ioFileContainer.push_back(ofFile("blauwraam_vector.jpg"));
	ioFileContainer.push_back(ofFile("breda_vector.jpg"));
	ioFileContainer.push_back(ofFile("canada_vector.jpg"));
	ioFileContainer.push_back(ofFile("grafitti_vector.jpg"));
	ioFileContainer.push_back(ofFile("radial.jpg"));
	ioFileContainer.push_back(ofFile("horizon_vector.jpg"));
	ioFileContainer.push_back(ofFile("kassa_vector.jpg"));
	ioFileContainer.push_back(ofFile("gradient_star.jpg"));
	ioFileContainer.push_back(ofFile("gradient_left.jpg"));
	ioFileContainer.push_back(ofFile("nachtwerk_logo_gradient.png"));
	ioFileContainer.push_back(ofFile("metro_vector.jpg"));
	ioFileContainer.push_back(ofFile("raam_vector.jpg"));
	ioFileContainer.push_back(ofFile("scheef_vector.jpg"));
	ioFileContainer.push_back(ofFile("sloterdijk_vector.jpg"));
	ioFileContainer.push_back(ofFile("spoor_vector.jpg"));
	ioFileContainer.push_back(ofFile("straat_vector.jpg"));
	ioFileContainer.push_back(ofFile("tram_vector.jpg"));
	ioFileContainer.push_back(ofFile("vuilnis_vector.jpg"));
	ioFileContainer.push_back(ofFile("yellow_vector.jpg"));
	ioFileContainer.push_back(ofFile("gradient_left.jpg"));
	*/
}



void ImageLoader::initDjImages(std::vector<ofFile>& inDjImageContainer)
{
	inDjImageContainer.push_back(ofFile("logo_overlay_inv.png"));
	inDjImageContainer.push_back(ofFile("logo_overlay.png"));
	
	/* UNCOMMENT TO LOAD IN MORE RESOURCES
	inDjImageContainer.push_back(ofFile("boston_strip.png"));
	inDjImageContainer.push_back(ofFile("presk.png"));
	inDjImageContainer.push_back(ofFile("pangaea.png"));
	inDjImageContainer.push_back(ofFile("plus.png"));
	*/
}


// Constructor
ImageLoader::ImageLoader()
{
	// Load our file objects
	initTextureImages(mTextureImages);
	initVectorImages(mVectorImages);
	initDjImages(mDjImages);
}



// Destructor
ImageLoader::~ImageLoader()
{}



// Loads the texture maps in the container
void ImageLoader::loadTextureMaps(std::vector<ImgTexture>& ioTextureContainer)
{
	// Create a new texture factory
	ImgTextureFactory tex_fac;

	// Clear the incoming container
	ioTextureContainer.clear();

	// Iterate over the sets and add them
	std::vector<TextureContainer>::iterator it;
	for(it = mTextureImages.begin(); it != mTextureImages.end(); it++)
	{
		ioTextureContainer.push_back(tex_fac.CreateImage(
			it->mTexture, it->mCluster));
	}

	std::cout << "Texture Map Count: " << ioTextureContainer.size() << "\n"; 
}



// Loads the vector maps in the container
void ImageLoader::loadVectorMaps(std::vector<ImgVectorField>& ioVectorFieldContainer)
{
	// Create a new vector field factory
	ImgVectorFieldFactory vec_fac;

	// Clear the incoming container
	ioVectorFieldContainer.clear();

	// Now iterate over all the file names and add them to the container
	std::vector<ofFile>::iterator it;
	int counter = 0;
	for(it = mVectorImages.begin(); it != mVectorImages.end(); it++)
	{
		ioVectorFieldContainer.push_back(vec_fac.CreateField(*it, counter));
		counter++;
	}

	std::cout << "Vector Map Count: " << mVectorImages.size() << "\n" ;
}



// Loads the dj images specified in the container given
void ImageLoader::loadDjImages(std::vector<ofImage>& ioImages)
{
	// Clear it
	ioImages.clear();

	// Add them
	std::vector<ofFile>::iterator it;
	for(it = mDjImages.begin(); it != mDjImages.end(); it++)
	{
		ioImages.push_back(ofImage(*it));
	}
}


