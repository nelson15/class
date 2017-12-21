// populate_BC_and_g.cpp
// AUTHOR: Corey Wetterer-Nelson
// DATE: 11-Dec-2017

//Function populate_BC_and_g()
//populate the BC array and the g vector to fully describe the Dirichlet
//boundary conditions of the problem
#include "run_functions.h"
int Problem::populate_BC_and_g(string problemType)
{
  BC.resize(srf->n_dof_global, 0);
  g.resize(srf->n_dof_global,0.0);

  if(problemType == "mmsP0")
  {
    cout << "Method of Manufactured Solutions, Problem 0 Chosen," <<
              " Applying BC's..." << endl;
    mmsP0_bc_and_g();
    return 0; //success!
  }
  else if(problemType == "mmsP1")
  {
    cout << "Method of Manufactured Solutions, Problem 1 Chosen," <<
              " Applying BC's..." << endl;
    mmsP1_bc_and_g();
    return 0; //success!
  }
  else
  {
    cout << "Problem with indicator " << problemType
          << endl << "Exiting." << endl;
    return 1; //failure
  }
}
