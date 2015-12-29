/********************************************************************************
 * 	Program to Draw a Bezier Curve  						*	
 *  Prgrammed by : AJinkya S Gavane	, Sudarshan Ghonge, Saurav Agarwalla		*
 *	Date : 17 Nov 2014															*
 *	Using : C++, GLUT,															*
 *  OpenGL																		*
 ********************************************************************************/
 

#include"surf_rot.h"	
#include"main_declarations.hpp"

int main(int argc, char **argv){
	
	//initialize glut
	glutInit(&argc, argv);	
	
	//Initialize Display Mode
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	
	//initialize the window-size
	glutInitWindowSize(window_wide, window_height);
	
	//Initializee window position
	glutInitWindowPosition(0.0,0.0);
	
	//create Window with a title
	glutCreateWindow("Computer Graphics Assignment:");
	
	//initialize openGL
	myInit();
	
	//call all the graphic functions
	glutDisplayFunc(drawCurve);
	
	//take keyboard input
	glutKeyboardFunc(myKey);
	glutMouseFunc(myMouse);
	glutMotionFunc(myMouseMotion);
	glutReshapeFunc(reshape);
	//show everything and stay
	glutMainLoop();
	
	return 0;
}

void drawCurve(void){
	//clear graphic window
	//glClearColor(0.0, 0.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT |GL_DEPTH_BUFFER_BIT);
	// set color of pixel to green
	glColor3f(0.0, 2.27, 0.12);
	// set the pixel size to 2
	glPointSize(2.0);
	//Draw all the points currently in the array and circle them
        drawAllControlPoints();
        //Draw all the lines joining the points in sequential order
        drawAllLines();
        //Draw the Bezier Curve
        bezier();
        glFlush();        
}	

//Initializing OpenGl
void myInit(void){
	// set window background
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	//set projections
	glViewport (0, 0, window_wide, window_height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, window_wide, 0.0, window_height);	
}

//Funciton to plot a pixel
void plotPixel(int x, int y){
	//bigin plotting
	glBegin(GL_POINTS);
	//plot integer point
	glVertex2i(x,y);
	//end
	glEnd();
}

//Function that will enable keyboard interaction to quit graphic window by key
// 'Esc' and clear graphic window by key 'c'
void myKey(unsigned char c, int x , int y){
		//quit window
	if(c == 27)
		exit(0);	
		//clear window buffer
	if( c == 'c' || c == 'C'){
		//this function will clear window buffer
		//glClearColor(0.0, 0.0, 0.0, 1.0);
		glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
		// this will refresh window screen
		glutPostRedisplay();
		// this will clear all the pixels that were saved;
		pixel.clear();
		//set check to 0 so that we can start fresh with a start point 
		check = 0;
	}
	
	//testing to see if pixel are getting saved properly
	if (c == 'e' || c == 'E')
	{
		edit_flag = 1;
		check = -1;
		flag_bezier = 0;
	}
	
	//Rotate around the x axis and store in file "sur_rot_x.off"
	if(c=='x' || c == 'X')
	{
	       surfaceRotation(pixel, c); 
	}
	//Rotate around the y axis and store in file "sur_rot_y.off"
	if(c=='y' || c == 'Y')
	{
	       surfaceRotation(pixel, c); 
	}
}

// Function to have user interaction using mouse
void myMouse(int button , int status, int x, int y){

	int inCircle;
	// if right click the set check to zero
	if(button == GLUT_RIGHT_BUTTON && status == GLUT_DOWN)
		check = 0;
	// if left click the start plotting pixels
	if(button == GLUT_LEFT_BUTTON && status == GLUT_DOWN){
		if (check == 0 && edit_flag == 0){
			
			// get pixel coordinates of the clicked point
			Start = std::pair<int , int>(x, window_height - y);
			
			inCircle = checkInCircle(Start);
			
			if(inCircle == 0)	{
				pixel.push_back(std::pair<int ,int>(Start.first,Start.second));
				flag_bezier++;
			}
			previousPixleIndex = finalPixelIndex;
			// increment check
			check++;
			
		}else if (check != -1 && edit_flag == 0) {
			// get pixel coordinates of the clicked point
			End = std::pair<int , int>(x, window_height - y);
			
			//Checking if the clicked pixel lies in the circle of any previous pixel;
			inCircle = checkInCircle(End);
			if(inCircle == 0)	{
				pixel.push_back(std::pair<int ,int>(End.first,End.second));	
				//flag_bezier++;	
			}
			previousPixleIndex = finalPixelIndex;
			// draw circle around the pixel
			//circleAlgo(End.first ,End.second ,Radius);
			// draw line from start pixel to this pixel
			//Bresenham();	
			Start = End;	
		}
		if(edit_flag == 1 && check == -1){
			std::cout<<"Select Pixel\n";
			editPixel = std::pair<int , int > (x, window_height - y);
		}	
	}
	if(button == GLUT_MIDDLE_BUTTON && status == GLUT_DOWN)
	{
	        End = std::pair<int , int>(x, window_height - y);
	        edit_point = checkInCircle(End);
	}       
	if(button == GLUT_MIDDLE_BUTTON && status == GLUT_UP)
	{
	    edit_point = -1;    
	}
	glutPostRedisplay();		        
}
void myMouseMotion(int x, int y)
{
	if (edit_point > -1)
	{
                End = std::pair<int , int>(x, window_height - y);
	        pixel[edit_point].first = End.first;
	        pixel[edit_point].second = End.second; 
		glutPostRedisplay();
	}
}

void drawAllControlPoints()
{
        for(int i=0; i<pixel.size(); i++)
        {
                plotPixel(pixel[i].first, pixel[i].second);
                circleAlgo(pixel[i].first, pixel[i].second, Radius);
        }
        glFlush();
}

void drawAllLines()
{
        for(int i=0; i+1<pixel.size(); i++)
        {
                Start = pixel[i];
                End = pixel[i+1];
                Bresenham();       
        }
        glFlush();       
}

// Taking care of window resize;
void reshape(int w, int h){
	glViewport(0,0,(GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, (GLdouble) w, 0.0, (GLdouble) h);
	window_wide = w;
	window_height = h;
	check = 0;
}

// this function uses the 8-way symmetry of a circle and plots the circle 
// pixels
void plotCircle(int x, int y, int center_x, int center_y){
	//1st quadrant
	plotPixel(x + center_x, y + center_y);
	plotPixel(y + center_x, x + center_y);
	
	//2nd quadrant
	plotPixel(-x + center_x,y + center_y);
	plotPixel(-y + center_x,x + center_y);
	
	//3rd quadrant
	plotPixel(-x + center_x,-y + center_y);
	plotPixel(-y + center_x,-x + center_y);
	
	//4th quadrant
	plotPixel(x + center_x,-y + center_y);
	plotPixel(y + center_x,-x + center_y);
}

// Fuction to plot the circle
void circleAlgo(int center_x, int center_y, int radius){
	plotPixel(center_x, center_y);
	int x = 0;
	int y =  radius;
	int d = 1 - radius;
	int incrE = 3;
	int incrSE = -2*radius + 5;
	plotCircle(x,y,center_x,center_y);
	//plotPixel(x,y);
	while(y > x){
		if( d < 0){ 	//select E point , midpoint lies inside the circle
			d += incrE;
			incrE += 2;
			incrSE += 2;
		} else {		// select SE point, midpoint lies outside the circle
			d += incrSE;
			incrE += 2;
			incrSE += 4;
			y--;
		}
		x++;
		plotCircle(x,y,center_x,center_y);
	}
}

// Fuction to draw line 
void Bresenham(){
	// declaring temporary variables
	int x,y,end_x, end_y,d, incr_x, incr_y;

	int dx = End.first - Start.first;
	int dy = End.second - Start.second;
	
	// to decide whether to increment x,y by 1 or -1 depending on the postion of 
	// start and end coordinates of the line segment
	incr_x = (dx > 0) ? 1 : -1;
	incr_y = (dy > 0) ? 1 : -1;
	
	// initialization of temporary variables
		x = Start.first;
		y = Start.second;
		end_x = End.first;
		end_y = End.second;
	
	dx = fabs(dx);
	dy = fabs(dy);
	
	// calculating increments
	int incrE = 2*dy;
	int incrNE = 2*dy  - 2*dx;
	int incrN = -2*dx;
	plotPixel(x,y);
	circleAlgo(End.first ,End.second ,Radius);
		
	if(dx >= dy){	// slope of line is less than 1
		d = 2*dy - dx;	//Initializing d
		while(x != end_x){		// xEnd lies on the right hand side of xStart
			x += incr_x;
			if( d > 0){		
				d+= incrNE;
				y += incr_y;
			}else {
				d += incrE;
			}			
			plotPixel(x,y);
		}
		
	} else {				// slope of line is greater than 1
		d = dy - 2*dx;		//Initializing d;
		while(y != end_y){		//yEnd lies on the right hand side of yStart
			y += incr_y;
			if(d > 0){
				d += incrN;
			}else {
				d+= incrNE;
				x += incr_x;
			}
			plotPixel(x,y);
		}
	}	
}

//Checking if the clicked pixel lies in the circle of any previous pixel;
int checkInCircle(std::pair<int,int> &point){
	pixelFlag = 0;
	int xp_minus_x, yp_minus_y, distance,xp,yp;
	unsigned int i;
	for(i= 0 ; i<pixel.size(); i++){
					xp = pixel[i].first;
					yp = pixel[i].second;
					xp_minus_x = xp - point.first;
					yp_minus_y = yp - point.second;
					distance = (yp_minus_y*yp_minus_y) + (xp_minus_x*xp_minus_x);
					if( distance < radiusSquare ){
						point.first = xp;
						point.second = yp;
						pixelFlag = i;
						break;	
					}
			}
	//return point;
	finalPixelIndex = i;
	return pixelFlag;
}

void bezier(){
	if(pixel.size()<4)
	        return;
	dpixel.resize(pixel.size());
	for(int i=0; i<pixel.size(); i++)
	{
                dpixel[i].first = (double)pixel[i].first;
	        dpixel[i].second = (double)pixel[i].second;		        
        }
	glColor3f(1.0,0.0,0.0);
	std::pair<double, double> curve;
	double t = 0.0;
	double dt = 0.001;
		
	while (t<=1)
	{
                curve = Lerp2d(dpixel, t);
		plotPixel((int)curve.first, (int)curve.second);
//		std::cout<<curveX<<"\t"<<curveY<<"\n";
		t += dt;
	}
	glColor3f(0.0, 2.27, 0.12);
	glFlush();
}

std::pair<double, double> Lerp2d(std::vector<std::pair<double, double>> a, double t)
{
        std::vector<std::pair<double, double>> b(a.size()-1);
        if(a.size()==2)
        {
                b[0].first = a[0].first*(1-t) + a[1].first*t;
                b[0].second = a[0].second*(1-t) + a[1].second*t;
                return b[0];                
                
        }
        
        for(int i=0; i<a.size()-1; i++)
        {
                b[i].first = a[i].first*(1-t) + a[i+1].first*t;
                b[i].second = a[i].second*(1-t) + a[i+1].second*t;                
        }
        
        return Lerp2d(b, t);
}
