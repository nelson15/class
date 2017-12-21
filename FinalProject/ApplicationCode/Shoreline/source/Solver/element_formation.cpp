// element_formation.cpp
// AUTHOR: Corey Wetterer-Nelson
// DATE: 11-Dec-2017

//Function element_assembly()
//Form the element level tangent matrix and RHS vector for the Laplace Beltrami
//equation
#include "run_functions.h"
int Solver_LaplaceBeltrami::element_formation(int e)
{
  double J;
  vector<array<double, 4> > R_x;
  vector<array<double, 3> > Rxi;
  array<array<double,2>,3> DF;
  array<double,3> x;
  array<double,3> wfxn;
  int I, qu, qv, a, b; //some iterators
  double quadpt_u, quadpt_v, qwt_Tot;

  for(qu = 0; qu < num_quad; qu++)
  {
    //get quad point in u direction
    quadpt_u = quad_pt[qu];
    for(qv = 0; qv < num_quad; qv++)
    {
      //get quad point in v direction
      quadpt_v = quad_pt[qv];
      qwt_Tot =  quad_wt[qu] * quad_wt[qv]; //tested normal

      //get info about the surface at the quad point
      srf->shape_function(e,quadpt_u, quadpt_v, &J, &R_x, &Rxi, &wfxn, &DF, &x);

      // if(qu == 0 && qv == 0 && e == srf->num_elems_u + 2)
      // {
      //   for(int a = 0; a < srf->n_dof_local; a++)
      //   {cout << "dR/dx = " << R_x[a][1] << endl;
      //   cout << "dR/dy = " << R_x[a][2]<< endl;
      //   cout << "dR/dz = " << R_x[a][3]<< endl;}
      //
      // }
      //cout << "J = " << J << endl;
      //loop over shape functions
      for(a = 0; a < srf->n_dof_local; a++)
      {
        for(b = 0; b < srf->n_dof_local; b++)
        {
          I = a* srf->n_dof_local + b;
          //integrate grad R_a dot grad R_b
          // k_elem[I] -= (R_x[a][1] * R_x[b][1]
          //             + R_x[a][2] * R_x[b][2]
          //             + R_x[a][3] * R_x[b][3]) * qwt_Tot*J;
          k_elem[I] -= (Rxi[a][1] * Rxi[b][1]
                      + Rxi[a][2] * Rxi[b][2]) * qwt_Tot*J;
        }
        //update forcing vector
        rhs_elem[a] += Rxi[a][0] * prb->forcing[srf->IEN[e][a]] * qwt_Tot*J;

        //cout << "rhs_elem[a] = " << rhs_elem[a] << endl;
      }
    }
  }

  //Apply Neumann boundary conditions...

  return 0;//success!
}
