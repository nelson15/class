// extract_geometry.cpp
// AUTHOR: Corey Wetterer-Nelson
// DATE: 11-Dec-2017

//Function extract_geometry()
//get the extracted geometry for each element
#include "run_functions.h"
int Surface::extract_Geometry()
{
  //get control points in projective space
  project_ctrlPts();

  CtrlPts_extracted.resize(num_elems, vector< array <double, 4> >(n_dof_local));
  for(auto & e: CtrlPts_extracted)
  {
    for(auto & c : e)
    {
      c[0] = 0; c[1] = 0; c[2] = 0; c[3] = 0;
    }
  }
  cout << "extracted control point storage made" << endl;
//  for e = 1:n_el
//     for j = 1:d+1
//         for a = 1:(p_1+1)*(p_2+1)
//             i = IEN(a,e);
//             P_e(a,1) = Pw(j,i);
//         end
//         C_e = C_operators(:,:,e);
//         P_bw(j,:,e) = (C_e'*P_e)';
//     end
// end
  int i;
  vector<double> P_e;
  P_e.resize(n_dof_local);
  cout << "n elems = " << num_elems << endl;
  for(int e = 0; e < num_elems; e++)
  {
    for(int j = 0; j < 4; j++) //loop over dimensions in projective space
    {
      for(int a = 0; a < n_dof_local; a++)
      {
        i = IEN[e][a];
        P_e[a] = CtrlPts[i][j];
      }
      for(int a = 0; a < n_dof_local; a++)
      {
        for(int b = 0; b < n_dof_local; b++)
        {
          CtrlPts_extracted[e][a][j] += C[e][b][a] * P_e[b];
        }
      }
    }
  }

  //de project the extracted control points
  for(int e = 0; e < num_elems; e++)
  {
    for(int a = 0; a < n_dof_local; a++)
    {
      CtrlPts_extracted[e][a][0] = CtrlPts_extracted[e][a][0]
                                  / CtrlPts_extracted[e][a][3];
      CtrlPts_extracted[e][a][1] = CtrlPts_extracted[e][a][1]
                                  / CtrlPts_extracted[e][a][3];
      CtrlPts_extracted[e][a][2] = CtrlPts_extracted[e][a][2]
                                  / CtrlPts_extracted[e][a][3];
    }
  }

  //get control points out of projective space
  deproject_ctrlPts();
  return 0; //success!
}
