#include "screencasts.h"

void DrawParallelopiped(GLfloat sizeX, GLfloat sizeY, GLfloat sizeZ, GLenum type){
	static GLfloat n[6][3] ={
							{-1.0, 0.0, 0.0},
							{0.0, 1.0, 0.0},
							{1.0, 0.0, 0.0},
							{0.0, -1.0, 0.0},
							{0.0, 0.0, 1.0},
							{0.0, 0.0, -1.0}
							};

	static GLint faces[6][4] ={
								{0, 1, 2, 3},
								{3, 2, 6, 7},
								{7, 6, 5, 4},
								{4, 5, 1, 0},
								{5, 6, 2, 1},
								{7, 4, 0, 3}
							};

	GLfloat v[8][3];
	GLint i;

	v[0][0] = v[1][0] = v[2][0] = v[3][0] = -sizeX / 2;
	v[4][0] = v[5][0] = v[6][0] = v[7][0] = sizeX / 2;
	v[0][1] = v[1][1] = v[4][1] = v[5][1] = -sizeY / 2;
	v[2][1] = v[3][1] = v[6][1] = v[7][1] = sizeY / 2;
	v[0][2] = v[3][2] = v[4][2] = v[7][2] = -sizeZ / 2;
	v[1][2] = v[2][2] = v[5][2] = v[6][2] = sizeZ / 2;

	for (i = 5; i >= 0; i--) {
		glBegin(type);
			glNormal3fv(&n[i][0]);
			glVertex3fv(&v[faces[i][0]][0]);
			glVertex3fv(&v[faces[i][1]][0]);
			glVertex3fv(&v[faces[i][2]][0]);
			glVertex3fv(&v[faces[i][3]][0]);
		glEnd();
	}
}

void platform(GLfloat sizeX){

		static GLfloat n[6][3] ={
							{-1.0, 0.0, 0.0},
							{0.0, 1.0, 0.0},
							{1.0, 0.0, 0.0},
							{0.0, -1.0, 0.0},
							{0.0, 0.0, 1.0},
							{0.0, 0.0, -1.0}
							};

	static GLint faces[6][4] ={
								{0, 1, 2, 3},
								{3, 2, 6, 7},
								{7, 6, 5, 4},
								{4, 5, 1, 0},
								{5, 6, 2, 1},
								{7, 4, 0, 3}
							};

	GLfloat v[8][3];
	GLint i;

	v[0][0] = v[1][0] = v[2][0] = v[3][0] = -sizeX / 2;
	v[4][0] = v[5][0] = v[6][0] = v[7][0] = sizeX / 2;
	v[0][1] = v[1][1] = v[4][1] = v[5][1] = -sizeX / 2;
	v[2][1] = v[3][1] = v[6][1] = v[7][1] = sizeX / 2;
	v[0][2] = v[3][2] = v[4][2] = v[7][2] = -sizeX / 2;
	v[1][2] = v[2][2] = v[5][2] = v[6][2] = sizeX / 2;

	for (i = 5; i >= 0; i--) {
		glBegin(GL_QUADS);
			glNormal3fv(&n[i][0]);
				glColor3f(0.74, 0.72, 0.42);
			if( i  == 4) glColor3f(0.0, 0.0, 0.0);		//Light
			glVertex3fv(&v[faces[i][0]][0]);
			if(i == 4)	glColor3f(0.10, 0.270 , 0.120);		
			glVertex3fv(&v[faces[i][1]][0]);
				glColor3f(0.930, 0.910, 0.670);
			if(i == 4)	glColor3f(0.10, 0.270, 0.12);
			glVertex3fv(&v[faces[i][2]][0]);
				glColor3f(0.930, 0.910, 0.670);		
			if(i == 4)	glColor3f(0.10, 0.0, 0.0);
			glVertex3fv(&v[faces[i][3]][0]);
		glEnd();
	}
}

void blackBoard(GLfloat sizeX){

		static GLfloat n[6][3] ={
							{-1.0, 0.0, 0.0},
							{0.0, 1.0, 0.0},
							{1.0, 0.0, 0.0},
							{0.0, -1.0, 0.0},
							{0.0, 0.0, 1.0},
							{0.0, 0.0, -1.0}
							};

	static GLint faces[6][4] ={
								{0, 1, 2, 3},
								{3, 2, 6, 7},
								{7, 6, 5, 4},
								{4, 5, 1, 0},
								{5, 6, 2, 1},
								{7, 4, 0, 3}
							};

	GLfloat v[8][3];
	GLint i;

	v[0][0] = v[1][0] = v[2][0] = v[3][0] = -sizeX / 2;
	v[4][0] = v[5][0] = v[6][0] = v[7][0] = sizeX / 2;
	v[0][1] = v[1][1] = v[4][1] = v[5][1] = -sizeX / 2;
	v[2][1] = v[3][1] = v[6][1] = v[7][1] = sizeX / 2;
	v[0][2] = v[3][2] = v[4][2] = v[7][2] = -sizeX / 2;
	v[1][2] = v[2][2] = v[5][2] = v[6][2] = sizeX / 2;

	for (i = 5; i >= 0; i--) {
		glBegin(GL_QUADS);
			glNormal3fv(&n[i][0]);
				glColor3f(0.80, 0.40, 0.0);
			if( i  == 4) glColor3f(0.0, 0.0, 0.0);
			glVertex3fv(&v[faces[i][0]][0]);
			if(i == 4)	glColor3f(0.0, 0.270 , 0.120);
			glVertex3fv(&v[faces[i][1]][0]);
			if(i == 4)	glColor3f(0.0, 0.270, 0.12);
			glVertex3fv(&v[faces[i][2]][0]);
			if(i == 4)	glColor3f(0.0, 0.0, 0.0);
			glVertex3fv(&v[faces[i][3]][0]);
		glEnd();
	}
}

void drawDesk(GLfloat sizeX){
	static GLfloat n[6][3] ={
							{-1.0, 0.0, 0.0},
							{0.0, 1.0, 0.0},
							{1.0, 0.0, 0.0},
							{0.0, -1.0, 0.0},
							{0.0, 0.0, 1.0},
							{0.0, 0.0, -1.0}
							};

	static GLint faces[6][4] ={
								{0, 1, 2, 3},
								{3, 2, 6, 7},
								{7, 6, 5, 4},
								{4, 5, 1, 0},
								{5, 6, 2, 1},
								{7, 4, 0, 3}
							};

	GLfloat v[8][3];
	GLint i;

	v[0][0] = v[1][0] = v[2][0] = v[3][0] = -sizeX / 2;
	v[4][0] = v[5][0] = v[6][0] = v[7][0] = sizeX / 2;
	v[0][1] = v[1][1] = v[4][1] = v[5][1] = -sizeX / 2;
	v[2][1] = v[3][1] = v[6][1] = v[7][1] = sizeX / 2;
	v[0][2] = v[3][2] = v[4][2] = v[7][2] = -sizeX / 2;
	v[1][2] = v[2][2] = v[5][2] = v[6][2] = sizeX / 2;

	for (i = 5; i >= 0; i--) {
		glBegin(GL_QUADS);
			glNormal3fv(&n[i][0]);
				glColor3f(0.80, 0.40, 0.0);
			if( i  == 4 || i == 2) glColor3f(0.0, 0.0, 0.0);
			glVertex3fv(&v[faces[i][0]][0]);
				glColor3f(0.6,0.2,0.0);
			if(i == 4 || i == 2)	glColor3f(0.5, 0.3, 0.1);
			glVertex3fv(&v[faces[i][1]][0]);
				glColor3f(0.6,0.2,0.0);
			if(i == 4 || i == 2)	glColor3f(0.5, 0.3, 0.1);
			glVertex3fv(&v[faces[i][2]][0]);
				glColor3f(0.80, 0.40, 0.0);		
			if(i == 4 || i == 2)	glColor3f(0.10, 0.0, 0.0);
			glVertex3fv(&v[faces[i][3]][0]);
		glEnd();
	}
}

void tableLeg(GLfloat sizeX){
	static GLfloat n[6][3] ={
							{-1.0, 0.0, 0.0},
							{0.0, 1.0, 0.0},
							{1.0, 0.0, 0.0},
							{0.0, -1.0, 0.0},
							{0.0, 0.0, 1.0},
							{0.0, 0.0, -1.0}
							};

	static GLint faces[6][4] ={
								{0, 1, 2, 3},
								{3, 2, 6, 7},
								{7, 6, 5, 4},
								{4, 5, 1, 0},
								{5, 6, 2, 1},
								{7, 4, 0, 3}
							};

	GLfloat v[8][3];
	GLint i;

	v[0][0] = v[1][0] = v[2][0] = v[3][0] = -sizeX / 2;
	v[4][0] = v[5][0] = v[6][0] = v[7][0] = sizeX / 2;
	v[0][1] = v[1][1] = v[4][1] = v[5][1] = -sizeX / 2;
	v[2][1] = v[3][1] = v[6][1] = v[7][1] = sizeX / 2;
	v[0][2] = v[3][2] = v[4][2] = v[7][2] = -sizeX / 2;
	v[1][2] = v[2][2] = v[5][2] = v[6][2] = sizeX / 2;

	for (i = 5; i >= 0; i--) {
		glBegin(GL_QUADS);
			glNormal3fv(&n[i][0]);
			
				glColor3f(0.75, 0.75, 0.75);
			
			if( i  == 4 || i == 2) glColor3f(0.0, 0.0, 0.0);
			glVertex3fv(&v[faces[i][0]][0]);
				glColor3f(0.75, 0.75, 0.75);
			if(i == 4 || i == 2)	glColor3f(0.0, 0.0, 0.0);
			glVertex3fv(&v[faces[i][1]][0]);
				glColor3f(0.75, 0.75, 0.75);
			if(i == 4 || i == 2)	glColor3f(0.70, 0.70, 0.70);
			glVertex3fv(&v[faces[i][2]][0]);
				glColor3f(0.75, 0.75, 0.75);	
			if(i == 4 || i == 2)	glColor3f(0.700, 0.70, 0.70);
			glVertex3fv(&v[faces[i][3]][0]);
		glEnd();
	}
}

void table(){
	//desk
	glColor3f(0.5, 0.3, 0.1);
	glPushMatrix();		
		glScalef(1.0,0.07,0.50);
		drawDesk(1);
	glPopMatrix();
	//left leg
	glColor3f(0.75, 0.75, 0.75);
	glPushMatrix();
		glScalef(0.03,0.80,0.50);
		glTranslatef(-13.5, -0.5, 0.0);
		tableLeg(1);
	glPopMatrix();
	//right leg
	glPushMatrix();
		glScalef(0.03,0.80,0.50);
		glTranslatef(13.5, -0.5, 0.0);
		tableLeg(1);
	glPopMatrix();
	// khalcha kappa
	glColor3f(0.1, 0.1, 0.1);
	glPushMatrix();
		glScalef(0.80,0.05,0.50);
		glTranslatef(0.0,-2.5,0.0);
		glutSolidCube(1);
	glPopMatrix();	
}

void chairLeg(GLfloat sizeX){
	static GLfloat n[6][3] ={
							{-1.0, 0.0, 0.0},
							{0.0, 1.0, 0.0},
							{1.0, 0.0, 0.0},
							{0.0, -1.0, 0.0},
							{0.0, 0.0, 1.0},
							{0.0, 0.0, -1.0}
							};

	static GLint faces[6][4] ={
								{0, 1, 2, 3},
								{3, 2, 6, 7},
								{7, 6, 5, 4},
								{4, 5, 1, 0},
								{5, 6, 2, 1},
								{7, 4, 0, 3}
							};

	GLfloat v[8][3];
	GLint i;

	v[0][0] = v[1][0] = v[2][0] = v[3][0] = -sizeX / 2;
	v[4][0] = v[5][0] = v[6][0] = v[7][0] = sizeX / 2;
	v[0][1] = v[1][1] = v[4][1] = v[5][1] = -sizeX / 2;
	v[2][1] = v[3][1] = v[6][1] = v[7][1] = sizeX / 2;
	v[0][2] = v[3][2] = v[4][2] = v[7][2] = -sizeX / 2;
	v[1][2] = v[2][2] = v[5][2] = v[6][2] = sizeX / 2;

	for (i = 5; i >= 0; i--) {
		glBegin(GL_QUADS);
			glNormal3fv(&n[i][0]);
				glColor3f(0.60,0.60,0.60);
			if( i  == 4 || i == 2) glColor3f(0.0, 0.0, 0.0);
			glVertex3fv(&v[faces[i][0]][0]);
				glColor3f(0.6,0.2,0.0);
			if(i == 4 || i == 2)	glColor3f(0.4, 0.2, 0.0);
			glVertex3fv(&v[faces[i][1]][0]);
				glColor3f(0.6,0.2,0.0);
			if(i == 4 || i == 2)	glColor3f(0.4, 0.2, 0.0);
			glVertex3fv(&v[faces[i][2]][0]);
				glColor3f(0.80, 0.40, 0.0);		
			if(i == 4 || i == 2)	glColor3f(0.10, 0.0, 0.0);
			glVertex3fv(&v[faces[i][3]][0]);
		glEnd();
	}
}

void chair(){
	//Resting part
	//back  up support left
	glColor3f(0.52, 0.37, 0.15);
	glPushMatrix();
		glScalef(0.07,0.5,0.07);
		glTranslatef(-2.7,0.5,2.7);
		glutSolidCube(1);
	glPopMatrix();
	//back up support right
	glColor3f(0.52, 0.37, 0.15);
	glPushMatrix();
		glScalef(0.07,0.5,0.07);
		glTranslatef(2.7,0.5,2.7);
		glutSolidCube(1);
	glPopMatrix();
	//Resting plank
	glColor3f(0.5, 0.3, 0.1);
	glPushMatrix();
		glScalef(0.4,0.3,0.07);
		glTranslatef(0.0,1.0,2.0);
		drawDesk(1);
	glPopMatrix();
	
	//seat
	glColor3f(0.45, 0.25, 0.05);
	glPushMatrix();
		glScalef(0.50,0.07,0.50);
		drawDesk(1);
	glPopMatrix();
	//legs
	glColor3f(0.60,0.60,0.60);
	//forward left
	glPushMatrix();
		glScalef(0.07,0.4,0.07);
		glTranslatef(-2.7,-0.5,-2.7);
		chairLeg(1);
	glPopMatrix();
	//forward right
	glPushMatrix();
		glScalef(0.07,0.4,0.07);
		glTranslatef(2.7,-0.5,-2.7);
		chairLeg(1);
	glPopMatrix();
	//back left
	glPushMatrix();
		glScalef(0.07,0.4,0.07);
		glTranslatef(-2.7,-0.5,2.7);
		chairLeg(1);
	glPopMatrix();
	//back right
	glPushMatrix();
		glScalef(0.07,0.4,0.07);
		glTranslatef(2.7,-0.5,2.7);
		chairLeg(1);
	glPopMatrix();
}

void bench(){
	glPushMatrix();
		table();
		glPushMatrix();
			glTranslatef(0.0, -0.4, 0.5);
			chair();
		glPopMatrix();
	glPopMatrix();
}

void dustbin(GLfloat sizeX){
	//Left face
	glColor3f(0.0,0.0,0.0);
	glPushMatrix();
		glScalef(0.02,0.3,0.2);
		glTranslatef(-5.5,-0.5,0.0);
		glutSolidCube(1);
	glPopMatrix();
	//Right Face
	glPushMatrix();		
		glScalef(0.02,0.3,0.2);
		glTranslatef(5.5,-0.5,0.0);
		glutSolidCube(1);
	glPopMatrix();
	// BackFace
	glColor3f(1.0,1.0,1.0);
	glPushMatrix();		
		glScalef(0.2,0.3,0.02);
		glTranslatef(0.0,-0.5,-4.2);
		glutSolidCube(1);
	glPopMatrix();
	// Front Face
	glPushMatrix();		
		glScalef(0.2,0.3,0.02);
		glTranslatef(0.0,-0.5,4.2);
		glutSolidCube(1);
	glPopMatrix();
	//Bottom Face
	glColor3f(1.0,.0,.0);
	glPushMatrix();		
		glScalef(0.2,0.02,0.2);
		glTranslatef(0.0,-14.5,0.0);
		glutSolidCube(1);
	glPopMatrix();
}

void light(GLfloat sizeX){
	static GLfloat n[6][3] ={
							{-1.0, 0.0, 0.0},
							{0.0, 1.0, 0.0},
							{1.0, 0.0, 0.0},
							{0.0, -1.0, 0.0},
							{0.0, 0.0, 1.0},
							{0.0, 0.0, -1.0}
							};

	static GLint faces[6][4] ={
								{0, 1, 2, 3},
								{3, 2, 6, 7},
								{7, 6, 5, 4},
								{4, 5, 1, 0},
								{5, 6, 2, 1},
								{7, 4, 0, 3}
							};

	GLfloat v[8][3];
	GLint i;

	v[0][0] = v[1][0] = v[2][0] = v[3][0] = -sizeX / 2;
	v[4][0] = v[5][0] = v[6][0] = v[7][0] = sizeX / 2;
	v[0][1] = v[1][1] = v[4][1] = v[5][1] = -sizeX / 2;
	v[2][1] = v[3][1] = v[6][1] = v[7][1] = sizeX / 2;
	v[0][2] = v[3][2] = v[4][2] = v[7][2] = -sizeX / 2;
	v[1][2] = v[2][2] = v[5][2] = v[6][2] = sizeX / 2;

	for (i = 5; i >= 0; i--) {
		glBegin(GL_QUADS);
			glNormal3fv(&n[i][0]);
				glColor3f(01.0, 1.40, 10.0);
			if( i  != 4) glColor3f(0.0, 0.0, 0.0);
			glVertex3fv(&v[faces[i][0]][0]);
			if(i != 4)	glColor3f(0.70, 0.70 , 0.70);
			glVertex3fv(&v[faces[i][1]][0]);
			if(i != 4)	glColor3f(0.70, 0.70, 0.72);
			glVertex3fv(&v[faces[i][2]][0]);
			if(i != 4)	glColor3f(0.0, 0.0, 0.0);
			glVertex3fv(&v[faces[i][3]][0]);
		glEnd();
	}
}

void window(GLfloat sizeX){
	glPushMatrix();
		glBegin(GL_QUADS);
			glColor3f(0.8,0.9,1.0);		//background color
			glVertex3d(0.01, 1, 1.0);
			glVertex3d(0.01, 1, -0.5 );
			glVertex3d(0.01, -0.5, -0.5);
			glVertex3d(0.01, -0.5, 1.0);
		
				glColor3f(0.54, 0.270, 0.07);	// windowPane color		
			glVertex3d(0,-0.5,-0.5);
			glVertex3d(0,1, -0.5);
				glColor3f(0.72, 0.52, 0.04);	// windowPane color
			glVertex3d(0,0.75,0);
			glVertex3d(0,-0.25,0);
			
				glColor3f(0.54, 0.270, 0.07);	// windowPane color	
			glVertex3d(0,-0.5,1.0);
			glVertex3d(0,1, 1.0);
				glColor3f(0.72, 0.52, 0.04);	// windowPane color	
			glVertex3d(0,0.75,0.5);
			glVertex3d(0,-0.25,0.5);
		glEnd();
	glPopMatrix();
	
	
}

void door(GLfloat sizeX){
	glPushMatrix();
		glBegin(GL_QUADS);
		glColor3f(0.8,0.9,1.0);		//background color
		glVertex3d(0.01, 1, 1.0);
		glVertex3d(0.01, 1, -0.5 );
		glVertex3d(0.01, -0.5, -0.5);
		glVertex3d(0.01, -0.5, 1.0);
		
			glColor3f(0.540, 0.0, 0.0);	// door color		
		glVertex3d(0,-0.5,-0.5);
		glVertex3d(0,1, -0.5);
			glColor3f(0.72, 0.13, 0.13);	// d00r color
		glVertex3d(0,0.75,0);
		glVertex3d(0,-0.25,0);
			
			glColor3f(0.540, 0.0, 0.0);	// d00r color	
		glVertex3d(0,-0.5,1.0);
		glVertex3d(0,1, 1.0);
			glColor3f(0.72, 0.13, 0.13);	// door color	
		glVertex3d(0,0.75,0.5);
		glVertex3d(0,-0.25,0.5);
		glEnd();
	glPopMatrix();
}
