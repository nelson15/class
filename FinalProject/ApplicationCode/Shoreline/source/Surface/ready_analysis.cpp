// ready_analysis.cpp
// AUTHOR:  Corey Wetterer-Nelson
// DATE:    10-Nov-2017

//Function ready_analysis()
// get the IEN array and the extraction operator
#include "run_functions.h"

int Surface::ready_analysis(bool Verbose)
{
  //build the IEN array for the Surface
  ien_2D();
  if(Verbose)
  {
    cout << "IEN array generated for Surface " << id << endl;
  }


  //build the extraction operator for all the elements on the surface
  extraction_2D();
  if(Verbose)
  {
    cout << "Extraction operators generated for Surface " << id << endl;
  }


  //get the extracted control points defining each element
  extract_Geometry();
  if(Verbose)
  {
    cout << "Element level control points extracted for Surface " << id << endl;
  }
  return 0; //success!
}
