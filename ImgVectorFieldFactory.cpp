#include "ImgVectorFieldFactory.h"
#include <assert.h>
#include <vector>
#include "ofMath.h"
#include "Utils.h"

// Constructor does nothing
ImgVectorFieldFactory::ImgVectorFieldFactory()
{}



// Destructor does nothing
ImgVectorFieldFactory::~ImgVectorFieldFactory()
{}



// Returns an Image Vector field based on an incoming image
ImgVectorField ImgVectorFieldFactory::CreateField(const ofFile& inFile, int inImageIndex)
{

	std::cout << "\nCreating Vector Field from Image: " << inFile.getFileName() << "\n";

	ofImage image;
	image.loadImage(inFile);

	// Make sure the image is there and has the right format
	assert(image.type == OF_IMAGE_COLOR);
	assert(image.bpp == 24);

	int width = image.getWidth();
	int height = image.getHeight();

	// The amount of vectors to create
	int vectorCount = width * height;

	// create a 2d vector field
	std::vector<ofVec2f> vectorField;
	vectorField.resize(vectorCount);

	// get the pixels from the image
	unsigned char * imagePixels = image.getPixels();

	// loop through all of the pixels
	for(int x=0; x < width; x++)
	{
		for(int y=0; y < height; y++)
		{
			// Pixels around current pixel
			unsigned char areaPixels[9];

			// loop through the area pixels
			for(int i=-1; i<=1; i++){
				for(int j=-1; j<=1; j++){

					// determine where to read from in the area (not optimized)
					// clamp the read position values, so they don't go out of bounds
					int ny = y+j;
					int nx = x+i;
					iClamp(0, width-1, nx);
					iClamp(0, height-1, ny);

					int readPos = ((ny) * width + (nx)) * 3;

					unsigned char R = imagePixels[readPos];
					unsigned char G = imagePixels[readPos+1];
					unsigned char B = imagePixels[readPos+2];

					// Get the greyscale value
					char BR = (0.299 * R) + (0.587 * G) + (0.114 * B);

					// Find the kernel write position and write
					int writePos = (j+1) * 3 + (i + 1);
					areaPixels[writePos] = BR;
				}
			}

			// Get the averages of the surrounding pixels as a 2d vector
			float dX = ((areaPixels[0] + areaPixels[3] + areaPixels[6])/3) - ((areaPixels[2] + areaPixels[5] + areaPixels[8])/3);
			float dY = ((areaPixels[0] + areaPixels[1] + areaPixels[2])/3) - ((areaPixels[6] + areaPixels[7] + areaPixels[8])/3);

			int vectorPos = (y * width) + x;

			vectorField[vectorPos].x = dX;
			vectorField[vectorPos].y = dY;
		}
	}

	// We actually need to normalize based on the vector length, instead of seperate x and y values
	// First find the max length
	float max_length = 0.0f;
	float nlength;
	for(int i=0; i< vectorCount; i++)
	{
		nlength = vectorField[i].length();
		if(nlength > max_length) 
		{
			max_length = nlength;
		}
	}

	// Now scale everything based on the max length
	for(int i=0; i< vectorCount; i++)
	{
		vectorField[i].x /= max_length;
		vectorField[i].y /= max_length;
	}

	// Return a new image vector field
	return ImgVectorField(inImageIndex, width, height, max_length, vectorField);
}