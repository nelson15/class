// AUTHOR:  Corey Wetterer-Nelson
// DATE:    18-Nov-2017

//Function print_solution_to_file()
// prints the solution to a file for res number of points per element
#include "run_functions.h"


int Solver_LaplaceBeltrami::print_solution_to_file(int res)
{
  //points in parametric space in 1D to get solution at.
  //should make evenly spaced points along the domain (0,1)
  vector<double> parPts_1D;
  double h = 1.0/((double)res+1);

  for(int i = 1; i < res+1; i++)
  {
    parPts_1D.push_back(i * h);
  }

  vector<array<double,4> > printable_solution;
  array<double,4> point_solution;

  //need some temporary stuff to store all the things
  //that come out of shape_function
  double J;
  vector<array<double, 4> > R_x;
  vector<array<double, 3> > Rxi;
  array<double,3> wfxn;
  array<array<double,2>,3> DF_plus;
  array<double,3> x;
  vector<double> solution_elm(srf->n_dof_local);
  for(int e = 0; e < srf->num_elems; e++)
  {
    VecGetValues(sol_vec, srf->n_dof_local, &(srf->IEN[e][0]),
                  &(solution_elm[0]) );
    for(int p1 = 0; p1 < parPts_1D.size(); p1++)
    {
      for(int p2 = 0; p2 < parPts_1D.size(); p2++)
      {
        srf->shape_function(e, parPts_1D[p1], parPts_1D[p2], &J,
                            &R_x, &Rxi, &wfxn, &DF_plus, &x);
        //get the xyz coords of the point
        point_solution[0] = x[0];
        point_solution[1] = x[1];
        point_solution[2] = x[2];
        //compute the solution at the point
        point_solution[3] = 0;

        for(int a = 0; a < srf->n_dof_local; a++)
        {
            int i = srf->IEN[e][a];
            point_solution[3] += Rxi[a][0] * solution_elm[i];
        }
        //add the point solution to the printable solution vector
        printable_solution.push_back(point_solution);
      }
    }
  }

  ofstream out;

  out.open("./output/solution.m");
  out << "sol = [" << endl;
  for(auto & p : printable_solution)
  {
    out << p[0] << ",\t" << p[1] << ",\t" << p[2] << ",\t" << p[3] << endl;
  }
  out << "];";
  out.close();
  return 0; //success!
}
