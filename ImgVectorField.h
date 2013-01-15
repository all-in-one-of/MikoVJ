#ifndef IMG_VECTOR_FIELD
#define IMG_VECTOR_FIELD

#include "ofImage.h"
#include "ofVec2f.h"
#include "ofPolyline.h"
#include <vector>
#include "ofVbo.h"

#define IMAGE_VECTOR_MULT 20.0f

/*
 * Defines a vector field from an image
 * This vector field can be used as a force for the solver
 * It can also be rendered as an image for debugging purposes
*/

class ImgVectorField
{
public:
	// Constructor
	ImgVectorField(int inImageIndex, int inWidth, int inHeight, float maxLength, std::vector<ofVec2f>& inImageVectors);

	// Destructor
	~ImgVectorField();

	// Returns the vector array as an image
	const ofImage* asImage();

	// Returns the width and height
	inline const int getWidth()								{return mWidth;		}
	inline const int getHeight()							{return mHeight;	}
	inline const int getIndex()								{return mIndex;		}
	inline const float getMaxLength()						{return mMaxLength;	}
	const std::vector<ofVec2f>* getVectors()				{return &mVectors;	}
	
	const ofVec2f* getValueAt(const int inXPosition, const int inYPosition);
	const ofVec2f* getValueAt(const int inIndex);
	void draw();

	// Creates a mesh that can be drawn
	void createPolyMesh(const int inScreenWidth, const int inScreenHeight);

	// Converts screen space to vector space
	void screenToVector(const int inX, const int inY, int& outX, int& outY);

	// Converts a vector to screen space
	void vectorToScreen(const int inVectorIndex, int& outX, int& outY);

	// Converts a vector to relative screen space
	void vectorToScreen(const int inVectorINdex, float& outX, float& outY);

private:
	// The image that can be drawn for debugging purposes
	ofImage  mVectorizedImage;

	// The pointer to the vector array
	std::vector<ofVec2f> mVectors;

	// The width of the sampled image
	int mWidth;

	// The height of the sampled image
	int mHeight;

	// The index of the image
	int mIndex;

	// The maximum length
	float mMaxLength;

	// The currently used screen width
	int mScreenWidth;

	// The currently used screen height
	int mScreenHeight;

	// The mesh object that can be drawn to screen
	ofVbo mVertexBuffer;

	// The pixel draw cutoff point
	static float PIXEL_VECTOR_CUTOFF;
};

#endif