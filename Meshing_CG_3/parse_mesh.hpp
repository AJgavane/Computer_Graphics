#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include<iostream>
#include<tuple>
#include<vector>
/* OpenGL and friends */
#ifdef USEGLEW
#include <GL/glew.h>
#endif
#define GL_GLEXT_PROTOTYPES
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#define first(x) std::get<0>(x)
#define second(x) std::get<1>(x)
#define third(x) std::get<2>(x)
#define Cos(theta) cos(M_PI/180*(theta))
#define Sin(theta) sin(M_PI/ 180 * (theta))
typedef std::tuple<double, double, double> vector3d_t;
typedef std::vector<vector3d_t> vector3d_array_t;
class Polygon
{
        public:
        int number_of_vertices;
        std::vector<int> vertices;
        
        void drawSelf(std::vector<vector3d_t> v_list);
        void readVertices(FILE *fp);

};
void parseMesh(std::vector<Polygon> &p_list, std::vector<vector3d_t> &v_list);
