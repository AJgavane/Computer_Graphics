
#include "vec3.h"

class Particle{
	private:
			// Properties of particle required are:
			Vec3f position;			//Current position of particle in 3D
			Vec3f old_position;		// position of particle in previous timestep 
									// Required for varlet integration
			bool movable;			// Particle moves or not?
			float mass;				// Mass of particle
			Vec3f acceleration;		// current acceleration of particle
	
	public:
			// Constructor
			Particle( Vec3f _position ): position(_position), old_position(_position), 
										 acceleration( Vec3f(0.0, 0.0, 0.0) ) , mass(1.0),
										 movable(true){}
			Particle();
			
			Vec3f &getPosition();
			
			void addForce(Vec3f force);		//Calculates resultant acceleration
			
			void timestep();				// Performs Verlet integration
				
			void resetAcceleration();		// Resets acceleration to zero
			
			void offSetPosition( const Vec3f v );		// Updates position
				
			void makeUnmovable();			//  sets movable = false
};
