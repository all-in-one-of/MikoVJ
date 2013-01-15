/*
 *  ParticleSystem.cpp
 *  ofxMSAFluid Demo
 *
 *  Created by Mehmet Akten on 02/05/2009.
 *  Copyright 2009 MSA Visuals Ltd.. All rights reserved.
 *
 */

#include "ParticleSystem.h"

using namespace MSA;

ParticleSystem::ParticleSystem() 
{
	curIndex = 0;
	setWindowSize( Vec2f( 1, 1 ) );
}

void ParticleSystem::setWindowSize( Vec2f winSize )
{
	windowSize = winSize;
	invWindowSize = Vec2f( 1.0f / winSize.x, 1.0f / winSize.y );
}

void ParticleSystem::updateAndDraw( bool drawingFluid ){

	glEnable(GL_BLEND);
	glDisable( GL_TEXTURE_2D );
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);      

	for(int i=0; i<MAX_PARTICLES; i++) {
		if(particles[i].alpha > 0) {
			
			// Update the particle itself
			particles[i].update( 
				*solver, 
				windowSize, 
				invWindowSize,
				controls->mTrailLength,
				controls->mParticleSpeed);
			
			// Update the vertex arrays with the particle info
			particles[i].updateVertexArrays( 
				drawingFluid, 
				invWindowSize, 
				i, 
				posArray, 
				colArray, 
				controls->mAlphaLines);
			
			// Only draw if we tell it to draw
			if(controls->mDrawPartPoints)
			{
				ofSetColor(particles[i].color, particles[i].alpha * 255.0f * controls->mAlphaParticles);
				ofCircle(ofPoint(particles[i].pos.x, particles[i].pos.y, 0.0f), particles[i].radius * controls->mParticleSize);
			}
		}
	}   


	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(2, GL_FLOAT, 0, posArray);
	
	glEnableClientState(GL_COLOR_ARRAY);
	glColorPointer(4, GL_FLOAT, 0, colArray);

	glLineWidth(controls->mLineWidth);
	
	// Draw our buffers to screen with the selected modes
	if(controls->mDrawPartHist)
		glDrawArrays(GL_LINES, 0, MAX_PARTICLES * 2);
	if(controls->mDrawPartLines)
		glDrawArrays(GL_LINE_STRIP, mBeginClusterIndex*2, mEndClusterIndex*2);

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);
	
	glDisable(GL_BLEND);
}



// Adds a new particle at the current index
void ParticleSystem::addParticle( const Vec2f &pos, const ofColor& inColor) {
	particles[curIndex].init( pos.x, pos.y, inColor, controls->mPartAlphaDecay);
	curIndex++;
	if(curIndex >= MAX_PARTICLES) curIndex = 0;
}



// Resets the system
void ParticleSystem::reset()
{
	for(int p=0; p<MAX_PARTICLES; p++)
	{
		particles[p] = Particle();
		
		int vi = p*4;
		posArray[vi++] = 0;
		posArray[vi++] = 0;
		posArray[vi++] = 0;
		posArray[vi++] = 0;

		int ci = p*8;
		colArray[ci++] = 0;
		colArray[ci++] = 0;
		colArray[ci++] = 0;
		colArray[ci++] = 0;
		colArray[ci++] = 0;
		colArray[ci++] = 0;
		colArray[ci++] = 0;
		colArray[ci++] = 0;
	}
	curIndex = 0;
}



// Updates the way the arrays should be drawn
void ParticleSystem::setIsReceivingCluster(bool inValue)
{
	if(inValue)
	{
		mBeginClusterIndex = curIndex;
		return;
	}

	mEndClusterIndex = curIndex;

}
