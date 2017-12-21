// main.cpp
// AUTHOR:  Corey Wetterer-Nelson
// DATE:    8-Nov-2017

#include "run_functions.h"

int main(int argc, char *argv[])
{
  PetscInitialize(&argc, &argv, PETSC_NULL, PETSC_NULL);
  // read in geometry file location
  string geomFile, problemType;
  if(argc > 1) {geomFile = argv[1];}
  else {geomFile = "Geometries/surfBump.nrbpts";}
  cout << geomFile << endl;

  if(argc > 2){problemType = argv[2];}
  else{problemType = "mmsP0";}

  int refinementLevels = 0;
  if(argc > 3){refinementLevels = stoi(argv[3]);}

  //////////////////////////////////////////////////////////////////////////////
  //define the surface object
  Surface srf = Surface(geomFile, 0);

  for(int i = 0; i < refinementLevels; i++)
  {
    srf.refine();
  }

  srf.ready_analysis(true);
  // srf.print_ien_2D();
  // srf.print_extracted_geometry();
  // srf.print_Extraction();
  //////////////////////////////////////////////////////////////////////////////
  //define the problem setup
  Problem prb = Problem(&srf, problemType);

  //////////////////////////////////////////////////////////////////////////////
  //define the solver
  Solver_LaplaceBeltrami slvr = Solver_LaplaceBeltrami(&srf, &prb);

  //////////////////////////////////////////////////////////////////////////////
  slvr.solve();
  slvr.print_Tangent();
  slvr.print_rhs();
  slvr.print_solution_to_file(10);
  slvr.print_sol_vec();

  //////////////////////////////////////////////////////////////////////////////
  //cleanup!
  slvr.petsc_cleanup();
  srf.print();
  PetscFinalize();

}
