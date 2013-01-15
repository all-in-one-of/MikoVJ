#include "Particle.h"

using namespace MSA;

static const float MOMENTUM = 0.5f;
static const float FLUID_FORCE = 0.6f;

void Particle::init(float x, float y, ofColor inColor, float inDecay) {
	pos = Vec2f( x, y );
	previous_pos = Vec2f(x-1, y-1);
	vel = Vec2f(0, 0);
	radius = ofRandom(1,4);
	alpha  = 1.0f - ofRandom(0,0.5);
	mass = Rand::randFloat( 0.1f, 1 );
	color = inColor;
	decay = inDecay;
	fcolor = Color(float(inColor.r)/255.0f, float(inColor.g)/255.0f, float(inColor.b)/255.0f);
}

void Particle::update( const FluidSolver &solver, const Vec2f &windowSize, const Vec2f &invWindowSize, const float& inTrailLength, const float& inParticleSpeed) 
{
	// only update if particle is visible
	if( alpha == 0 )
		return;

	// Now get the new velocity values and update
	vel = solver.getVelocityAtPos( pos * invWindowSize ) * (mass * FLUID_FORCE ) * windowSize + vel * MOMENTUM;
	vel *= inParticleSpeed;
	
	// bounce of edges
	if( pos.x < 0 ) {
		pos.x = windowSize.x;
		previous_pos.x = pos.x;
	}
	else if( pos.x > windowSize.x ) {
		pos.x = 0;
		previous_pos.x = pos.x;
	}
	if( pos.y < 0 ) {
		pos.y = windowSize.y;
		previous_pos.y = pos.y;
	}
	else if( pos.y > windowSize.y ) {
		pos.y = 0;
		previous_pos.y = pos.y;
	}

	previous_pos = pos-(vel*inTrailLength);

	// fade out a bit (and kill if alpha == 0);
	alpha -= decay;
	if( alpha < 0.01 )
		alpha = 0;

	pos += vel;	
}



void Particle::updateVertexArrays( bool drawingFluid, const Vec2f &invWindowSize, int i, float* posBuffer, float* colBuffer, float inAlphaLines) {
	
	// Get the current buffer index
	int vi = i * 4;
	
	posBuffer[vi++] = previous_pos.x;
	posBuffer[vi++] = previous_pos.y;
	posBuffer[vi++] = pos.x;
	posBuffer[vi++] = pos.y;
	
	int ci = i * 8;

	colBuffer[ci++] = fcolor.r;
	colBuffer[ci++] = fcolor.g;
	colBuffer[ci++] = fcolor.b;
	colBuffer[ci++] = (alpha) * inAlphaLines;
	colBuffer[ci++] = fcolor.r;
	colBuffer[ci++] = fcolor.g;
	colBuffer[ci++] = fcolor.b;
	colBuffer[ci++] = (alpha) * inAlphaLines;
}