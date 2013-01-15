/*
 *  ParticleSystem.h
 *  ofxMSAFluid Demo
 *
 *  Created by Mehmet Akten on 02/05/2009.
 *  Copyright 2009 MSA Visuals Ltd.. All rights reserved.
 *
 */
#pragma once

#include "Particle.h"
#include "ofColor.h"
#include "FluidControls.h"

//#define MAX_PARTICLES	36864
#define MAX_PARTICLES 100000

using namespace MSA;

class ParticleSystem {
public:	
	
	// Arrays used for drawing those damn things
    float posArray[MAX_PARTICLES * 2 * 2];
    float colArray[MAX_PARTICLES * 4 * 2];

	// Members to update the system
	Vec2f				windowSize;
	Vec2f				invWindowSize;
	const FluidSolver	*solver;
	
	// Tracks current particle in system
    int curIndex;
	
	// Particle Array
    Particle particles[MAX_PARTICLES];

	// Controls
	const FluidControls* controls;

	
	ParticleSystem();
	void setFluidSolver( const FluidSolver *aSolver ) { solver = aSolver; }
	void setControls (const FluidControls* inControls) {controls = inControls; }
	
    void updateAndDraw( bool drawingFluid );
	void addParticle( const Vec2f &pos, const ofColor& inColor);
	void setWindowSize( Vec2f winSize );

	void reset();
	void setIsReceivingCluster(bool inValue);

private:
	int		mBeginClusterIndex;
	int		mEndClusterIndex;
	bool	mIsReceiving;
};

