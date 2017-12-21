// get_gaussQuad.cpp
// AUTHOR: Corey Wetterer-Nelson
// DATE: 13-Dec-2017

//Function get_gaussQuad()
//get gauss quadrature points and weights
#include "run_functions.h"
int Solver_LaplaceBeltrami::get_gaussQuad()
{
  quad_pt.reserve(0);
  quad_wt.reserve(0);
  int p = max(srf->p_u, srf->p_v); //get max polynomial order in srf

  if (p < 4)
  { //overkill for p < 3
    quad_pt.push_back(0.5*(-0.861136311594053) + 0.5);
    quad_pt.push_back(0.5*(-0.339981043584856) + 0.5);
    quad_pt.push_back(0.5*(0.339981043584856) + 0.5);
    quad_pt.push_back(0.5*(0.861136311594053) + 0.5);

    quad_wt.push_back(0.347854845137454);
    quad_wt.push_back(0.652145154862546);
    quad_wt.push_back(0.652145154862546);
    quad_wt.push_back(0.347854845137454);

    num_quad = 4;
  }
  else if(p == 4)
  {
    quad_pt.push_back(0.5*(0.000000000000000) + 0.5);
    quad_pt.push_back(0.5*(0.538469310105683) + 0.5);
    quad_pt.push_back(0.5*(0.906179845938664) + 0.5);
    quad_pt.push_back(0.5*(-0.538469310105683) + 0.5);
    quad_pt.push_back(0.5*(-0.906179845938664) + 0.5);

    quad_wt.push_back(0.568888888888889);
    quad_wt.push_back(0.478628670499366);
    quad_wt.push_back(0.236926885056189);
    quad_wt.push_back(0.478628670499366);
    quad_wt.push_back(0.236926885056189);

    num_quad = 5;
  }
  else
  {
    quad_pt.push_back(0.5*(-0.932469514203152) + 0.5);
    quad_pt.push_back(0.5*(-0.661209386466265) + 0.5);
    quad_pt.push_back(0.5*(-0.238619186083197) + 0.5);
    quad_pt.push_back(0.5*(0.932469514203152) + 0.5);
    quad_pt.push_back(0.5*(0.661209386466265) + 0.5);
    quad_pt.push_back(0.5*(0.238619186083197) + 0.5);

    quad_wt.push_back(0.171324492379170);
    quad_wt.push_back(0.360761573048139);
    quad_wt.push_back(0.467913934572691);
    quad_wt.push_back(0.171324492379170);
    quad_wt.push_back(0.360761573048139);
    quad_wt.push_back(0.467913934572691);

    num_quad = 6;
  }
  return 0; //success!
}
