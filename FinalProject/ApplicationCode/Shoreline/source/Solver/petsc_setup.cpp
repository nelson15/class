// petsc_setup.cpp
// AUTHOR:  Corey Wetterer-Nelson
// DATE:    8-Dec-2017

//Setup the petsc variables and stuff
#include "run_functions.h"

int Solver_LaplaceBeltrami::petsc_setup()
{
  //////////////////////////////////////////////////////////////////////////////
  //setup right-hand side vector
  VecCreate(PETSC_COMM_WORLD,&rhs);
	VecSetSizes(rhs,PETSC_DECIDE, srf->n_dof_global);
	VecSetFromOptions(rhs);
	VecSetUp(rhs);
  cout << "RHS vector allocated" << endl;

  //////////////////////////////////////////////////////////////////////////////
  //setup solution vector
  VecCreate(PETSC_COMM_WORLD,&sol_vec);
	VecSetSizes(sol_vec,PETSC_DECIDE, srf->n_dof_global);
	VecSetFromOptions(sol_vec);
	VecSetUp(sol_vec);
  cout << "Solution vector allocated" << endl;


  //////////////////////////////////////////////////////////////////////////////
  //setup LHS tangent matrix
  MatCreate(PETSC_COMM_WORLD, &Tangent);
	MatSetSizes(Tangent, PETSC_DECIDE, PETSC_DECIDE,
              srf->n_dof_global, srf->n_dof_global);
	MatSetFromOptions(Tangent);
	MatSeqAIJSetPreallocation(Tangent, srf->num_elems * srf->n_dof_local, NULL);
	MatSetUp(Tangent);

  cout << "LHS tangent matrix allocated" << endl;

  //////////////////////////////////////////////////////////////////////////////
  //setup krylov solver and the LU preconditioner
  KSPCreate(PETSC_COMM_WORLD, &ksp);
  KSPSetType(ksp,KSPGMRES);
  KSPGetPC(ksp,&pc);
  PCSetType(pc,PCLU);
  KSPSetTolerances(ksp,PETSC_DEFAULT,PETSC_DEFAULT,PETSC_DEFAULT,PETSC_DEFAULT);
  KSPSetFromOptions(ksp);
  cout << "KSP solver and preconditioner setup" << endl;

  return 0; //success!
}


////////////////////////////////////////////////////////////////////////////////
//clean up PETSc data structures
int Solver_LaplaceBeltrami::petsc_cleanup()
{
  int rerr;
  rerr = MatDestroy(&Tangent);
  rerr = VecDestroy(&sol_vec);
  rerr = KSPDestroy(&ksp);
  rerr = VecDestroy(&rhs);

  cout << "PETSc data structures are destroyed" << endl;
  return rerr;
}
