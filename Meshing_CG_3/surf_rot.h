#include<iostream>
#include<string.h>
#include<stdlib.h>
#include<GL/glut.h>
#include<math.h>
#include<cstdio>
#include<vector>
#include<tuple>
#include<iostream>
#include<stdio.h>
#include<tuple>
#define ROT_POINTS 36
#define SAMPLE_SIZE 10
#define first(x) std::get<0>(x)
#define second(x) std::get<1>(x)
#define third(x) std::get<2>(x)
#define Sin(x)  sin(x*M_PI/180.0)
#define Cos(x) cos(x*M_PI/180.0)

typedef std::tuple<double, double, double> vector3d_t;
typedef std::vector<vector3d_t> vector3d_array_t;

/*Following function takes in the 2-d pixel as argument and the axis around which to rorate, then stores the resulting surface in a .off file*/
void surfaceRotation(std::vector<std::pair<int, int>> pixel_2d, char axis);
/*Following function is a recursive implementation for the linear interpolation of n control points*/
vector3d_t Lerp3d(vector3d_array_t a, double t);
