//extraction functions
// AUTHOR:  Corey Wetterer-Nelson
// DATE:    29-Nov-2017
#include "run_functions.h"
//#define DEBUG_EX
////////////////////////////////////////////////////////////////////////////////
//build the extraction operator for the surface
int Surface::extraction_2D()
{
  extraction_1D(1);
  // cout << "Extraction operator generated in u direction." <<endl;
  // print_Extraction_1D(1);
  extraction_1D(2);
  // cout << "Extraction operator generated in v direction." <<endl;
  // print_Extraction_1D(2);

  C.resize(num_elems, vector <vector <double> >(n_dof_local,
                                                  vector<double>(n_dof_local)));

  #ifdef DEBUG_EX
  cout << "Size of C: " << C.size() << ", " << C.at(0).size()
       << ", " << C.at(0)[0].size() << endl;

  cout << "Number of Elements: " << num_elems_u * num_elems_v << endl;
  cout << "Size of side i: " << (p_u+1)*(p_v+1) << endl;
  cout << "Size of side j: " << (p_u+1)*(p_v+1) << endl;
  #endif
  // for e1 = 1:nb1
  //       for e2 = 1:nb2
  //           e = (e1-1)*nb2 + e2;
  //           C(:,:,e) = kron(C1(:,:,e1),C2(:,:,e2));
  //       end
  //   end
  //initialize some iterators
  int e, ev, eu, iu, iv, ju, jv, I, J;
  for(eu = 0; eu < num_elems_u; eu++)
  {
    for(ev = 0; ev < num_elems_v; ev++)
    {
      e = eu * num_elems_v + ev; //get the element number
      #ifdef DEBUG_EX
      cout << "Element #: " << e << endl;
      #endif
      //need to perform a kronecker product by looping over 2 2D arrays
      for(iu = 0; iu < p_u+1; iu++)
      {
        for(ju = 0; ju < p_u+1; ju++)
        {
          for(iv = 0; iv < p_v+1; iv++)
          {
            for(jv = 0; jv < p_v+1; jv++)
            {
              I = iu*(p_v+1) + iv;
              J = ju*(p_v+1) + jv;

              #ifdef DEBUG_EX
              cout << "I: " << I << " J: " << J << endl;
              #endif

              C[e][I][J] = C_u[eu][iu][ju] * C_v[ev][iv][jv];
            }
          }
        }
      }
    }
  }
  return 0; //success!
}

////////////////////////////////////////////////////////////////////////////////
//print the 2D extraction operator
int Surface::print_Extraction()
{
  cout << "Surface " << id << " Extraction Operators: " << endl;
  for(auto & e : C)
  {
    for(auto & i : e)
    {
      for(auto & j : i)
      {
        cout << j << " ";
      }
      cout << endl;
    }
    cout << endl;
  }
  return 0;
}

////////////////////////////////////////////////////////////////////////////////
//print the 1D extraction operator
int Surface::print_Extraction_1D(int uv)
{
  vector< vector< vector <double> > > *C_op;
  string dir;
  switch(uv)
  {
    case 2:
    C_op = &this->C_v;
    dir = "v";
    break;
    default:
    C_op = &this->C_u;
    dir = "u";
  }
  cout << "Surface " << id << " Extraction Operators in " << dir
        << " direction:" << endl;
  for(auto & e : *C_op)
  {
    for(auto & i : e)
    {
      for(auto & j : i)
      {
        cout << j << "\t";
      }
      cout << endl;
    }
    cout << endl;
  }
  return 0;
}
////////////////////////////////////////////////////////////////////////////////
//get the element level contrl points for the surface via Bezier extraction
// AUTHOR: Corey Wetterer-Nelson
// DATE: 5-Dec-2017
// int Surface::extract_Geometry()
// {
//   //get control points in projective space
//   project_ctrlPts();
//
//   //allocate the extracted control points arrays num_elems x n_dof_local x 4
//   CtrlPts_extracted.resize(num_elems, vector< array <double, 4> >(n_dof_local));
//
//   int e, a, b, d; //some iterators
//   array <double,4> ctrlPt_tmp; //temp place to store 1 control point
//   vector< array <double,4> > elemCtrlPt_tmp (n_dof_local);
//   for(e = 0; e < num_elems; e++)
//   {
//     for(a = 0; a < n_dof_local; a++)
//     {
//       //pick out the controlling ctrlpts over each element
//       CtrlPts_extracted[e][a] = CtrlPts[IEN[e][a]];
//     }
//
//     //apply extraction operator
//     for(a = 0; a < n_dof_local; a++) //loop over extracted contrl points
//     {
//       ctrlPt_tmp.fill(0);
//       for(b = 0; b < n_dof_local; b++)
//       {
//         for(d = 0; d < 4; d++ )
//         {
//           ctrlPt_tmp[d] += C[e][a][b] * CtrlPts_extracted[e][a][d];
//         }
//       }
//       elemCtrlPt_tmp[a] = ctrlPt_tmp;
//     }
//     //element e is done, cast elemCtrlPt_tmp[][] to CtrlPts_extracted[e][][]
//     for(a = 0; a < n_dof_local; a++)
//     {
//       CtrlPts_extracted[e][a] = elemCtrlPt_tmp[a];
//       CtrlPts_extracted[e][a][0] = CtrlPts_extracted[e][a][0]
//                                   /CtrlPts_extracted[e][a][3];
//       CtrlPts_extracted[e][a][1] = CtrlPts_extracted[e][a][1]
//                                   /CtrlPts_extracted[e][a][3];
//       CtrlPts_extracted[e][a][2] = CtrlPts_extracted[e][a][2]
//                                   /CtrlPts_extracted[e][a][3];
//     }
//   }
//   deproject_ctrlPts();
//   return 0; //success!
// }

int Surface::print_extracted_geometry()
{
  ofstream out;

  out.open("./output/CtrlPtsExtracted.m");
  for(int e = 0; e < num_elems; e++)
  {
    out << "e" << e << "=[" << endl;
    for(int a = 0; a < n_dof_local; a++)
    {
      out << CtrlPts_extracted[e][a][0] << ", "
          << CtrlPts_extracted[e][a][1] << ", "
          << CtrlPts_extracted[e][a][2] << ", "
          << CtrlPts_extracted[e][a][3] << endl;
    }
    out << "];" << endl << endl;
  }

  out << "figure;" << endl << "hold on;" << endl;
  for(int e = 0; e < num_elems; e++)
  {
    out << "scatter3(e" << e << "(:,1),e" << e << "(:,2),e" << e
          << "(:,3),200,'.');" << endl;
  }
  out.close();
  return 0;
}
