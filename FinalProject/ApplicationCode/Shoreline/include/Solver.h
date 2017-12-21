// Solver.h
// AUTHOR: Corey Wetterer-Nelson
// DATE: 6-Dec-2017

//Class Solver
//Responsible for element formation and assembly along with system solution
//will start with Laplace-Beltrami in serial and inherit from that
//to get more complex solvers
#ifndef SOLVER_H
#define SOLVER_H

#include "run_functions.h"
using namespace std;
class Solver_LaplaceBeltrami
{
public:
  Surface * srf; //pointer to surface object to solve over
  Problem * prb; //pointer to problem data
  //PETSc data structures
  Mat Tangent;
  Vec rhs;
  Vec sol_vec;
  KSP ksp;
	PC pc;
  PetscViewer viewer;


  //gauss quadrature schemes
  int num_quad;
  vector<double> quad_pt;
  vector<double> quad_wt;

  //element level variables so we don't have to lug them around
  vector<int> indices_elem;
  vector<double> k_elem;
  vector<double> rhs_elem;

  //////////////////////////////////////////////////////////////////////////////
  //default constructor takes in a surface object
  Solver_LaplaceBeltrami(Surface *srf, Problem *prb);

  //////////////////////////////////////////////////////////////////////////////
  // call this to solve the problem wrapper for calling element_assembly() and
  // then calling KSPSetOperators() followed by KSPSolve() which populates
  //  sol_vec with the solution to the pde
  int solve();

  //////////////////////////////////////////////////////////////////////////////
  //crude storage for gauss quadrature points... want to get this to be better
  int get_gaussQuad();

  //////////////////////////////////////////////////////////////////////////////
  //subroutines responsible for managing petsc data structures and calling
  //global system solve etc.
  int petsc_setup();
  int petsc_cleanup();

  int print_Tangent(); //prints the tangent to a .m file for viewing in Matlab
  int print_rhs();
  int print_sol_vec();
  int print_solution_to_file(int res);

  //////////////////////////////////////////////////////////////////////////////
  //subroutines responsible for element formation
  // loop over elements and call element_formation() then assemble into
  //  global system
  //takes in a vector of indices and a vector representing the element
  //contribution to the global stiffness matrix
  int element_formation(int e);
  int element_indices(int e);
  //////////////////////////////////////////////////////////////////////////////
  //subroutines responsible for system assembly
  //call element_formation in a loop over elements
  int element_assembly();
  int size_element_structures(); //set element level data structure sizes
};
#endif //SOLVER_H
