
#include "particle.h"

class Constraint{
	
	private:
			float natural_length;	// length between two particles p1 and p2 in rest state.
	
	public:
			Particle *p1, *p2;		// two particles named p1 and p2
			
			// Constructor
			Constraint(Particle *_p1, Particle *_p2): p1(_p1), p2(_p2){
				Vec3f vec = p1->getPosition() - p2->getPosition();
				natural_length = vec.magnitude();
//				std::cout<<"constraint length: "<<natural_length << "\n";
			}
			
			// implementing constraints
			void satisfyConstriant();

};
