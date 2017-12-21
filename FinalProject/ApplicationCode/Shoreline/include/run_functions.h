#ifndef RUNFUNCTIONS_H
#define RUNFUNCTIONS_H

#include "libraries.h"
///////////////////////////// Function Prototypes //////////////////////////////
int basisFuncsAndDers( vector<double>* knotVec, const int cDegree,
                const double u, const int numDers, vector<double> * ders);
int BernsteinBasisAndDerivs2D(vector < array <double, 3> > * B,
                              int p_u, int p_v, double xi_u, double xi_v);
int findSpan(const std::vector<double>& knotVec, const int cDegree,
                const double value);
double bern(int i, int p, double x); //bernstien basis function evaluation
void getGaussQuad(vector<double>* quad_pt, vector<double>* quad_wt,
                int& num_quad, int p);
int knotVecCreate(int num_elem_1D, int p, double ki, double kf, double h,
                string type, vector<double>*knot_vec);
int IEN_1D(int i, int j);
int set_Identity(vector<vector<double> > * A, int m);
#endif //RUNFUNCTIONS_H
