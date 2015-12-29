#include "constraint.h"
#include "vec3.h"

			
// implementing constraints
/********************************************************************************
 * In this fuction single constriant between 2 particles is solved. 			*
 * This is called many times per frames.										*
 * Using the fact of correction : say we have 2 numbers 5 and 3 then the to		*
 * 								  bring 5 to 3 the correction is 5*( 1 - 3/5)	*
 * Implemented this to get the desired correction_vector						*
 ********************************************************************************/
 
void Constraint::satisfyConstriant(){
					// Vector from p1 to p2
	Vec3f p1_to_p2 = p2->getPosition() - p1->getPosition();	
					// current distance between p1 and p2 
	float current_distance = p1_to_p2.magnitude();
	
					// this is and offSet vector which will move p1 to the 
					// distance of natural_length of p2;
					
	Vec3f correction_vector = p1_to_p2*( 1 - (natural_length/current_distance) );
//	std::cout<< correction_vector<< " here\n";
					// Making it half so that we can move both p1 and p2  to
					// satisfyConstriant
	Vec3f half_correction_vector = correction_vector*0.5;
	
//	std::cout<< half_correction_vector<< " here\n";
	//Updating postions
	/****************************************************************************
	 *			  P1 o-------------------o P2									*
     *				P1  o------------o P2										*
	 *	Editing Vector from both ends to satisfy length constriant				*
	 ****************************************************************************/	
					// Moving p1 along the vector p1_to_p2 by half_correction_vector
	p1->offSetPosition(half_correction_vector);
					// Moving p2 along negative vector p1_to_p2 by half_correction_vector
					// because vector is form p1_to_p2
	p2->offSetPosition(-half_correction_vector);
	
}
