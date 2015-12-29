#include "cloth.h"

Particle* Cloth::getParticle(int i, int j){
	return &particles[ j*num_of_particles_along_width + i ];
}
 			
void Cloth::makeConstraint(Particle *p1, Particle *p2){
	constraints.push_back( Constraint(p1,p2) );
}

void Cloth::drawTriangle(Particle *p1, Particle *p2, Particle *p3, const Vec3f color){
	glColor3fv( (float *) &color );
	glVertex3fv( (float *) &(p1->getPosition() ) );
	glVertex3fv( (float *) &(p2->getPosition() ) );
	glVertex3fv( (float *) &(p3->getPosition() ) );
}

Cloth::Cloth(float width, float height, int _num_of_particles_along_width, int _num_of_particles_along_height):
 						num_of_particles_along_height( _num_of_particles_along_height ),
 						num_of_particles_along_width( _num_of_particles_along_width )
{
	
	// Using vector as an array which has space for
	// #_particles_height*#_particles_width particles 
	particles.resize( num_of_particles_along_height * num_of_particles_along_width );
	
	//Creating particles in a grid from (0,0,0) to (width, -height,0)
	for (int x = 0; x < num_of_particles_along_width; x += 1)
	{
		for (int y = 0; y < num_of_particles_along_height; y += 1)
		{
			Vec3f pos =  Vec3f( width * ( (float)x/(float)num_of_particles_along_width ),
								-height *( (float)y/(float)num_of_particles_along_height),
								 0.0 );
			particles[y*num_of_particles_along_width + x] = Particle(pos);
		}
	}
	
	/******************** Adding Constraints ***********************************/
	// Connecting nearest neighbours of the particle for length constraint
	/*
			o-----o
			|.   .|
			| . . |	
			|  .  |
			| . . |
			|.   .|
			o-----o
	*/
	for (int x = 0; x < num_of_particles_along_width; x += 1)
	{
		for (int y = 0; y < num_of_particles_along_height; y += 1)
		{
			if(x < num_of_particles_along_width -1)
				makeConstraint( getParticle(x,y) , getParticle(x+1, y) );
				
			if(y < num_of_particles_along_height - 1)
				makeConstraint( getParticle(x,y) , getParticle(x, y+1) );
				
			if(x<num_of_particles_along_width - 1 && y<num_of_particles_along_height-1)
				makeConstraint( getParticle(x,y) , getParticle(x+1,y+1) );
				
			if( x<num_of_particles_along_width-1 && y<num_of_particles_along_height-1)
				makeConstraint( getParticle(x+1, y), getParticle(x, y+1) );
		}
	}
	
	// Connecting those neighbours which are at distance 2
	for (int x = 0; x < num_of_particles_along_width; x += 1)
	{
		for (int y = 0; y < num_of_particles_along_height; y += 1)
		{
			if(x < num_of_particles_along_width -2)
				makeConstraint( getParticle(x,y) , getParticle(x+2, y) );
				
			if(y < num_of_particles_along_height - 2)
				makeConstraint( getParticle(x,y) , getParticle(x, y+2) );
				
			if(x<num_of_particles_along_width - 2 && y<num_of_particles_along_height-2)
				makeConstraint( getParticle(x,y) , getParticle(x+2,y+2) );
				
			if( x<num_of_particles_along_width-2 && y<num_of_particles_along_height-2)
				makeConstraint( getParticle(x+2, y), getParticle(x, y+2) );
		}
	}
	
	// Anchoring the top left and top right corners of the cloth 
	for (int i = 0; i < 3; i += 1)
	{
		getParticle(0+i, 0)->offSetPosition( Vec3f(0.5,0.0,0.0) );
		
		getParticle(0+i, 0)->makeUnmovable();
	
		getParticle(0+i, 0)->offSetPosition(Vec3f(-0.5,.0, .0));
		
		getParticle(num_of_particles_along_width - 1 - i, 0)->makeUnmovable();
	}

}

//Function to draw cloth.
void Cloth::drawCloth()
{
	glBegin(GL_TRIANGLES);
		for (int x = 0; x < num_of_particles_along_width-1; x += 1)
		{
			for (int y = 0; y < num_of_particles_along_height-1; y += 1)
			{
				Vec3f color(0.0, 0.0 ,0.0);
				if(x%2 == 0)
					color = Vec3f(0.6,0.0,0.0);
				else
					color = Vec3f(1.0,1.0,1.0);	

				drawTriangle(getParticle(x+1,y) , getParticle(x,y), getParticle(x,y+1), color);
				drawTriangle( getParticle(x+1,y+1), getParticle(x+1, y), getParticle(x,y+1) ,color);
			}
		}
	glEnd();
//	std::cout<<"cloth drawn\n";
}


// adding forces like gravity and other if any
void Cloth::addForce(const Vec3f direction){
	// creating a particle iterator to traverse through all particles
	std::vector<Particle>::iterator particle_itr;
	
	for(particle_itr = particles.begin(); particle_itr != particles.end(); particle_itr++)
	{
		(*particle_itr).addForce(direction);
	}
}

/* This function updates the entire cloth for a single timeStep and calls functions
	like satisfyConstriant() for every constraint and calling timestep() for 
	each particle
	*/
void Cloth::timeStep(){
	
	// creating a constraint iterator to traverse through all constraints
	std::vector<Constraint>::iterator constraint_itr;
	// 15 is number of times constraints to be checked more is better
	for (int i = 0; i < 15; i += 1)			
	{
		for(constraint_itr = constraints.begin(); constraint_itr != constraints.end(); constraint_itr++)
		{
			(*constraint_itr).satisfyConstriant();		// Satisfy constraint
			
		}
			
	}
	 
	 // creating a particle iterator to traverse through all particles
	std::vector<Particle>::iterator particle_itr;
	for(particle_itr = particles.begin(); particle_itr != particles.end(); particle_itr++)
	{
		(*particle_itr).timestep();	// calculate the position of each particle at the next time step.
	}	
	
}

// This function is a simpler form of collision of cloth with ball
void Cloth::ballCollision( const Vec3f center, const float radius){

	std::vector< Particle >::iterator particle_itr;
	
	for(particle_itr = particles.begin() ; particle_itr != particles.end(); particle_itr++){
	
		Vec3f vec = (*particle_itr).getPosition() - center;
		float length = vec.magnitude();
		
		if(length < radius){
			//project the particle on the surface of the sphere
			(*particle_itr).offSetPosition( vec.normalize() *(radius - length) );
		}
	}

}
