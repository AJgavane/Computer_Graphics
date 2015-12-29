
#include "particle.h"

#define TIME_STEPSIZE2 0.5*0.5
#define DAMPING 0.01
Particle::Particle(){}

// Calculating resultant acceleration
void Particle::addForce(Vec3f force){
	acceleration += force/mass;
}

// Verlet integration
/********************************************************************************
 * This integration scheme does not stores velocity but computes it on the 		*
 * fly. Given a particle wholse position is x and velocity is v. Then in the 	*
 * timestep loop the new posiion x' and velocity v' are computed as follows.	*
 *						x' = x + v.dt											*
 * 						v' = v + a.dt											*
 *	In this method instead of storing current postion and velocity of a 		*
 * particle we store current posiion x and old_position x*. Keeping the 		*
 * timeStep fixed, the update rule( or integration step) is then				*
 *						x' = 2x -x* + a.dt.dt									*
 *						x* = x';												*
 * The term 2x-x* = x + (x - x*)	and 	(x-x*)	is a good approximation		*
 *	of current velocity.														*
 ********************************************************************************/
void Particle::timestep(){
	if (movable)
	{	
		Vec3f temp = position;
		position = position + (position - old_position)*(1.0 - DAMPING) + acceleration*TIME_STEPSIZE2;
		old_position = temp;
		acceleration = Vec3f(0.0 ,0.0, 0.0);
	}
}

Vec3f &Particle::getPosition(){
	return position;
}

void Particle::resetAcceleration(){
	acceleration = Vec3f(0.0, 0.0, 0.0);
}

void Particle::offSetPosition( const Vec3f v ){
	if(movable)
		position += v;
}

void Particle::makeUnmovable(){
	movable = false;
}
