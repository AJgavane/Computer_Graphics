/********************************************************************************
 * 	Program to Create a Simple 3D scene of a Classroom 							*
 *  Prgrammed by : Ajinkya S Gavane	, Sudarshan Ghonge, Saurav Agarwalla		*
 *	Using : C++, GLUT,	OpenGL													*
 ********************************************************************************/

#include "screencasts.h"
//Macros needed
#define PI 3.1415926
#define Cos(theta) cos(PI/180*(theta))
#define Sin(theta) sin(PI/ 180 * (theta))
	
//Globals
double dz = 0.5, dx = 1.2, dy = 0.50;
double dim = 3.0;
int windowWidth = 700;
int windowHeight = 650;
double lookX = 0.0, lookY = -0.0, lookZ = -0.1;
//Special Globals
double eyeX = 0.0, eyeY = 0.0, eyeZ  = 8.0;		// Camera coordinates
int toggleAxes = 0;				// Toggle Axes on/off
int toggleValues = 1;			// Toggle Values on/off
int toggleMode = 1; 			// toggle Mode on/off
int theta = 0;					//azimuth of view angle 
int phi = 0;					// elevation of view angle
int fov = 60;					// field of view for perspective
int asp = 1; 					// aspect ratio

// Function prototype
void initRendering();
void project();
void reshape(int w, int h);
void handleKeyPress(unsigned char key, int x, int y);
void SpecialKeyPress(int key, int x, int y);
void drawAxes();
void drawValues();
void drawPlatform();
void drawBlackBoard();
void drawBenchs();
void drawOnPlatform();
void drawDustbin();
void drawLights();
void drawWindow();
void drawDoor();
void drawRoom();
void display();

using namespace std;

int main (int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
	glutInitWindowSize(windowWidth,windowHeight);
	glutCreateWindow("Assignment 2");
	//initRendering();
	glutDisplayFunc(display);
	glutKeyboardFunc(handleKeyPress);
	glutReshapeFunc(reshape);
	glutSpecialFunc(SpecialKeyPress);
	glutMainLoop();
	return 0;
}


void display(){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	glClearColor(0.8,0.9,1.0,1.0);
	glLoadIdentity();
	// Perspective - set eye position
	if(toggleMode){			
		printAt(5, 45, "eyeX, eyeY, eyeZ :(%d, %d, %d)", eyeX, eyeY , eyeZ);
		gluLookAt(eyeX , eyeY, eyeZ, eyeX + lookX , eyeY + lookY, eyeZ + lookZ, 0, 4.0, 0);
	} else {
		glRotatef(phi, 1, 0, 0);
		glRotatef(theta, 0, 1, 0);
	}
	drawRoom();
	drawAxes();
	drawValues();
	drawPlatform();
	drawBlackBoard();
	drawBenchs();
	drawOnPlatform();
	drawDustbin();
	drawLights();
	drawWindow();
	drawDoor();
	glFlush();
	glutSwapBuffers();
}


void drawRoom(){
	/* Ceiling */
		glBegin(GL_QUADS);
			glNormal3f(0.0, -1.0, 0.0);
				glColor3f(0.4, 0.0, 0.4);				
			glVertex3f(-5.0f, 3.0f, -8.0f);
			glVertex3f(5.0f, 3.0f, -8.0f);
				glColor3f(0.2,0.0,0.2);
			glVertex3f(5.0f, 3.0f, 0.0f);
			glVertex3f( -5.0f, 3.0f, 0.0f);
		glEnd();
	/* 	Back Wall */
		glBegin(GL_QUADS);
			glNormal3f(0.0f, 0.0f, 1.0f);
			glColor3f(0.0f, 1.0f , 0.0f);	//Dark			
			glVertex3f( 5.0f, 3.0f, -8.0f); //Draw Back Wall - Top Right
			glVertex3f(-5.0f, 3.0f, -8.0f); //Draw Back Wall - Top Left	
			glColor3f(0.0f,0.2f,0.0f);		//Light			
			glVertex3f(-5.0f, -3.0f, -8.0f); //Draw Back Wall - Bottom Left
			glVertex3f( 5.0f, -3.0f, -8.0f); //Draw Back Wall - Bottom Right
		glEnd();
	/* 	Left Wall */
		glBegin(GL_QUADS);
			glNormal3f(1.0f, 0.0f, 0.0f);
				glColor3f(0.80f,0.80f,0.0f);		//Light
			glVertex3f( -5.0f, 3.0f,-8.0f); //Draw Left Wall - Top Right
			glVertex3f( -5.0f, 3.0f, 0.0f); //Draw Left Wall - Top Left	
				glColor3f(0.20f,0.20f,0.0f);		//dark
			glVertex3f( -5.0f, -3.0f, 0.0f); //Draw Left Wall - Bottom Left
			glVertex3f( -5.0f, -3.0f,-8.0f); //Draw Left Wall - Bottom Right
		glEnd();
	/* 	Right Wall */
		glBegin(GL_QUADS);
			glNormal3f(-1.0f, 0.0f, 0.0f);
				glColor3f(0.70f,0.0f,0.0f);		//Light				
			glVertex3f( 5.0f, 3.0f, 0.0f); //Draw Right Wall - Top Right
			glVertex3f( 5.0f, 3.0f,-8.0f); //Draw Right Wall - Top Left
				glColor3f(0.20f,0.0f,0.0f);		//Dark
			glVertex3f( 5.0f, -3.0f,-8.0f); //Draw Right Wall - Bottom Left
			glVertex3f( 5.0f, -3.0f, 0.0f); //Draw Right Wall - Bottom Right
		glEnd();
	/* 	Floor */
		glBegin(GL_QUADS);
			glNormal3f(0.0f, 1.0f, 0.0f);
				glColor3f(0.0f,0.0f,.60f);		//Light
			glVertex3f(  5.0f,-3.0f,-8.0f); //Draw Floor - Top Right
			glVertex3f( -5.0f,-3.0f,-8.0f); //Draw Floor - Top Left	
				glColor3f(0.0f,0.0f,0.20f);		//Dark
			glVertex3f( -5.0f,-3.0f, 0.0f); //Draw Floor - Bottom Left
			glVertex3f(  5.0f,-3.0f, 0.0f); //Draw Floor - Bottom Right
		glEnd();
}

// Displays current x,y,z axis. Feature to make us easier to do transformation along axes.
void drawAxes(){
	if (toggleAxes)
	{
		float len = 2.0f;
		glColor3f(0.0f, 1.0f, 0.0f);
		glBegin(GL_LINES);
			glVertex3f(0.0f, 0.0f, 0.0f);
			glVertex3f(len, 0.0f, 0.0f);
			glVertex3f(0.0f, 0.0f, 0.0f);
			glVertex3f(0.0f, len, 0.0f);
			glVertex3f(0.0f, 0.0f, 0.0f);
			glVertex3f(0.0f, 0.0f, len);
		glEnd();
		// Label axes
		glRasterPos3f(len, 0, 0);
		print("X");
		glRasterPos3f(0 ,len, 0);
		print("Y");
		glRasterPos3f(0, 0, len);
		print("Z");
	}
}

// Display project mode and theta phi values. This is to keep track of Camera
void drawValues(){
	if(toggleValues){
		glColor3f(1.0f, 0.0f, 0.0f);
		printAt(5,5,"View Angle(theta, phi) : (%d , %d)", theta, phi);
		printAt(5, 25, "Project Mode : %s", toggleMode ? "Perspective":"Orthogonal");
	}
}

//Creates Platform
void drawPlatform(){
	glPushMatrix();
		glColor3f(0.1, 0.1, 0.1);
		glScalef(5.0, 0.5, 2.0);
		glTranslatef(0.0, -5.5, -3.5);	
		platform(1);
	glPopMatrix();
}

// draw Blackboard
void drawBlackBoard(){
	glPushMatrix();
		glScalef(4.0, 3.0, 0.20);
		glTranslatef(0.0, -0.0, -39.0);	
		blackBoard(1.0);
	glPopMatrix();
}

// Draw multiple benches
void drawBenchs(){
	//Row 1 Starts
		//bench 1
		glPushMatrix();
			glTranslatef(3.7, -2.2, -4.0);
			bench();
		glPopMatrix();
		//bench 2
		glPushMatrix();
			glTranslatef(2.2, -2.2, -4.0);
			bench();
		glPopMatrix();
		//bench 3
		glPushMatrix();
			glTranslatef(0.7, -2.2,  -4.0);
			bench();
		glPopMatrix();
		//bench 4
		glPushMatrix();
			glTranslatef(-0.8, -2.2, -4.0);
			bench();
		glPopMatrix();
		//bench 5
		glPushMatrix();
			glTranslatef(-2.3, -2.2, -4.0);
			bench();
		glPopMatrix();
		//bench 6
		glPushMatrix();
			glTranslatef(-3.8, -2.2, -4.0);
			bench();
		glPopMatrix();
	// Row  1 ends
	
	//Row 2 Starts
		//bench 1
		glPushMatrix();
			glTranslatef(3.7, -2.2, -2.5);
			bench();
		glPopMatrix();
		//bench 2
		glPushMatrix();
			glTranslatef(2.2, -2.2, -2.5);
			bench();
		glPopMatrix();
		//bench 3
		glPushMatrix();
			glTranslatef(0.7, -2.2, -2.5);
			bench();
		glPopMatrix();
		//bench 4
		glPushMatrix();
			glTranslatef(-0.8, -2.2, -2.5);
			bench();
		glPopMatrix();
		//bench 5
		glPushMatrix();
			glTranslatef(-2.3, -2.2, -2.5);
			bench();
		glPopMatrix();
		//bench 6
		glPushMatrix();
			glTranslatef(-3.8, -2.2, -2.5);
			bench();
		glPopMatrix();
	// Row  2 ends
	
	//Row 3 Starts
		//bench 1
		glPushMatrix();
			glTranslatef(3.7, -2.2, -1.0);
			bench();
		glPopMatrix();
		//bench 2
		glPushMatrix();
			glTranslatef(2.2, -2.2, -1.0);
			bench();
		glPopMatrix();
		//bench 3
		glPushMatrix();
			glTranslatef(0.7, -2.2, -1.0);
			bench();
		glPopMatrix();
		//bench 4
		glPushMatrix();
			glTranslatef(-0.8, -2.2, -1.0);
			bench();
		glPopMatrix();
		//bench 5
		glPushMatrix();
			glTranslatef(-2.3, -2.2, -1.0);
			bench();
		glPopMatrix();
		//bench 6
		glPushMatrix();
			glTranslatef(-3.8, -2.2, -1.0);
			bench();
		glPopMatrix();
	// Row  3 ends
}

// Draw chiar , table and teapot on platform
void drawOnPlatform(){
	// Table
	glPushMatrix();
		glColor3f(0.1, 0.1, 0.1);
		glScalef(2.0, 1.2, 1.0);
		glTranslatef(0.50, -1.28, -6.3);	
		table();
	glPopMatrix();
	//Chair
	glPushMatrix();
		glColor3f(0.1, 0.1, 0.1);
		glScalef(1.5, 1.5, 1.5);
		glTranslatef(-1.20, -1.28, -4.5);	
		glRotatef(135, 0, -1.0, 0);
		chair();
	glPopMatrix();
	//Teapot on table
	glPushMatrix();
		glColor3f(0.90, 0.9, 0.9);
		glScalef(0.2, 0.2, 0.2);
		glTranslatef(5.20, -06.9, -31.5);	
		glRotatef(45, 0, -1.0, 0);
		glutSolidTeapot(1);
	glPopMatrix();
}

//Draw dustbin
void drawDustbin(){
	glPushMatrix();
		glScalef(1.5,1.5,1.5);
		glTranslatef(-3.0, -1.7, -5.0);
		dustbin(1);
	glPopMatrix();
}

// Draw 3 lights
void drawLights(){
	//Light 1
	glPushMatrix();
		glRotatef(90, 0.0, 1.0, 0.0);
		glScalef(3.0, 0.1, 0.1);
		glTranslatef(2.0, 14.0 ,-49.5);
		light(1);
	glPopMatrix();
	//Light 2
	glPushMatrix();
		glRotatef(90, 0.0, 1.0, 0.0);
		glScalef(3.0, 0.1, 0.1);
		glTranslatef(0.70, 14.0 ,-49.5);
		light(1);
	glPopMatrix();
	//Light above blackboard
	glPushMatrix();
		//glRotatef(90, 0.0, 1.0, 0.0);
		glScalef(3.0, 0.1, 0.1);
		glTranslatef(0.0, 17.0 ,-79.5);
		light(1);
	glPopMatrix();
}

// draw 2 windows on right wall
void drawWindow(){
	glPushMatrix();
		glTranslatef(4.992, -1.0, -04.0);	
		glScalef(0.7,0.7,1.0);
		window(1);
	glPopMatrix();
	glPushMatrix();
		glTranslatef(4.992, -1.0, -02.0);	
		glScalef(0.7,0.7,1.0);
		window(1);
	glPopMatrix();
}

// Draw door on back wall
void drawDoor(){
	glPushMatrix();
		glTranslatef(3.5, -2.1, -07.98);	
		glScalef(1.2,1.8,1.0);
		glRotatef(90, 0.0, 1.0 ,0.0);
		door(1);
	glPopMatrix();
}

// projection mode is defined 
void project(){
//	glViewport(0,0,w,h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (toggleMode)
	{
		//Perspective
		gluPerspective( fov , asp , 3.0, 300.0);	
	} else	{
		// orthogonal
		glOrtho(-dim*asp, +dim*asp, -dim, +dim, -dim, +dim);
	}
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

// Taking vare of reshape
void reshape(int w, int h){
	asp = (h > 0) ? (double)w/ (double)h : 1;
	glViewport(0,0,w,h);
	project();
}

// handling key Press
void handleKeyPress(unsigned char key, int x, int y){	
	if(key == 27)	exit(0);
	else if( key == 'p' || key == 'P')	toggleAxes = 1 - toggleAxes;
	else if( key == 'v' || key == 'V')	toggleValues = 1 - toggleValues;
	else if( key == 'm' || key == 'M') 	toggleMode = 1 - toggleMode;
	
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
	project();
	glutPostRedisplay();
}

// Handling special keys
void SpecialKeyPress(int key, int x, int y){
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
	glutPostRedisplay();
}

// enabling depth test.
void initRendering(){
	glEnable(GL_DEPTH_TEST);
}

