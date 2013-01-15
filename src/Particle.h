#pragma once

#include "MSACore.h"
#include "MSAFluidSolver.h"
#include "ofColor.h"

using namespace MSA;

class Particle {
public:	
    Vec2f	pos, vel, previous_pos;
    float	radius;							//< Radius of the particle
    float	alpha;							//< Alpha of the particle
    float	mass;							//< Mass of the particle
	float	decay;							//< Alpha decay amount

	ofColor color;							//< Color of the particle
	Color	fcolor;							//< Color as float of the particle

	
    void init(float x, float y, ofColor inColor, float inDecay);
    void update( const FluidSolver &solver, const Vec2f &windowSize, const Vec2f &invWindowSize, const float& inTrailLength, const float& inParticleSpeed);
	void updateVertexArrays( bool drawingFluid, const Vec2f &invWindowSize, int i, float* posBuffer, float* colBuffer, float inAlphaLines);
};

