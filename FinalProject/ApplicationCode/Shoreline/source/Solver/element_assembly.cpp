// element_assembly.cpp
// AUTHOR: Corey Wetterer-Nelson
// DATE: 11-Dec-2017

//Function element_assembly()
//form the global system by calling element_formation() in a loop over elements
//assemble the values into the matrix and RHS vector
#include "run_functions.h"
//#define DEBUG_ASM
int Solver_LaplaceBeltrami::element_assembly()
{
  int e;
  for(e = 0; e < srf->num_elems; e++)
  {
    //fill the element level arrays with zeros
    fill( indices_elem.begin(), indices_elem.end(),0);
    fill(  k_elem.begin(), k_elem.end(), 0.0);
    fill(rhs_elem.begin(), rhs_elem.end(), 0.0);

    element_indices(e);
    //form the element level stiffness matrix and rhs vector
    element_formation(e);

    #ifdef DEBUG_ASM
    cout << "element " << e << " formed. " << endl;
    #endif

    //tidy up the forcing vector
    int a, b, i, j, I;
    for(a = 0; a < srf->n_dof_local; a++)
    {
      i = srf->IEN[e][a];
      if(!(prb->BC[i]))
      {
        for(b = 0; b < srf->n_dof_local; b++)
        {
          j = srf->IEN[e][a];
          if(prb->BC[j])
          {
            I = a * srf->n_dof_local + b;
            rhs_elem[a] -= k_elem[I] * prb->g[j];
          }
        }
      }
    }
    #ifdef DEBUG_ASM
    for(auto & k : k_elem)
    {
      cout << k << endl;
    }
    cout << endl;
    #endif

    //assemble element level LHS matrix into global matrix
    MatSetValues(Tangent, srf->n_dof_local, &indices_elem[0],
                  srf->n_dof_local, &indices_elem[0], &k_elem[0],ADD_VALUES);

    //assemble element level RHS vector into global vector
    VecSetValues(rhs, srf->n_dof_local, &indices_elem[0],
                  &rhs_elem[0], ADD_VALUES);
  }


  VecSetValues(rhs, prb->BC_rows.size(), &(prb->BC_rows[0]),
                &(prb->g_compressed[0]),INSERT_VALUES);

  //assemble the matrix system into the PETSc structure
  MatAssemblyBegin(Tangent,MAT_FINAL_ASSEMBLY);
	MatAssemblyEnd(Tangent,MAT_FINAL_ASSEMBLY);
  MatZeroRowsColumns(Tangent, prb->BC_rows.size(), &(prb->BC_rows[0]), 1.0,
                  PETSC_NULL, PETSC_NULL);

  //assemble the rhs vector system into the PETSc structure
  VecAssemblyBegin(rhs);
	VecAssemblyEnd(rhs);
  return 0;
}
