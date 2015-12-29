/********************************************************************************
 * 	Program to Draw a line using Bresenham's Algorithm  						*
 *  Prgrammed by : Ajinkya S Gavane	, Sudarshan Ghonge, Saurav Agarwalla		*
 *	Using : C++, GLUT,	OpenGL													*
 ********************************************************************************/

#include<iostream>
#include<string.h>
#include<stdlib.h>
#include<GL/glut.h>
#include<math.h>
#include<cstdio>
#include<vector>
#include"energy_minimization.hpp"

//Define globaly window's dimensions
int window_wide = 640;
int window_height = 640;


		// check is to identify if the pixel that is been plotted is the start pixel of
		// a line or end, its a flag
int check = 0;

		// flag type variable to keep track that a pixel is getting stored in
		// the vector once
int pixelFlag = 0;

		//creating start and end pixel coordinates
std::pair<int,int> Start;
std::pair<int,int> End;
		//creating previous to keep track of previous selected pixel and later selected pixel
int previousPixleIndex = 0;
int finalPixelIndex = 0;

int Radius = 10;
		//calculating radius square
int radiusSquare = Radius * Radius;

		//save list of pixels by using vectors and a built in fuction "pair" in cpp
std::vector<std::pair<int,int> > pixel;
std::vector<std::pair<int,int> > new_pixel;

		// structure to save the which point is connected to which pixels
std::vector < std::vector<int> > branch;


		//Adjacency Matrix
double **adjacencyMatrix;
//double **nextAdjacencyMatrix;

/*************Functions Declarations*********************/

		//Initializing OpenGl
void myInit(void);
		//Funciton to plot a pixel
void plotPixel(int x, int y);
		//Function that will enable keyboard interaction to quit graphic window by key
		// 'q' and clear graphic window by key 'c'
void myKey(unsigned char c, int x , int y);
void myKeyForWindow2(unsigned char c, int x, int y);

		// Function to have user interaction using mouse
void myMouse(int button , int status, int x, int y);
void myMouseDoNothing (int button, int status, int x, int y);

		// taking care of window resize
void reshape(int w, int h);

		// this function uses the fact of 8-way symmetry of a circle and plot
		//the circle pixels
void plotCircle(int x, int y, int center_x, int center_y);

		// Fuction to plot the circle
void circleAlgo(int center_x, int center_y, int radius);

		// Functions which makes call to draw lines and circles
void drawLine(void);

		//Checking if the clicked pixel lies in the circle of any previous pixel;
int checkInCircle(std::pair<int,int> &point);

		// Function to create Adjacency Matrix
void createAdjacencyMatrix(double **adjacencyMatrix, int dimension);

		// Function to create new window to display result
void createNewWindowForResult();

		//Function to reDraw the stable Graph
void energyMinimizedGraph();

		//Fuction to fit the output graph within the window by shifting
void shiftPixelsToFitWindowFrame(std::vector< std::pair<int, int> > &new_pixel);

/********** Funtions declaration ends and main function starts**********/
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
	glutCreateWindow("Computer Graphics Assignment: Input");

	//initialize openGL
	myInit();

	//call all the graphic functions
	glutDisplayFunc(drawLine);

	//take keyboard input
	glutKeyboardFunc(myKey);

	//
	glutReshapeFunc(reshape);
	//show everything and stay
	glutMainLoop();

	return 0;
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
	//Forces previously issued OpenGL commands to begin execution,
	//thus guaranteeing that they complete in finite time.
	glFlush();
}

//Function that will enable keyboard interaction to quit graphic window by key
// 'q' and clear graphic window by key 'c'
void myKey(unsigned char c, int x , int y){
		//quit window
	if(c == 'q' || c == 'Q')
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
		branch.clear();
		//set check to 0 so that we can start fresh with a start point
		check = 0;
	}

	//input is completed and proceed to create adjacency matrix;
	if( c == 'd' || c == 'D'){
		glutSetCursor(GLUT_CURSOR_NONE);
		glutMouseFunc(myMouseDoNothing);
		glutSetWindowTitle("Computer Graphics Assignment: Processing");

		int numOfPixel = pixel.size();
		adjacencyMatrix = new double*[numOfPixel];
		//nextAdjacencyMatrix = new double*[numOfPixel];
		for(int i = 0; i < numOfPixel; ++i){
			adjacencyMatrix[i] = new double[numOfPixel];
		}


		for(int i = 0 ; i<numOfPixel; i++){
			for(int j = 0  ; j<numOfPixel ; j++){
				if(i == j)
					adjacencyMatrix[i][j] = 0;
				else
					adjacencyMatrix[i][j] =  INFINITY;
			}
		}
		createAdjacencyMatrix(adjacencyMatrix, numOfPixel);

		//Redraw the New Stable energy minimized graph
		createNewWindowForResult();

	}
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

// this function uses the fact of 8-way symmetry of a circle and plot the circle
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
		/* To be included if points are float
		while(x > end_x){		//xEnd lies on left hand side of xStart
			x += incr_x;
			if( d > 0){
				d+= incrNE;
				y += incr_y;
			}else {
				d += incrE;
			}
			plotPixel(x,y);
		}*/
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
		/* To be included if points are floating points
		while(y > end_y){		//yEnd lies on the left hand side of yStart
			y += incr_y;
			if(d > 0){
				d += incrN;
			}else {
				d+= incrNE;
				x += incr_x;
			}
			plotPixel(x,y);
		}*/
	}

}

void drawLine(void){
		//clear graphic window
	//glClearColor(0.0, 0.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT |GL_DEPTH_BUFFER_BIT);
		// set color of pixel to green
	glColor3f(0.0, 2.27, 0.12);
		// set the pixel size to 2
	glPointSize(2.0);
		// tessting
	plotPixel(-1,-1);
		// call mouse function
	glutMouseFunc(myMouse);
}

// Function to have user interaction using mouse
void myMouse(int button , int status, int x, int y){

	int inCircle;
	// if right click the set check to zero
	if(button == GLUT_RIGHT_BUTTON && status == GLUT_DOWN)
		check = 0;
	// if left click the start plotting pixels
	if(button == GLUT_LEFT_BUTTON && status == GLUT_DOWN){
		if (check == 0){

			// get pixel coordinates of the clicked point
			Start = std::pair<int , int>(x, window_height - y);

			inCircle = checkInCircle(Start);

			if(inCircle == 0)	{
				pixel.push_back(std::pair<int ,int>(Start.first,Start.second));
				//push a empty vector in the branch vector.
				branch.push_back(std::vector<int> ());
			}
			previousPixleIndex = finalPixelIndex;

			// draw circle around the pixel
			circleAlgo(Start.first ,Start.second ,Radius);
			// increment check
			check++;
		}else {
			// get pixel coordinates of the clicked point
			End = std::pair<int , int>(x, window_height - y);

			//Checking if the clicked pixel lies in the circle of any previous pixel;
			inCircle = checkInCircle(End);
			if(inCircle == 0)	{
				pixel.push_back(std::pair<int ,int>(End.first,End.second));
				//push a empty vector in the branch vector.
				branch.push_back(std::vector<int> ());
			}
			branch[previousPixleIndex].push_back(finalPixelIndex);
			branch[finalPixelIndex].push_back(previousPixleIndex);
			previousPixleIndex = finalPixelIndex;
			// draw circle around the pixel
			circleAlgo(End.first ,End.second ,Radius);
			// draw line from start pixel to this pixel
			Bresenham();
			Start = End;
		}

	}

}

//Checking if the clicked pixel lies in the circle of any previous pixel;
int checkInCircle(std::pair<int,int> &point){
	pixelFlag = 0;
	int xp_minus_x, yp_minus_y, distance,xp,yp,i;
	for(i= 0 ; i<pixel.size(); i++){
					xp = pixel[i].first;
					yp = pixel[i].second;
					xp_minus_x = xp - point.first;
					yp_minus_y = yp - point.second;
					distance = (yp_minus_y*yp_minus_y) + (xp_minus_x*xp_minus_x);
					if( distance < radiusSquare ){
						point.first = xp;
						point.second = yp;
						pixelFlag = 1;
						break;
					}
			}
	finalPixelIndex = i;
	return pixelFlag;
}

void myMouseDoNothing (int button, int status, int x, int y){
	glutSetWindowTitle("Computer Graphics Assignment: Processing");
}

// creates adjacency matrix with distances
void createAdjacencyMatrix(double **adjacencyMatrix, int dimension){
	double distance = 0;
	double dx, dy;
	for(int i = 0 ; i<dimension ; i++){
			for(int k = 0 ;  k< branch[i].size(); k++){
				distance = 1;
				adjacencyMatrix[i][branch[i][k]] =  distance;
			}
	}
}

void createNewWindowForResult(){
	glutCreateWindow("Computer Graphics Assignment: Result");
	myInit();
	glutDisplayFunc(energyMinimizedGraph);
	glutKeyboardFunc(myKeyForWindow2);
}

void energyMinimizedGraph(void){
	//clear graphic window
	//glClearColor(0.0, 0.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT |GL_DEPTH_BUFFER_BIT);
		// set color of pixel to green
	glColor3f(0.0, 2.27, 0.12);
		// set the pixel size to 2
	glPointSize(2.0);
	plotPixel(-1,-1);
	//FloydWarshall(nextAdjacencyMatrix, adjacencyMatrix, pixel.size());

	/********Code here will return final pixel sets stored in pixel vector pair****/
	new_pixel.resize(pixel.size());
	minimizeEnergy(pixel, adjacencyMatrix, new_pixel);
	shiftPixelsToFitWindowFrame(new_pixel);

	for(int i = 0 ; i< new_pixel.size() ; i++){
		Start = new_pixel[i];
		circleAlgo(new_pixel[i].first ,new_pixel[i].second ,Radius);
		for(int k = 0 ; k < branch[i].size() ; k++){
			End = new_pixel[branch[i][k]];
			Bresenham();
		}
	}
}

void myKeyForWindow2(unsigned char c, int x, int y){
	if(c == 'q' || c == 'Q')
		exit(1);
}

void shiftPixelsToFitWindowFrame(std::vector< std::pair<int, int> > &new_pixel){
	int dx=0,dy=0;
	for(int i = 0 ; i< new_pixel.size(); i++){
		dx=0;
		dy=0;
		if(new_pixel[i].first < 0)
			dx = 0 - new_pixel[i].first + 2*Radius;

		if(new_pixel[i].first > window_wide)
			dx = window_wide - new_pixel[i].first - 2*Radius;

		if(new_pixel[i].second < 0)
			dy = 0 - new_pixel[i].second + 2*Radius;

		if(new_pixel[i].second > window_height)
			dy = window_height - new_pixel[i].second - 2*Radius ;

		for(int j = 0 ; j< new_pixel.size(); j++){
			new_pixel[j].first = new_pixel[j].first + dx ;
			new_pixel[j].second = new_pixel[j].second + dy ;
		}
	}
}
