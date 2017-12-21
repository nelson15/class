// Problem.h
// AUTHOR:  Corey Wetterer-Nelson
// Date:    6-Dec-2017

//Class Problem
//Stores info about the problem to be solved
#ifndef PROBLEM_H
#define PROBLEM_H

#include "run_functions.h"
using namespace std;

class Problem
{
public:
  Surface * srf;//pointer to surface object to solve over

  // some iterators
  int i, j, a, b, I;

  vector<double> g; //dirichlet conditions on each basis function
  vector<bool> BC;  //label which bases connect to boundary values
  vector<double> forcing;//forcing term computed throughout domain

  //sparse version of g and BC. stores same info as BC and g, but without
  //info about interior bases. used to zero out rows corresponding to
  //Dirichlet bc's in the PETSc data structure
  vector<int> BC_rows;
  vector<double>g_compressed;

  //////////////////////////////////////////////////////////////////////////////
  //default constructor takes in a surface object and string referencing
  //the type of problem to solve
  Problem(Surface *srf, string problemType);

  //////////////////////////////////////////////////////////////////////////////
  //populate the data structures to be used by the solver wrt BC's and forcing
  //calls a different problem definition depending on problemType
  int populate_BC_and_g(string problemType);
  int populate_forcing(string problemType);
  int compress_BC_and_g();
  //////////////////////////////////////////////////////////////////////////////
  //problem definitions
  //mmsP0 - manufactured solution constant 1 on left side, 0 on other sides
  //        no forcing
  int mmsP0_bc_and_g();
  int mmsP0_forcing();

  int mmsP1_bc_and_g();
  int mmsP1_forcing();
};

#endif //PROBLEM_H
