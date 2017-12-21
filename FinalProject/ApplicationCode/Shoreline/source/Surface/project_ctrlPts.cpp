// project_ctrlPts.cpp
// AUTHOR: Corey Wetterer-Nelson
// DATE: 16-Dec-2017

#include "run_functions.h"
//Function project_ctrlPts()
//project control points to projective space (mult by weights)
int Surface::project_ctrlPts()
{
  if(!ctrlPtsprojective)
  {
      for(auto & c : CtrlPts)
    {
      c[0] = c[0] * c[3];
      c[1] = c[1] * c[3];
      c[2] = c[2] * c[3];
    }
    ctrlPtsprojective = true;
    return 0; //success!
  }
  else
  {
    return 1; // already in projective space!
  }
}

////////////////////////////////////////////////////////////////////////////////
//Function deproject_ctrlPts()
//project control points to projective space (mult by weights)
int Surface::deproject_ctrlPts()
{
  if(ctrlPtsprojective)
  {
    for(auto & c : CtrlPts)
    {
      c[0] = c[0] / c[3];
      c[1] = c[1] / c[3];
      c[2] = c[2] / c[3];
    }
    ctrlPtsprojective = false;
    return 0; //success!
  }
  else
  {
    return 1; //already in physical space!
  }
}
