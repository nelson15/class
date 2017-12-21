// subdivide_surf.cpp
// AUTHOR:  Corey Wetterer-Nelson
// DATE:    10-Nov-2017

//Function subdivide_surf()
/*
  When importing from Blender, it is possible to have a set of control points
  and weights along with a polynomial degree that are not condusive to an
  open knot vector, so we can add in some control points to account for this
  and easily build an open knot vector to interface with our IGA stuff.
  this is done via linear interpolation of the knots at an index specified
*/

//INPUTS
//  uv = which coordinate direction to interpolate, u or v (1 or 2)
//  index = the index to insert the control points at
//          (index=1 -> insert after 0th control point)

#include "run_functions.h"
int Surface::subdivide_surf(int uv, int index)
{
  if(uv == 1) //add a row of control points in u direction
  {
    for(int i = index - 1; i < this->n_v; i++)
    {
      array<double,4> newCtrlPt;
      for(int j = 0; j < 4; i++)  //linearly interpolate control pts
      {
        newCtrlPt[j] = (this->CtrlPts[i][j] + this->CtrlPts[i+1][j])/2;
      }
      this->CtrlPts.insert(this->CtrlPts.begin()+index*i, newCtrlPt);
    }
  }
  else if(uv == 2) //add a row of control points in v direction
  {
    for(int i = index - 1; i < this->n_u; i++)
    {
      cout << i << endl;
      array<double,4> newCtrlPt;
      for(int j = 0; j < 4; i++)  //linearly interpolate control pts
      {
        newCtrlPt[j] = (this->CtrlPts[i][j] + this->CtrlPts[i+this->n_u][j])/2;
        //cout << newCtrlPt[j] << endl;
      }
      cout << endl;
      this->CtrlPts.insert(this->CtrlPts.begin()+this->n_u*index+i, newCtrlPt);
    }
    this->n_v++;
  }
  return 0;
}
