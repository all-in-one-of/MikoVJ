#include "ImgVectorField.h"
#include <iostream>
#include <assert.h>
#include "ofMain.h"
#include "ofMesh.h"

float ImgVectorField::PIXEL_VECTOR_CUTOFF = 1.0f/IMAGE_VECTOR_MULT;

// Constructor
ImgVectorField::ImgVectorField(int inImageIndex, int inWidth, int inHeight, float inMaxLength, std::vector<ofVec2f>& inImageVectors)
{
	// Make sure the resolution is equal to the amount of vectors
	assert(inWidth*inHeight == inImageVectors.size());

	mVectors = inImageVectors;
	mWidth = inWidth;
	mHeight = inHeight;
	mIndex = inImageIndex;
	mMaxLength = inMaxLength;

	// Create our poly lines so it can be drawn directly
	createPolyMesh(ofGetWidth(), ofGetHeight());
}



// Destructor does nothing
ImgVectorField::~ImgVectorField()
{}



const ofImage* ImgVectorField::asImage()
{
	//TODO: Make sure to create the vectorized image!
	return &mVectorizedImage;
}



// Gets the vector value at pixel index specified, this is from screen to vector
const ofVec2f* ImgVectorField::getValueAt(const int inXPosition, const int inYPosition)
{
	int new_x;
	int new_y;
	screenToVector(inXPosition, inYPosition, new_x, new_y);
	return &(mVectors[(new_y*mWidth)+new_x]);
}



// Gets a vector value at a certain index
const ofVec2f* ImgVectorField::getValueAt(const int inIndex)
{
	return &mVectors[inIndex];
}



// Converts screen to vector space, resulting in a nearest neighbour approx
void ImgVectorField::screenToVector(const int inX, const int inY, int& outX, int& outY)
{
	outX = inX / mWidth;
	outY = inY / mHeight;
}



// Converts a vector based on it's index to a location on screen
void ImgVectorField::vectorToScreen(const int inVectorIndex, int& outX, int& outY)
{
	// First convert to local x and y, then to screen
	int y = inVectorIndex / mWidth;
	int x = inVectorIndex % mWidth;

	// Now scale based on screen space
	outY = (int)((float)y * ((float)mScreenWidth / (float)mWidth));
	outX = (int)((float)x * ((float)mScreenHeight / (float)mHeight));
}



// Converts a vector to relative screen space
void ImgVectorField::vectorToScreen(const int inVectorINdex, float& outX, float& outY)
{
	int y = inVectorINdex / mWidth;
	int x = inVectorINdex % mWidth;

	outY = float(y) / (float)mHeight;
	outX = float(x) / (float)mWidth;
}



void ImgVectorField::createPolyMesh(const int  inScreenWidth, const int inScreenHeight)
{
	mScreenWidth = inScreenWidth;
	mScreenHeight = inScreenHeight;

	// Make sure the image fills the screen, offset the vector
	float dx = (float)inScreenWidth / (float)mWidth;
	float dy = (float)inScreenHeight / (float)mHeight;

	// Create a of mesh object
	ofMesh mesh;

	// Assuming we have the same amount of vectors as lines, copy one by one
	for(int y = 0; y < mHeight; y++)
	{
		for(int x = 0; x < mWidth; x++)
		{
			int pixel_index =  (y*mWidth)+x;

			mesh.addVertex(ofVec3f((float)x*dx, (float)y*dy, 0.0f));
			mesh.addVertex(ofVec3f(
				((float)x*dx) + (mVectors[pixel_index].x * IMAGE_VECTOR_MULT),
				((float)y*dy) + (mVectors[pixel_index].y * IMAGE_VECTOR_MULT),
				0.0f
				));

			mesh.addColor(ofFloatColor(255.0f, 255.0f, 255.0f));
			mesh.addColor(ofFloatColor(255.0f, 0.0f, 0.0f));
		}
	}
	mVertexBuffer.setMesh(mesh, GL_STATIC_DRAW);
}



// Draws the poly lines to screen
void ImgVectorField::draw()
{	
	mVertexBuffer.draw(GL_LINES,0,mVectors.size()*2);
}