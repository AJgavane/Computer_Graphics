/********************************************************************************
 * Project : Cloth Simulation													*		
 * Written by: AJInkya S. Gavane, Sudarshan Ghonge, Saurav Agarwalla			*
 * Last Modify Date: 23-11-2014													*
 ********************************************************************************/
#define TIME_STEPSIZE2 0.5*0.5
#define PI 3.1415926
#define Cos(theta) cos(PI/180*(theta))
#define Sin(theta) sin(PI/ 180 * (theta))

#include<iostream>
#include<stdlib.h>
//#include<vector>
#include<GL/glut.h>
#include<math.h>
#include "vec3.h"
#include "cloth.h"

/******************* Function Prototype ****************************************/
void init(void);
void handleKeys(unsigned char key, int x, int y);
void handleResize(int w, int h);
void handleSpecialKeys( int key, int x, int y);
void drawScene(void);
/*******************************************************************************/


/*************** Global variables **********************************************/
int window_wide = 680;
int window_height = 720;
double dz = 0.5, dx = 1.2, dy = 0.50;
double dim = 3.0;
double lookX = 0.0, lookY = -0.0, lookZ = -0.1;
double eyeX = 0.0, eyeY = 0.0, eyeZ  = 8.0;		// Camera coordinates
int toggleAxes = 0;				// Toggle Axes on/off
int toggleValues = 1;			// Toggle Values on/off
int toggleMode = 1; 			// toggle Mode on/off
int theta = 0;					//azimuth of view angle 
int phi = 0;					// elevation of view angle
int fov = 60;					// field of view for perspective
int asp = 1; 					// aspect ratio
int roll_x = 0;
int roll_y = 10;
int roll_z = 0;
Cloth cloth1(14,10,55,45);	// one Cloth object of the Cloth class
Vec3f ball_position(7,-5,8);
float radius_of_ball = 2;

/********************************************************************************/

int main (int argc, char* argv[])
{
	//initializing glut
	glutInit(&argc, argv);
	
	//Initializing Display mode
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	
	//initializing window size
	glutInitWindowSize( window_wide, window_height );
	
	// Creating Window
	glutCreateWindow("Cloth Simulation");
	
	// Initializing openGl
	init();
	
	// Calling function to display graphics
	glutDisplayFunc(drawScene);
	
	// Calling reshape function
	glutReshapeFunc(handleResize);
	
	// Calling keyboard Function
	glutKeyboardFunc(handleKeys);
	
	// Handling Special keys
	glutSpecialFunc(handleSpecialKeys);
	
	// Displaying Graphics continuously
	glutMainLoop();
	
	return 0;
}

/*************************** Drawing Function ***********************************/
void drawScene(void){
	
	/* Calculating Position */
	// add gravity for each frame directing downwards;
		cloth1.addForce( Vec3f(0.0, -0.2, 0.0)*TIME_STEPSIZE2);		// adding g*dt*dt
	// calculate the particle position for next time frame
		cloth1.timeStep();
		cloth1.ballCollision(ball_position, radius_of_ball);
//	std::cout<<"Done Update \n"	;
	
	
	// Drawing
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	if(toggleMode){			
		gluLookAt(eyeX , eyeY, eyeZ, eyeX + lookX , eyeY + lookY, eyeZ + lookZ, roll_x, roll_y, roll_z);
	} else {
		glRotatef(phi, 1, 0, 0);
		glRotatef(theta, 0, 1, 0);
	}
	glTranslatef(-6.5,4,-12.0f); // move camera out and center on the cloth
	glRotatef(25,0,1,0); // rotate a bit to see the cloth from the side
	cloth1.drawCloth();
	
	// Drawing ball
	glPushMatrix();
		glColor3f(0.2f,0.5f,0.2f);
		glTranslatef(ball_position[0] , ball_position[1], ball_position[2]);
		glutSolidSphere(radius_of_ball - 0.1, 50, 50);
	glPopMatrix();
//	std::cout<<"Done drawn \n"	;
//	glFlush();
	glutSwapBuffers();
	glutPostRedisplay();
}

/*************************** Initializing OpenGL ********************************/
void init(void){
	// Setting Background Color
	glClearColor(0.2f , 0.2f , 0.4f , 1.0f);
	
	//Enabling Depth Buffer
	glEnable(GL_DEPTH_TEST);
	
	//Nice Perspective correction
	glHint( GL_PERSPECTIVE_CORRECTION_HINT , GL_NICEST);
	
	// Just to give 3D effect to ball these lightings are added. 
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_LIGHTING); //Enable lighting
	glEnable(GL_LIGHT0); //Enable light #0
	glEnable(GL_LIGHT1); //Enable light #1
//	glEnable(GL_LIGHTING);
//	glEnable(GL_LIGHT0);	
//	glEnable(GL_LIGHT2);
}


/*************************** Keyboard Keys handle function **********************/
void handleKeys( unsigned char key, int x, int y){
	if(key == 27)	exit(0);
	else if( key == 'p' || key == 'P')	toggleAxes = 1 - toggleAxes;
	else if( key == 'v' || key == 'V')	toggleValues = 1 - toggleValues;
	else if( key == 'm' || key == 'M') 	toggleMode = 1 - toggleMode;
	
	// Camera Rolling 
	else if( key == 'x' || key == 'X' ){
		roll_x += 1;
		roll_y -= 1;
		roll_z -= 1;
	}
	else if ( key == 'c' || key == 'C' ){
		roll_x -=1;
		roll_y += 1;
		roll_z += 1;
	}
	// Change field of view angle
	else if( key == '+' && key > 1)		fov--;
	else if( key == '-' && key <179 ) 	fov++;
	
	//Change Dimensions
	else if(key == 'z')	dim += 0.1;
	else if( key == 'Z' && dim > 1) dim -= 0.1;
	
	//Rotate camera
	if( key == 'a' || key == 'A'){	// look left
		if(theta > -65){
			theta -= 3;
			lookX = Sin(theta);
			lookZ = -Cos(theta);
		}
	}
	if( key == 'd' || key == 'D'){	// look right
		if(theta < 65){
			theta += 3;
			lookX = Sin(theta);
			lookZ = -Cos(theta);
		}
	}
	if( key == 'w' || key == 'W'){	// look up
		if(phi < 60){
			phi += 3;
			lookY = Sin(phi);
			lookZ = -Cos(phi);
		}
	}
	if( key == 's' || key == 'S'){	// look down
		if(phi > -60){
			phi -= 3;
			lookY = Sin(phi);
			lookZ = -Cos(phi);
		}
	}
	
	// move ball_position
	if( key == 'i' || key =='I'){
		ball_position[2] -= 0.1;
	}
	if( key == 'k' || key == 'K'){
		ball_position[2] += 0.1;
	}
	if( key == 'j' || key == 'J'){
		ball_position[0] -= 0.1;
	}
	if( key == 'l' || key == 'L'){
		ball_position[0] += 0.1;
	}
	if(key == 'r' || key == 'R'){
		//reset ball positioned
		ball_position = Vec3f(7,-5,8);
	}
	if(key == 'o' || key == 'O'){
		ball_position[1] -= 1;
	}
	if(key == 'u' || key == 'U'){
		ball_position[1] += 1;
	}
} 

/************************** Keyboard Special Keys Handle Function ***************/
void handleSpecialKeys( int key, int x, int y){
	// Walk rightward
	if(key == GLUT_KEY_RIGHT){
		if(eyeX < 4)
			eyeX += dx;
	} 
	// Walk leftward
	if(key == GLUT_KEY_LEFT){
		if(eyeX > -4)
			eyeX -= dx;
	}
	// walk forward
	if(key == GLUT_KEY_UP){
		if(eyeZ > -1)
			eyeZ -= dz;
	}
	// walk backwards
	if(key == GLUT_KEY_DOWN) {
		if(eyeZ < 10)
			eyeZ += dz;
	}
	// move camera up
	if( key == GLUT_KEY_PAGE_UP){
		if(eyeY < 4)
			eyeY += dy;
	}
	// move camera Up along up vector
	if( key == GLUT_KEY_PAGE_DOWN){
		if (eyeY >-3)
			eyeY -= dy;
	}
	
//	keep angle to +/- 360 degrees
	theta %= 360;
	phi %= 360;
}


/************************** Handles Resize of WIndow ****************************/
void handleResize(int width, int height){
	// Compute aspect ratio of the new Window
	if(height == 0)	height = 1;
	float aspect_ratio = (float)width/(float)height;
	
	// Set Viewport to cover new Window
	glViewport( 0, 0, width, height	);	// ( xTopLeft, yTopLeft, width, height)
	
	//Enable Projection Matrix for operation and Resetting it
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();				// Reset
	
	// Enabling perspective projection with fov, aspect, zNear, zFar
	if (toggleMode)
	{
		//Perspective
		gluPerspective( fov , aspect_ratio , 1.0, 300.0);	
	} else	{
		// orthogonal
		glOrtho(-dim*aspect_ratio, +dim*aspect_ratio, -dim, +dim, -dim, +dim);
	}
	// Enable Model View matrix and reset it.
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();				//Reset
}
