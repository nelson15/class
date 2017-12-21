// refine_surf.cpp
// AUTHOR: Corey Wetterer-Nelson
// DATE: 5-Dec-2017

////////////////////////////////////////////////////////////////////////////////
// pad the knot vector at the front and back, add repeated control points
// at front and back to compensate
#include "run_functions.h"

// #define DEBUG_RF

int Surface::pad_knots()
{
  if(use_endpoint_u){ pad_knot_u(); }
  if(use_endpoint_v){ pad_knot_v(); }
  n_dof_global = n_u * n_v;
  return 0; //success!
}

int Surface::pad_knot_u()
{
  //add knots the front and back of knot vector
  Xi_u.insert(Xi_u.begin(),0); Xi_u.push_back(Xi_u.back());
  int I, i ,j;
  vector< vector<array <double,4> > > CtrlPts_rect(n_u,
                                              vector<array<double,4> >(n_v));
  for( i = 0; i < n_u; i++)
  {
    for(j = 0; j < n_v; j++)
    {
      I = i* n_v + j;
      CtrlPts_rect[i][j] = CtrlPts[I];
    }
  }

  CtrlPts_rect.insert(CtrlPts_rect.begin(),CtrlPts_rect.front());
  CtrlPts_rect.push_back(CtrlPts_rect.back());

  n_u  = Xi_u.size() - p_u - 1; //added 2 control points and 2 knots ->adds 2 dofs in u direction

  CtrlPts.resize(CtrlPts.size()+2*n_v);
  //rearrange the control points back into their list form
  for(i = 0; i < n_u; i++)
  {
    for(j = 0; j < n_v; j++)
    {
      I = i* n_v + j;

      CtrlPts[I] = CtrlPts_rect[i][j];
    }
  }

  #ifdef DEBUG_RF
  for(auto & y: CtrlPts)
  {
    cout << "(" << y[0] << ", " << y[1] << ", " << y[2] << ", "
    << y[3] << "), ";
    cout << endl;
  }
  cout << endl;
  #endif

  return 0; //success!
}

////////////////////////////////////////////////////////////////////////////////
int Surface::pad_knot_v()
{
  Xi_v.insert(Xi_v.begin(),0); Xi_v.push_back(Xi_v.back());
  int I, i ,j;
  vector< vector<array <double,4> > > CtrlPts_rect(n_u,
                                              vector<array<double,4> >(n_v));
  for( i = 0; i < n_u; i++)
  {
    for(j = 0; j < n_v; j++)
    {
      I = i* n_v + j;
      CtrlPts_rect[i][j] = CtrlPts[I];
    }
  }
  for(i = 0; i < n_u ; i++)
  {
    CtrlPts_rect[i].insert(CtrlPts_rect[i].begin(),CtrlPts_rect[i].front());
    CtrlPts_rect[i].push_back(CtrlPts_rect[i].back());
  }
  n_v = Xi_v.size() - p_v - 1;

  //return control points to their list formation
  CtrlPts.resize(CtrlPts.size()+2*n_u);
  for(i = 0; i < n_u; i++)
  {
    for(j = 0; j < n_v; j++)
    {
      I = i* n_v + j;
      CtrlPts[I] = CtrlPts_rect[i][j];
    }
  }
  return 0; //success!
}

////////////////////////////////////////////////////////////////////////////////
//add a knot to the knot vector in the uv (1 or 2) direction
// will add control points too.
// int Surface::add_knot(int uv, double Xi_add)
// {
//   switch(uv) //pick the direction
//   {
//     case 2: //v direction
//       //Xi_expanded = Xi_v;
//       p = this->p_v;
//       n = this->n_v;
//       use_cyclic = this->use_cyclic_v;
//       break;
//
//     default:
//       //u direction
//       //Xi_expanded = Xi_u;
//       p = this->p_u;
//       n = this->n_u;
//       use_cyclic = this->use_cyclic_u;
//   }
//
//   //get control points in projective space
//   vector< array <double,4> > CtrlPts_Proj = CtrlPts;
//   for(auto & c : CtrlPts_Proj)
//   {
//     c[0] = (double)c[0]*c[3];
//     c[1] = (double)c[1]*c[3];
//     c[2] = (double)c[2]*c[3];
//   }
//   //adding 1 knot adds p control points (see IGA notes), removing (p-1)
//   vector<array <double,4> > CtrlPts_add(p);
//
//   //get position of added knot
//   vector<double> Xi_new = Xi;
//   Xi_new.push_back(Xi_add);
//   sort(Xi_new.begin(), Xi_new.end());
//   vector<double>::iterator it = find(Xi_new.begin(), Xi_new.end(), Xi_add);
//   int i = distance(Xi_new.begin(), it);
//
//   //get the region of influence for the new knot
//   int k = i-p;
//   int count  = 0;
//   //for(int j = k;)
//
// i = binarySearch(add_Xi(newKnot),Xi);
//      k = i - p;
//      count = 1; %for each knot added, we make p new control points, so this
//                  //counts thru p entries on Q_add
//      for j = (k+1):i
//          alpha = (add_Xi(newKnot) - Xi(j))/(Xi(j+p) - Xi(j));
//          Q_add(count,:) = (1-alpha)*P_proj(j-1,:) + alpha * P_proj(j,:);
//          count = count+1;
//      end
//
//      if length(add_Xi) == 1
//          Q_proj = [P_proj(1:k,:);Q_add;P_proj(i:end,:)];
//      else
//          if newKnot == 1 %start Q with first elements of P, then append
                                          //added control points
//              Q_proj = [P_proj(1:k,:);Q_add];
//          elseif newKnot == length(add_Xi) %append the last elements of P
//              Q_proj = [Q_proj;P_proj(i_last:k,:);Q_add;P_proj(i:end,:)];
//          else %add in retained control points from P before new Q_add
//              Q_proj = [Q_proj;P_proj(i_last:k,:);Q_add];
//          end
//
//      end
// }
