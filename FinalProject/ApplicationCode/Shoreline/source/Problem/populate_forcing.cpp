// populate_forcing.cpp
// AUTHOR: Corey Wetterer-Nelson
// DATE: 11-Dec-2017

//Function populate_forcing()
//populate a vector of length srf->n_dof_global to store the steady state
//forcing for the specified problem
#include "run_functions.h"
int Problem::populate_forcing(string problemType)
{
  forcing.resize(srf->n_dof_global);
  if(problemType == "mmsP0")
  {
    cout << "Method of Manufactured Solutions, Problem 0 Chosen," <<
              " Applying Forcing..." << endl << endl;
    mmsP0_forcing();
    return 0;
  }
  else if(problemType == "mmsP1")
  {
    cout << "Method of Manufactured Solutions, Problem 1 Chosen," <<
              " Applying Forcing..." << endl << endl;
    mmsP1_forcing();
    return 0;
  }
  else
  {
    cout << "Problem with indicator " << problemType
          << endl << "Exiting." << endl;
    return 1; //failure
  }
}
