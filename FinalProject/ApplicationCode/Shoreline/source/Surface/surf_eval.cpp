// surf_eval.cpp
// AUTHOR:  Corey Wetterer-Nelson
// DATE:    10-Nov-2017

//Function surf_eval()
// evaluates basis functions
#include "run_functions.h"

int Surface::surf_basis(double xi1, double xi2)
{
  vector<double> temp1, temp2;
  basisFuncsAndDers(&Xi_u, p_u, xi1, 0, &temp1);
  basisFuncsAndDers(&Xi_v, p_v, xi2, 0, &temp2);

  vector<double> Bases((p_u+1)*(p_v+1), 0.0);
  for(int i = 0; i < p_u + 1; i++)
  {
    for(int j = 0; j < p_v + 1; j++)
    {
      // Bases[i+(p_u+1)*j] =
    }
  }
  return 0; //success!
}

////////////////////////////////////////////////////////////////////////////////
//perform shape function routines to generate basis R^e(x,y), and its
//physical derivatives R^e,x, R^e,y, R^e,z via computation of psuedo inverse
//Jacobian
// INPUTS:
//  e = element Number
// xi_u, xi_v, parametric coodinate on element between 0 and 1
// J = surface element scaling
// R_x = NURBS basis and derivatives in x,y,z directions
// Rxi = NURBS basis and derivatives in xi1 and xi2 directions(parametric space)
// DF =  jacobian at the point in parametric space (3x2 matrix)
// wfxn = weight function and derivatives in xi1 and xi2 directions
// x = point in physical space <x,y,z>

int Surface::shape_function(int e, double xi_u, double xi_v, double * J,
      vector<array<double, 4> > *R_x, vector<array<double, 3> > *Rxi,
      array<double,3>*wfxn, array<array<double,2>,3> *DF_plus,
      array<double,3> * x)
{
  *J = 0;
  wfxn->at(0) = 0;
  wfxn->at(1) = 0;
  wfxn->at(2) = 0;
  DF_plus->at(0)[0] = 0;DF_plus->at(0)[1] = 0;
  DF_plus->at(1)[0] = 0;DF_plus->at(1)[1] = 0;
  DF_plus->at(2)[0] = 0;DF_plus->at(2)[1] = 0;


  x->at(0) = 0; x->at(1) = 0; x->at(2) = 0;

  for(auto & r : *R_x)
  {
    r[0] = 0; r[1] = 0; r[2] = 0; r[3] = 0;
  }
  for(auto & r : *Rxi)
  {
    r[0] = 0; r[1] = 0; r[2] = 0;
  }

  int a, b; //some iterators

  array<array<double,2>,3> DF; //mapping from physical to parametric
  DF[0][0] = 0;DF[0][1] = 0;
  DF[1][0] = 0;DF[1][1] = 0;
  DF[2][0] = 0;DF[2][1] = 0;
  //initialize all the variables to zeros
  R_x->resize(n_dof_local);
  Rxi->resize(n_dof_local);

  for(auto g : DF)
  {
    g[0] = 0; g[1] = 0;
  }
  //fill(DF->begin(),DF->end(),array<double,2>(0.0));
  fill(wfxn->begin(),wfxn->end(), 0.0);
  fill(x->begin(), x->end(), 0.0);

  //compute values of Bernstein polynomials at xiu,xiv
  // B[i][0] = value of basis i
  // B[i][1] = u derivative of basis i
  // B[i][2] = v derivative of basis i
  vector<array <double,3> > B;
  BernsteinBasisAndDerivs2D( & B, this->p_u, this->p_v, xi_u, xi_v);

  //compute weighting function and its derivatives
  for(a = 0; a < n_dof_local; a++)
  {
    wfxn->at(0) += CtrlPts_extracted[e][a][3] * B[a][0]; //value
    wfxn->at(1) += CtrlPts_extracted[e][a][3] * B[a][1]; //xi_u derivative
    wfxn->at(2) += CtrlPts_extracted[e][a][3] * B[a][2]; //xi_v derivative
  }

  //compute basis functions and parametric derivatives
  for(a = 0; a < n_dof_local; a++)
  {
    for(b = 0; b < n_dof_local; b++)
    {
      //value
      Rxi->at(a)[0] += CtrlPts_extracted[e][a][3] * C[e][a][b]
                    * B[a][0] / wfxn->at(0);
      // xi_u derivative
      Rxi->at(a)[1] += CtrlPts_extracted[e][a][3] * C[e][a][b]
                    * (B[a][1]/wfxn->at(0) - wfxn->at(1)
                    * B[a][0] / (wfxn->at(0) * wfxn->at(0)));
      //xi_v derivative
      Rxi->at(a)[2] += CtrlPts_extracted[e][a][3] * C[e][a][b]
                    * (B[a][2]/wfxn->at(0) - wfxn->at(2)
                    * B[a][0] / (wfxn->at(0) * wfxn->at(0)));
    }
  }
  // cout << "Rxi" << endl;
  // for(auto & r : *Rxi)
  // {
  //   for(auto & ri :r)
  //   {
  //     cout << ri << ", ";
  //   }
  //   cout << endl;
  // }

  //compute phsyical space quantities
  for(a = 0; a < n_dof_local; a++)
  {
    //point in physical space
    x->at(0) += CtrlPts_extracted[e][a][3]
              * CtrlPts_extracted[e][a][0] * B[a][0]/wfxn->at(0); // x
    x->at(1) += CtrlPts_extracted[e][a][3]
              * CtrlPts_extracted[e][a][1] * B[a][0]/wfxn->at(0); // y
    x->at(2) += CtrlPts_extracted[e][a][3]
              * CtrlPts_extracted[e][a][2] * B[a][0]/wfxn->at(0); // z

    //components of Jacobian (3 x 2 array)
    // DF[0][0] = dx/dxiu, DF[0][1] = dx/dxiv
    // DF[1][0] = dy/dxiu, DF[1][1] = dy/dxiv
    // DF[2][0] = dz/dxiu, DF[2][1] = dz/dxiv
    DF[0][0] += CtrlPts_extracted[e][a][3]
                 * CtrlPts_extracted[e][a][0]
                 * (B[a][1]/wfxn->at(0) - wfxn->at(1)
                 * B[a][0] / (wfxn->at(0) * wfxn->at(0)));
    DF[1][0] += CtrlPts_extracted[e][a][3]
                 * CtrlPts_extracted[e][a][1]
                 * (B[a][1]/wfxn->at(0) - wfxn->at(1)
                 * B[a][0] / (wfxn->at(0) * wfxn->at(0)));
    DF[2][0] += CtrlPts_extracted[e][a][3]
                 * CtrlPts_extracted[e][a][2]
                 * (B[a][1]/wfxn->at(0) - wfxn->at(1)
                 * B[a][0] / (wfxn->at(0) * wfxn->at(0)));

    DF[0][1] += CtrlPts_extracted[e][a][3]
                 * CtrlPts_extracted[e][a][0]
                 * (B[a][2]/wfxn->at(0) - wfxn->at(2)
                 * B[a][0] / (wfxn->at(0) * wfxn->at(0)));
    DF[1][1] += CtrlPts_extracted[e][a][3]
                 * CtrlPts_extracted[e][a][1]
                 * (B[a][2]/wfxn->at(0) - wfxn->at(2)
                 * B[a][0] / (wfxn->at(0) * wfxn->at(0)));
    DF[2][1] += CtrlPts_extracted[e][a][3]
                 * CtrlPts_extracted[e][a][2]
                 * (B[a][2]/wfxn->at(0) - wfxn->at(2)
                 * B[a][0] / (wfxn->at(0) * wfxn->at(0)));
  }
  DF[0][0] = 1;DF[0][1] = 0;
  DF[1][0] = 0;DF[1][1] = 1;
  DF[2][0] = 0;DF[2][1] = 0;
  //
  // for(auto &di : DF)
  // {
  //   for(auto &dj : di)
  //   {
  //     cout << dj << ", ";
  //   }
  //   cout << endl;
  // }

  //compute Monroe-Penrose pseudoinverse of the Jacobian
  // DF+ = (DF^T DF)^-1 DF^T = (DFp_tmp)^-1 DF^T
  // dx/dxi = (DF+)^T
  array<array<double,2>,2> DFp_tmp;
  double DFp_tmp_j;
  array<array<double,2>,2> DFp_tmp_inv;
  //compute the matrix product inside the inverse within the definition above
  DFp_tmp[0][0] = DF[0][0]*DF[0][0] + DF[1][0]*DF[1][0] + DF[2][0]*DF[2][0];
  DFp_tmp[1][0] = DF[0][1]*DF[0][0] + DF[1][1]*DF[1][0] + DF[2][1]*DF[2][0];
  DFp_tmp[0][1] = DF[0][0]*DF[0][1] + DF[1][0]*DF[1][1] + DF[2][0]*DF[2][1];
  DFp_tmp[1][1] = DF[0][1]*DF[0][1] + DF[1][1]*DF[1][1] + DF[2][1]*DF[2][1];

  //compute one over the matrix determinant for taking the inverse of that 2x2
  DFp_tmp_j = 1 / (DFp_tmp[0][0]*DFp_tmp[1][1] - DFp_tmp[1][0]*DFp_tmp[0][1]);

  //compute the inverse of the 2x2 inside the definition above
  DFp_tmp_inv[0][0] =   DFp_tmp_j * DFp_tmp[1][1];
  DFp_tmp_inv[1][1] =   DFp_tmp_j * DFp_tmp[0][0];
  DFp_tmp_inv[1][0] = - DFp_tmp_j * DFp_tmp[0][1];
  DFp_tmp_inv[0][1] = - DFp_tmp_j * DFp_tmp[1][0];

  //compute matrix product DFp_tmp_inv DF^T
  DF_plus->at(0)[0] = DFp_tmp_inv[0][0]*DF[0][0] + DFp_tmp_inv[0][1]*DF[0][1];
  DF_plus->at(0)[1] = DFp_tmp_inv[1][0]*DF[0][0] + DFp_tmp_inv[1][1]*DF[0][1];
  DF_plus->at(1)[0] = DFp_tmp_inv[0][0]*DF[1][0] + DFp_tmp_inv[0][1]*DF[1][1];
  DF_plus->at(1)[1] = DFp_tmp_inv[1][0]*DF[1][0] + DFp_tmp_inv[1][1]*DF[1][1];
  DF_plus->at(2)[0] = DFp_tmp_inv[0][0]*DF[2][0] + DFp_tmp_inv[0][1]*DF[2][1];
  DF_plus->at(2)[1] = DFp_tmp_inv[1][0]*DF[2][0] + DFp_tmp_inv[1][1]*DF[2][1];

  //surface element
  *J = sqrt(pow(DF[1][0]*DF[2][1] + DF[2][0]*DF[1][1],2)
          + pow(DF[2][0]*DF[0][1] + DF[0][0]*DF[2][1],2)
          + pow(DF[0][0]*DF[1][1] + DF[1][0]*DF[0][1],2));

  //compute the gradients of the bases in physical space
  for(a = 0; a< n_dof_local; a++)
  {
    R_x->at(a)[0] = Rxi->at(a)[0];
    //dR/dx
    R_x->at(a)[1] = (Rxi->at(a)[1] * DF_plus->at(0)[0]
                  +  Rxi->at(a)[2] * DF_plus->at(0)[1]);
    //dR/dy
    R_x->at(a)[2] = (Rxi->at(a)[1] * DF_plus->at(1)[0]
                  +  Rxi->at(a)[2] * DF_plus->at(1)[1]);
    //dR/dz
    R_x->at(a)[3] = (Rxi->at(a)[1] * DF_plus->at(2)[0]
                  +  Rxi->at(a)[2] * DF_plus->at(2)[1]);
  }
  return 0; //success!
}
