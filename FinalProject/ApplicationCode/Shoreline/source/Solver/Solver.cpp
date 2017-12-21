// Solver.cpp
// AUTHOR:  Corey Wetterer-Nelson
// DATE:    8-Dec-2017
#include "run_functions.h"
////////////////////////////////////////////////////////////////////////////////
//Default constructor for the solver
Solver_LaplaceBeltrami::Solver_LaplaceBeltrami(Surface *srf, Problem *prb)
{
  this->prb = prb;
  this->srf = srf;
  petsc_setup();
  get_gaussQuad();
  size_element_structures();
}

////////////////////////////////////////////////////////////////////////////////
//helper function to resize the vectors associated with element level
//contribution to the global system
int Solver_LaplaceBeltrami::size_element_structures()
{
  int n_dof_squared = srf->n_dof_local * srf->n_dof_local;
  indices_elem.resize(srf->n_dof_local, 0);
  k_elem.resize(n_dof_squared, 0);
  rhs_elem.resize(srf->n_dof_local, 0);
  return 0; //success!
}
