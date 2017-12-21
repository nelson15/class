// element_indices.cpp
// AUTHOR: Corey Wetterer-Nelson
// DATE: 11-Dec-2017

//Function element_indices()
// get the global indices for the element
#include "run_functions.h"

int Solver_LaplaceBeltrami::element_indices(int e)
{
  indices_elem = srf->IEN[e];
  return 0;
}
