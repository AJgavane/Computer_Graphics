#include<iostream>
#include<stdlib.h>
#include<math.h>
#include<cstdio>
#include<vector>
#define K0 1.0
#define L0 500
#define TOLERANCE 1e-14

using namespace std;

/* In the Energy Minimization Algorithm, the domain of workspace is real numbers.
 * Hence, we have typedefed the data type "Vector of pairs" to "dblvec_t"*/
typedef std::vector<double> dblvec_t;

/*Declaration for the energy minimization function. This function is contains the algoritm
 * which takes as input the vertex set (V) and edge set (E) of a connected graph (G) and
 * outputs the new pixel locations*/
void minimizeEnergy(std::vector<std::pair<int, int> > , double **, std::vector<std::pair<int, int> > &);//, std::vector<std::pair<int, int>> &, int **&);

/*Used in calculating the minimum of two numbers*/
double min_length(double, double);

/*Given a set of distances, the following function calculates the maximum.*/
double max_dist(std::vector<double>);

/*The following function updates the the partial derivatives of E wrt x and y and also
 * updates the force (Delta_m) on each node*/
void updateAll(std::vector<std::pair<double, double> > , dblvec_t , dblvec_t ,dblvec_t &,dblvec_t &,dblvec_t &,dblvec_t &,dblvec_t &,dblvec_t &);

/*The following function updates the force (Delta_m) for a particular particle*/
void updateIndividual(std::vector<std::pair<double, double> > , dblvec_t , dblvec_t ,dblvec_t &,dblvec_t &,dblvec_t &,dblvec_t &,dblvec_t &,dblvec_t &, int );

/* Following function calculates the euclidean distance between two points*/
double distanceBetweenPoints(std::pair<double, double>, std::pair<double, double>);

/*Checks to see if any of the forces (Delta_m) exceed the tolerance and stores it's value
 * in an integer variable*/
bool maximumForce(dblvec_t &forces, int &j);
