//Globals
#include "parse_mesh.hpp"
double dz = 0.5, dx = 1.2, dy = 0.50;
double dim = 3.0;
int windowWidth = 700;
int windowHeight = 650;
double lookX = 0.0, lookY = -0.0, lookZ = -0.1;
std::vector<Polygon> p_list; 
std::vector<vector3d_t> v_list;
//Special Globals
double eyeX = 0.0, eyeY = 20.0, eyeZ  = 100.0;		// Camera coordinates
int toggleAxes = 0;				// Toggle Axes on/off
int toggleValues = 1;			// Toggle Values on/off
int toggleMode = 1; 			// toggle Mode on/off
int theta = 0;					//azimuth of view angle 
int phi = 0;					// elevation of view angle
int fov = 60;					// field of view for perspective
int asp = 1; 					// aspect ratio


void parseDisplay();
void handleKeyPress(unsigned char key, int x, int y);
void SpecialKeyPress(int key, int x, int y);
void project();

int main(int argc, char **argv)
{
	parseMesh(p_list, v_list);
	//printf("File read done. Detected %d vertices and %d faces\n", v_list.size(), p_list.size());
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
	glutInitWindowSize(windowWidth,windowHeight);
	glutCreateWindow("Assignment 3");   
        glutDisplayFunc(parseDisplay);
        glutKeyboardFunc(handleKeyPress);
        glutSpecialFunc(SpecialKeyPress);
        glutMainLoop();
	return 0;
        

}

void parseDisplay()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	glClearColor(0.8,0.9,1.0,1.0);
	glLoadIdentity();
	// Perspective - set eye position
	if(toggleMode){			
		//printAt(5, 45, "eyeX, eyeY, eyeZ :(%d, %d, %d)", eyeX, eyeY , eyeZ);
		gluLookAt(eyeX , eyeY, eyeZ, eyeX + lookX , eyeY + lookY, eyeZ + lookZ, 0, 4.0, 0);
	} else {
		glRotatef(phi, 1, 0, 0);
		glRotatef(theta, 0, 1, 0);
	}
	glPushMatrix();
	glScalef(0.1,0.1,0.1);
	//glTranslatef(0.0, 10.0, -200.0);
	glColor3f(0.4, 0.0, 0.4);
	for(int i=0; i<p_list.size(); i++)
        {
                p_list[i].drawSelf(v_list);
        }
        glPopMatrix();
        //printf("Finished drawing vertices\n");
        
        glFlush();
	glutSwapBuffers();
	        
}

void project()
{
//	glViewport(0,0,w,h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (toggleMode)
	{
		//Perspective
		gluPerspective( fov , asp , 1.0, 500.0);	
	} else	{
		// orthogonal
		glOrtho(-dim*asp, +dim*asp, -dim, +dim, -dim, +dim);
	}
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void handleKeyPress(unsigned char key, int x, int y)
{	
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
		if(1/*theta > -65*/){
			theta -= 3;
			lookX = Sin(theta);
			lookZ = -Cos(theta);
		}
	}
	if( key == 'd' || key == 'D'){	// look right
		if(1/*theta < 65*/){
			theta += 3;
			lookX = Sin(theta);
			lookZ = -Cos(theta);
		}
	}
	if( key == 'w' || key == 'W'){	// look up
		if(1/*phi < 60*/){
			phi += 3;
			lookY = Sin(phi);
			lookZ = -Cos(phi);
		}
	}
	if( key == 's' || key == 'S'){	// look down
		if(/*phi > -60*/1){
			phi -= 3;
			lookY = Sin(phi);
			lookZ = -Cos(phi);
		}
	}
	project();
	glutPostRedisplay();
}

void SpecialKeyPress(int key, int x, int y){
	// Walk rightward
	if(key == GLUT_KEY_RIGHT){
		//if(eyeX < 4)
			eyeX += dx;
	} 
	// Walk leftward
	if(key == GLUT_KEY_LEFT){
		//if(eyeX > -4)
			eyeX -= dx;
	}
	// walk forward
	if(key == GLUT_KEY_UP){
		//if(eyeZ > -1)
			eyeZ -= dz;
	}
	// walk backwards
	if(key == GLUT_KEY_DOWN) {
		//if(eyeZ < 10)
			eyeZ += dz;
	}
	// move camera up
	if( key == GLUT_KEY_PAGE_UP){
		//if(eyeY < 4)
			eyeY += dy;
	}
	// move camera Up along up vector
	if( key == GLUT_KEY_PAGE_DOWN){
		//if (eyeY >-3)
			eyeY -= dy;
	}
	
//	keep angle to +/- 360 degrees
	theta %= 360;
	phi %= 360;
	glutPostRedisplay();
}

