#ifndef IMG_CLUSTER_FACTORY
#define IMG_CLUSTER_FACTORY

#include "ofFileUtils.h"
#include "ImgCluster.h"

class ImgClusterFactory
{
	/*
	 * Can only create a clustered image
	 * Holds only one method that returns one
	 */

	public:
		ImgClusterFactory();
		~ImgClusterFactory();

		// The function that creates one
		ImgCluster CreateClusteredImage(const ofFile& inFile);
};

#endif