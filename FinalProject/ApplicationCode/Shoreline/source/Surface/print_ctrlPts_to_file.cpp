// print_ctrlPts_to_file.cpp
// AUTHOR: Corey Wetterer-Nelson
// DATE: 18-Dec-2017

//Function print_ctrlPts_to_file()
//prints the control points to a file
#include "run_functions.h"

int Surface::print_ctrlPts_to_file()
{
  ofstream out;

  out.open("./output/CtrlPts.csv");

  for(auto & c : CtrlPts)
  {
    out << c[0] << ", "<< c[1] << ", "<< c[2] << ", "<< c[3] << endl;
  }
  out.close();
  return 0;
}
