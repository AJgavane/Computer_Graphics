//Define globaly window's dimensions
int window_wide = 680;
int window_height = 680;
int flag_bezier = 0;
		
// check is to identify if the pixel that is been plotted is the start pixel of
// a line or end, its a flag
int check = 0;
int edit_flag = 0;
//Variable to see if the pixel is being edited
int edit_point=-1;
// flag type variable to keep track that a pixel is getting stored in
// the vector once
int pixelFlag = 0;
		
//creating start and end pixel coordinates 
std::pair<int,int> Start;
std::pair<int,int> End;
std::pair<int,int> editPixel;
std::pair<int,int> newPixel;
//creating previous to keep track of previous selected pixel and later selected pixel
int previousPixleIndex = 0;
int finalPixelIndex = 0;
int pixelSelected;
int Radius = 10;
		//calculating radius square
int radiusSquare = Radius * Radius;

		//save list of pixels by using vectors and a built in fuction "pair" in cpp
std::vector<std::pair<int,int> > pixel;
std::vector<std::pair<double, double>> dpixel; //pixel in double

/*************Functions Declarations*********************/

		//Initializing OpenGl
void myInit(void);
//Funciton to plot a pixel
void plotPixel(int x, int y);
//Function that will enable keyboard interaction to quit graphic window by key
// 'q' and clear graphic window by key 'c'
void myKey(unsigned char c, int x , int y);

		// Function to have user interaction using mouse
void myMouse(int button , int status, int x, int y);

void myMouseMotion(int x, int y);
// taking care of window resize
void reshape(int w, int h);

// this function uses the fact of 8-way symmetry of a circle and plot 
//the circle pixels
void plotCircle(int x, int y, int center_x, int center_y);

// Fuction to plot the circle
void circleAlgo(int center_x, int center_y, int radius);

//Bresenham line drawing algo
void Bresenham();
		
// Functions which makes call to draw lines and circles
void drawCurve(void);
//Function which draws all control points
void drawAllControlPoints();
//Function which draws all lines joining the bezier control points
void drawAllLines();
//Draws the n-th order bezier curve
void bezier();

//Checking if the clicked pixel lies in the circle of any previous pixel;
int checkInCircle(std::pair<int,int> &point);
//Linearly approximated point using the control points
std::pair<double, double> Lerp2d(std::vector<std::pair<double, double>> a, double t);
