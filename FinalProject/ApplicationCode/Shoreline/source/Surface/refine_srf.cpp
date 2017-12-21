// refine_srf.cpp
// AUTHOR: Corey Wetterer-Nelson
// DATE: 15-Dec-2017

//Function refine_srf()
//cut all elements in half along both parametric coordinates
#include "run_functions.h"

int Surface::refine()
{
  //refine u direction
  vector<double> knots_to_add = cut_knots_half(1);
  add_knots_u(knots_to_add);
  //refine v direction
  knots_to_add = cut_knots_half(2);
  add_knots_v(knots_to_add);
  return 0;
}
////////////////////////////////////////////////////////////////////////////////
int Surface::add_knots_u(vector<double> knots_to_add)
{
  project_ctrlPts();//perform refinement in projective space

  //get new knot vector
  vector<double> new_Xi_u = Xi_u;
  for(auto & nk: knots_to_add)
  {
    new_Xi_u.push_back(nk);
  }
  sort(new_Xi_u.begin(), new_Xi_u.end());

  //make the control points rectangular to allow for easy looping
  vector< vector<array <double,4> > > CtrlPts_rect(n_u,
                                              vector<array<double,4> >(n_v));
  int I;//an iterator
  //cast control points into a rectangular array
  for(int i = 0; i < n_u; i++)
  {
    for(int j = 0; j < n_v; j++)
    {
      I = i* n_v + j;
      CtrlPts_rect[i][j] = CtrlPts[I];
    }
  }

  vector<double> a( p_u, 0.0 );
  vector< vector<array <double,4> > > Q(p_u, vector<array<double,4> >(n_v));
  vector<array<double,4> > placeHolder;
  placeHolder.resize(n_v);
  for(int i = 0; i < new_Xi_u.size(); i++)
  {
    if(new_Xi_u[i] != Xi_u[i])
    {
      for(int j = 0; j < p_u; j ++)
      {
        int kj = i - (p_u-j);
        //compute alphas making up the convex combination of ctrlpts
        a[j] = (new_Xi_u[i] - Xi_u[kj]) / (Xi_u[kj+p_u] - Xi_u[kj]);
        for(int k = 0; k < n_v; k++)
        {
          Q[j][k][0] = (1- a[j])*CtrlPts_rect[kj-1][k][0]
                          + a[j] * CtrlPts_rect[kj][k][0];
          Q[j][k][1] = (1- a[j])*CtrlPts_rect[kj-1][k][1]
                          + a[j] * CtrlPts_rect[kj][k][1];
          Q[j][k][2] = (1- a[j])*CtrlPts_rect[kj-1][k][2]
                          + a[j] * CtrlPts_rect[kj][k][2];
          Q[j][k][3] = (1- a[j])*CtrlPts_rect[kj-1][k][3]
                          + a[j] * CtrlPts_rect[kj][k][3];
        }
      }
      //insert a control point, will be replacing p-1 ctrlpts with p ctrlpts
      CtrlPts_rect.insert(CtrlPts_rect.begin()+i-p_u+1, placeHolder);
      for(int j = 0; j < p_u; j++)
      {
        CtrlPts_rect[i-p_u + j] = Q[j];
      }
      //insert the new knot into the knot vector
      Xi_u.insert(Xi_u.begin()+i, new_Xi_u[i]);
      n_u = Xi_u.size() - p_u - 1; //update n_u
    }
  }
  //recast ctrlpts to a 1D vector
  vector<array<double,4> > CtrlPtsTmp;
  for(int i = 0; i < n_u; i++)
  {
    for(int j = 0; j < n_v; j++)
    {
      I = i* n_v + j;
      CtrlPtsTmp.push_back(CtrlPts_rect[i][j]);
    }
  }
  CtrlPts = CtrlPtsTmp;
  deproject_ctrlPts(); //get contrl points out of projective space
  getNumberOfElementsAndDOFs();
  return 0;//success!
}

////////////////////////////////////////////////////////////////////////////////
int Surface::add_knots_v(vector<double> knots_to_add)
{
  project_ctrlPts();//perform refinement in projective space

  //get new knot vector
  vector<double> new_Xi_v = Xi_v;
  for(auto & nk: knots_to_add)
  {
    new_Xi_v.push_back(nk);
  }
  sort(new_Xi_v.begin(), new_Xi_v.end());

  //make the control points rectangular to allow for easy looping
  vector< vector<array <double,4> > > CtrlPts_rect(n_u,
                                              vector<array<double,4> >(n_v));
  int I;//an iterator
  //cast control points into a rectangular array
  for(int i = 0; i < n_u; i++)
  {
    for(int j = 0; j < n_v; j++)
    {
      I = i* n_v + j;
      CtrlPts_rect[i][j] = CtrlPts[I];
    }
  }
  vector<double> a( p_v, 0.0 );
  vector< vector<array <double,4> > > Q(n_u, vector<array<double,4> >(p_v));
  array<double,4> placeHolder;
  for(int i = 0; i < new_Xi_v.size(); i++)
  {
    if(new_Xi_v[i] != Xi_v[i])
    {
      for(int j = 0; j < p_v; j ++)
      {
        int kj = i - (p_v-j);
        //compute alphas making up the convex combination of ctrlpts
        a[j] = (new_Xi_v[i] - Xi_v[kj]) / (Xi_v[kj+p_u] - Xi_v[kj]);

        //compute the ctrlpts to add
        for(int k = 0; k < n_u; k++)
        {
          Q[k][j][0] = (1- a[j])*CtrlPts_rect[k][kj-1][0]
                          + a[j] * CtrlPts_rect[k][kj][0];
          Q[k][j][1] = (1- a[j])*CtrlPts_rect[k][kj-1][1]
                          + a[j] * CtrlPts_rect[k][kj][1];
          Q[k][j][2] = (1- a[j])*CtrlPts_rect[k][kj-1][2]
                          + a[j] * CtrlPts_rect[k][kj][2];
          Q[k][j][3] = (1- a[j])*CtrlPts_rect[k][kj-1][3]
                          + a[j] * CtrlPts_rect[k][kj][3];
        }
      }
  //     //insert a control point, will be replacing p-1 ctrlpts with p ctrlpts
      for(int j = 0; j < n_u; j++)
      {
        CtrlPts_rect[j].insert(CtrlPts_rect[j].begin()+i-p_v+1, placeHolder);
      }
      for(int j = 0; j < n_u; j++)//insert new ctrlpts into ctrlpt array
      {
        for(int k = 0; k < p_v; k++)
        {
          CtrlPts_rect[j][i-p_v + k] = Q[j][k];
        }
      }
      //insert the new knot into the knot vector
      Xi_v.insert(Xi_v.begin()+i, new_Xi_v[i]);
      n_v = Xi_v.size() - p_v - 1;
    }
  }
  //recast ctrlpts to a 1D vector
  vector<array<double,4> > CtrlPtsTmp;
  for(int i = 0; i < n_u; i++)
  {
    for(int j = 0; j < n_v; j++)
    {
      I = i* n_v + j;
      CtrlPtsTmp.push_back(CtrlPts_rect[i][j]);
    }
  }
  CtrlPts = CtrlPtsTmp;
  deproject_ctrlPts(); //get contrl points out of projective space
  getNumberOfElementsAndDOFs();
  return 0; //success!
}
////////////////////////////////////////////////////////////////////////////////
//get a list of knots that refines srf by adding knots between each span
vector<double> Surface::cut_knots_half(int uv)
{
  vector<double> knots_to_add;
  vector<double> * Xi;
  switch(uv)
  {
    case 2:
    Xi = &Xi_v;
    break;
    default:
    Xi = &Xi_u;
  }

  for(int i = 0; i < Xi->size()-1; i++)
  {
    if(Xi->at(i) != Xi->at(i+1))
    {
      knots_to_add.push_back(0.5*(Xi->at(i) + Xi->at(i+1)));
    }
  }
  return knots_to_add;
}
