
#include "constraint.h"			// particle.h is already included in constraint.h
#include<vector>
#include <GL/glut.h>

class Cloth{
 	private:
 			int num_of_particles_along_width; 
 			int num_of_particles_along_height;
			
			std::vector<Particle> particles;
			std::vector<Constraint> constraints; 			
 			
 			Particle *getParticle(int i, int j);
 			
 			void makeConstraint(Particle *p1, Particle *p2);
 			
 			void drawTriangle(Particle *p1, Particle *p2, Particle *p3, const Vec3f color);
 			
 	public:
 			//Constructor
 			Cloth( float width, float height, int _num_of_particles_along_width, int _num_of_particles_along_height );
 			
 			void drawCloth();
 			
 			void addForce(const Vec3f direction);
 			
 			void timeStep();
 			
 			void ballCollision( const Vec3f center, const float radius);
			
			
};
