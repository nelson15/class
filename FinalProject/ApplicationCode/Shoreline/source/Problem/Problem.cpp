// Problem.cpp
// AUTHOR:  Corey Wetterer-Nelson
// DATE:    11-Dec-2017
#include "run_functions.h"
////////////////////////////////////////////////////////////////////////////////
//Default constructor for the problem class
Problem::Problem(Surface *srf, string problemType)
{
  this->srf = srf;

  populate_BC_and_g(problemType);
  populate_forcing(problemType);
  compress_BC_and_g();
}
