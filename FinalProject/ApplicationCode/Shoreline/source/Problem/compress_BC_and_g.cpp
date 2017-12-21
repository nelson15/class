// compress_BC_and_g.cpp
// AUTHOR: Corey Wetterer-Nelson
// DATE: 13-Dec-2017

//Function compress_BC_and_g()
//get a compressed list of the bases that represent basis functions and their
//corresponding dirichlet value, useful for the PETSc data structures
#include "run_functions.h"
int Problem::compress_BC_and_g()
{
  for(i = 0; i < srf->n_dof_global; i++)
  {
    if(BC[i])
    {
      BC_rows.push_back(i);
      g_compressed.push_back(g[i]);
    }
  }
  return 0; //success!
}
