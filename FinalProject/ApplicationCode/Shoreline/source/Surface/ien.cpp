//ien.cpp
// AUTHOR:  Corey Wetterer-Nelson
// DATE:    29-Nov-2017
#include "run_functions.h"

////////////////////////////////////////////////////////////////////////////////
// builds an IEN array in 1 direction u or v (0 or 1)
int Surface::ien_1D(int uv)
{
  int n, p, num_elem;
  bool use_cyclic; //need to fix the last p elements to wrap the ordering around
  vector<double> * Xi;
  vector< vector <int> > * ien;

  switch(uv) //pick the direction
  {
    case 2: //v direction
      p = this->p_v;
      n = this->n_v;
      Xi = &this->Xi_v;
      ien = &this->ien_v;
      num_elem = this->num_elems_v;
      use_cyclic = this->use_endpoint_v;
      break;

    default: //u direction
      p = this->p_u;
      n = this->n_u;
      Xi = &this->Xi_u;
      ien = &this->ien_u;
      num_elem = this->num_elems_u;
      use_cyclic = this->use_endpoint_u;
  }

  //resize ien array to be size (num_elem, p+1)
  ien->resize(num_elem, vector<int>(p+1));


  int l = p+1; //knot span
  int e = 0; //element

  while(l < n + 2)
  {
    for(int a = 0; a < p+1; a++) //fill element e's ien vector
    {
      ien->at(e)[a] = (l+a) - (p+1);
      //cout <<ien->at(e)[a] << ", ";
    }
    //cout << endl;
    l++;

    while(Xi->at(l) == Xi->at(l-1) && l < (Xi->size() - 1))
    {
      l++;
    }
    e++;
  }
  return 0; //success!
}

////////////////////////////////////////////////////////////////////////////////
//IEN_2D builds the 2D IEN array on the surface
 int Surface::ien_2D()
 {
   ien_1D(1); //build the u ien array
   ien_1D(2); //build the v ien array

   IEN.resize((this->num_elems), vector<int>(this->n_dof_local));

   int eu, ev, au, av, iu, iv, e, a, i;
   for(eu = 0; eu < num_elems_u; eu++)
   {

     for(au = 0; au < p_u + 1; au++)
     {
       iu = ien_u[eu][au];

       for(ev = 0; ev < num_elems_v; ev++)
       {
         for(av = 0; av < p_v + 1; av++)
         {
           iv = ien_v[ev][av];
           e = eu * num_elems_v + ev;
           a = au * (p_v + 1) +av;
           i = iu*n_v + iv;
           IEN[e][a] = i;
         }
       }
     }
   }
   return 0; //success!
 }

////////////////////////////////////////////////////////////////////////////////
//print the 2D ien array
int Surface::print_ien_2D()
{
  for(auto & e : IEN)
  {
    for(auto & a: e)
    {
      cout << a << ", ";
    }
    cout << endl;
  }
  return 0; //success!
}

////////////////////////////////////////////////////////////////////////////////
//print the 1D ien array
int Surface::print_ien_1D(int uv)
{
  vector <vector<int> > * the_ien;
  switch(uv)
  {
    case 2:
    the_ien = &ien_v;
    break;
    default:
    the_ien = &ien_u;
  }
  for(auto & e : *the_ien)
  {
    for(auto & a: e)
    {
      cout << a << ", ";
    }
    cout << endl;
  }
  return 0; //success!
}
