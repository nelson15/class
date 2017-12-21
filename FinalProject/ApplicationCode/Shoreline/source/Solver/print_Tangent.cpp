// print_Tangent.cpp
// AUTHOR: Corey Wetterer-Nelson
// DATE: 13-Dec-2017


#include "run_functions.h"
//Function print_Tangent()
//print the tangent matrix to a .m file for viewing in matlab
int Solver_LaplaceBeltrami::print_Tangent()
{
  PetscViewerASCIIOpen(PETSC_COMM_WORLD,"output/Tangent.m", &viewer);

  PetscViewerPushFormat(viewer,PETSC_VIEWER_ASCII_MATLAB);
  MatView(Tangent,viewer);
  return 0; // success!
}

//Function print_rhs()
//print the rhs vector to a .m file for viewing in matlab
int Solver_LaplaceBeltrami::print_rhs()
{
  PetscViewerASCIIOpen(PETSC_COMM_WORLD,"output/rhs.m", &viewer);

  PetscViewerPushFormat(viewer,PETSC_VIEWER_ASCII_MATLAB);
  VecView(rhs,viewer);
  return 0; //success!
}

//Function print_rhs()
//print the rhs vector to a .m file for viewing in matlab
int Solver_LaplaceBeltrami::print_sol_vec()
{
  PetscViewerASCIIOpen(PETSC_COMM_WORLD,"output/solVec.m", &viewer);

  PetscViewerPushFormat(viewer,PETSC_VIEWER_ASCII_MATLAB);
  VecView(sol_vec,viewer);
  return 0; //success!
}
