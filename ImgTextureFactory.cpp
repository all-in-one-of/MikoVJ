#include "ImgTextureFactory.h"
#include <assert.h>
#include <vector>


// Used for sampling the amount of clusters
int ImgTextureFactory::CLUSTER_SAMPLE_WIDTH = 250;



// Minimum amount of pixels in a cluster
int ImgTextureFactory::MIN_CLUSTER_PIXEL_COUNT = 100;



// Constructor does nothing
ImgTextureFactory::ImgTextureFactory()
{}



// Destructor does nothing
ImgTextureFactory::~ImgTextureFactory()
{}



// Create the clusters out of the image
ImgTexture ImgTextureFactory::CreateImage(const ofFile& inImageFile, const ofFile& inClusterFile)
{
	std::cout << "\nCreating Image: " << inImageFile.getFileName() << "\n";

	std::cout << "\nCreating Clustered Image: " << inClusterFile.getFileName() << "\n";

	// First create an image out of the incoming file, this can have any format
	ofImage image;
	image.loadImage(inImageFile);
	assert(image.isAllocated());

	// Load our clustered image in a pixel buffer
	ofPixels clustered_pix;
	ofLoadImage(clustered_pix, inClusterFile.getFileName());

	/*
	// Load our sample image in a pixel buffer
	ofPixels clustered_sample_pix;
	ofLoadImage(clustered_pix, inClusterFile.getFileName());
	*/

	// Now create our clustered image, this needs to be of a type (rgba, 8bc)
	assert(clustered_pix.isAllocated());
	assert(clustered_pix.getImageType() == OF_IMAGE_COLOR_ALPHA);
	assert(clustered_pix.getBitsPerPixel() == 32);

	// Will hold the final amount of clusters
	int cluster_counter = 0;

	// Used for storing the color value
	std::vector<BYTE>			colors;
	std::vector<int>			color_refs;

	// Now get the pixels and iterate over them
	// We sample how many clusters there are in the image,
	// The colors that belong to that cluster and how many times that color appears in the image
	BYTE* pixels = clustered_pix.getPixels();
	for (int x=0; x < clustered_pix.getWidth(); x++)
	{
		for(int y=0; y < clustered_pix.getHeight(); y++)
		{
			// Get the current read pos and sample color
			int read_pos = ((y*clustered_pix.getWidth())+ x) * 4;

			// Make sure alpha is not 0
			if(pixels[read_pos+3] < 2)
				continue;

			BYTE color = pixels[read_pos];

			// See if it's in the colors array, if not add
			bool	already_present = false;
			int		color_counter = 0;
			for(std::vector<BYTE>::iterator it = colors.begin(); it != colors.end(); ++it) 
			{
				// Get the color and sample within a range
				BYTE p_color = *it;
				if(!(color > *it+2) && !(color < *it-2))
				{
					already_present = true;
					(color_refs[color_counter])++;
					break;
				}

				// Increment color counter
				color_counter++;
			}

			if(!already_present)
			{
				colors.push_back(color);
				color_refs.push_back(1);
				cluster_counter++;
			}
		}
	}

	// Now delete the clusters that don't have enough pixels
	std::vector<BYTE> final_color_set;
	int counter = 0;
	int fclusters = 0;
	for(std::vector<int>::iterator it = color_refs.begin(); it != color_refs.end(); ++it)
	{
		if(*it >= MIN_CLUSTER_PIXEL_COUNT)
		{
			final_color_set.push_back(colors[counter]);
			fclusters++;
		}
		counter++;
	}

	// Sort the remaining ones based on color
	vector<BYTE>::iterator it;
	sort(final_color_set.begin(), final_color_set.end());

	// Return a new texture that holds the image and clusters
	return ImgTexture(image, clustered_pix, fclusters, final_color_set);
}