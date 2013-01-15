#ifndef FLUID_CONTROLS
#define FLUID_CONTROLS

class FluidControls{

public:
	// Constructor
	FluidControls();

	// Destructor
	~FluidControls();

	// Sets the amount of images
	inline void setMaxImages(int inMaxImages)			{mMaxImages = inMaxImages; }
	inline void setMaxClusters(int inMaxClusters)		{mMaxClusters = inMaxClusters; }
	inline void setMaxVectorFields(int inMaxFields)		{mMaxVectorFields = inMaxFields; }
	inline void setMaxOverlays(int inMaxOverlays)		{mMaxOverlays = inMaxOverlays; }
	inline void setResetFluid(bool inValue)				{mResizeFluid = inValue; }
	inline int  getMaxImages()							{return mMaxImages; }
	inline int	getMaxVectorFields()					{return mMaxVectorFields; }
	inline int	getMaxClusters()						{return mMaxClusters; }

	// Sets the image counters
	void setImageIndex(int inIndex);
	void setClusterIndex(int inIndex);
	void setVectorIndex(int inIndex);
	void setOverlayIndex(int inIndex);

	// Gets the image counters
	int getImageIndex()								{return mSelectedImage; }
	int getClusterIndex()							{return mSelectedCluster; }
	int getVectorIndex()							{return mSelectedVectorField; }
	int getOverlayIndex()							{return mSelectedOverlay; }

	// Triggers
	void setEmitCluster(bool inEmit)				{mEmitCluster = inEmit; }
	void setResetParticles(bool inReset)			{mReset = inReset; }
	bool getEmitCluster();
	bool getResetParticles();
	bool getResetFluid();

	// Gets the particle multiplier
	float getParticleMult()							{return mParticleMult; }
	void  setParticleMult(float inValue)			{mParticleMult = inValue; mParticleSize = mParticleScale * mParticleMult;}
	float getParticleScale()						{return mParticleScale;}
	void  setParticleScale(float inValue)			{mParticleScale = inValue; mParticleSize = mParticleScale * mParticleMult;}

	// The control members that can be accessed and set immediately
	int		mFluidCellsX;			//< The amount of fluid cells
	bool	mDrawFluid;				//< If the fluid needs to be drawn to screen
	bool	mDrawParticles;			//< If the particles need to be drawn to screen
	bool	mDrawImageVectors;		//< If the image vectors need to be drawn to screen
	bool	mDrawImage;				//< If the image needs to be drawn
	float	mAlphaParticles;		//< Visibility of the particles
	float	mAlphaLines;			//< Visibility of the lines
	float	mAlphaFluid;			//< Visibility of the fluid
	float	mAlphaImage;			//< Visibility of the image
	float	mVelNormScale;			//< Normalized vector scale
	float	mVelWeighScale;			//< Weighted scale to be added
	float	mPartAlphaDecay;		//< The decay rate of the particle
	bool	mDrawPartPoints;		//< If the particles are drawn as points
	bool	mDrawPartHist;			//< If the history is drawn
	bool	mDrawPartLines;			//< If the particles are connected
	float	mLineWidth;				//< The width of the line
	float	mTrailLength;			//< Length of the trail
	float	mParticleSize;			//< Size of the particles on screen
	float	mParticleSpeed;			//< The speed at which the particle is allowed to conform to the fluid velocity
	int		mEmitAmount;			//< The amount of particles to emit toggled
	float	mFluidAlphaScale;		//< The amount the fluid is scaled based on the amount of particles emitted
	float	mAlphaLogo;				//< The amount of alpha of the overlay;
	bool	mShowLogo;				//< If the logo should be shown

private:
	// These can only be accessed by the helper methods
	int mMaxImages;					//< Max Images
	int mMaxVectorFields;			//< Max Vector fields
	int mMaxOverlays;				//< Max amount of overlays
	int mMaxClusters;				//< Max Clusters

	int		mSelectedImage;			//< The image currently selected for drawing
	int		mSelectedVectorField;	//< The vector field currently selected
	int		mSelectedCluster;		//< The currently selected cluster
	int		mSelectedOverlay;

	bool	mReset;					//< Resets all the particles
	bool	mEmitCluster;			//< Emits particles from a cluster

	bool	mResizeFluid;			//< If the fluid needs to be receized

	float	mParticleMult;			//< Particle Size Multiplier
	float	mParticleScale;			//< The size of the particle
};

#endif