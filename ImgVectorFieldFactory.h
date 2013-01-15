#include "ImgVectorField.h"

#ifndef IMG_VECTOR_FIELD_FACTORY
#define IMG_VECTOR_FIELD_FACTORY

class ImgVectorFieldFactory
{
	/*
	 * Can only create image vector fields
	 * Holds only one method, that returns one
	 */

	public:
		ImgVectorFieldFactory();
		~ImgVectorFieldFactory();

		// The function that creates one
		ImgVectorField CreateField(const ofFile& inFile, int inImageIndex);
};

#endif