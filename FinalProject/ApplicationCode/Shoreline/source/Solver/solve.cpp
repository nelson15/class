// solve.cpp
// AUTHOR: Corey Wetterer-Nelson
// DATE: 13-Dec-2017

//Function solve()
// call assembly operation over all elements, assemble global system and solve
#include "run_functions.h"
int Solver_LaplaceBeltrami::solve()
{
  cout << endl << endl << "============================================" <<endl;
  cout << "Solver Initialized, Forming Global System..." << endl;
  element_assembly();
  cout << "Global System Formed." << endl;
  KSPSetOperators(ksp,Tangent,Tangent);
  KSPSolve(ksp,rhs,sol_vec);
  cout << "Global System Solved" << endl << endl;
  return 0; //success!
}
