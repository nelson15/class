// Extraction_1D.cpp
// AUTHOR:  Corey Wetterer-Nelson
// DATE:    6-Nov-2017

//Function print_Extraction()
//prints the 1D extraction operator

//INPUTS:
// C = storage of extraction operator
// num_elem = number of elements in 1D
// p = polynomial degree
// elems = number of element operators to actually print (starts from 0)
//          a negative value will print all the elements

//OUTPUTS:
// NONE: just prints to std_out
#include "run_functions.h"

int print_Extraction(double *** C, int num_elem, int p, int elems)
{
  int e, i, j; //some iterators
  if(elems < 0)
  {num_elem = num_elem;}
  else{num_elem = elems;} //print only the first elems elements

  for(e = 0; e < num_elem; e++)
  {
    cout << "Element " << e << endl;
    for(i = 0; i < p+1; i++)
    {
      for(j = 0; j < p+1; j++)
      {
        cout << C[e][i][j] << " ";
      }
      cout << endl;
    }
    cout << endl << endl;
  }
  return 0; //success!
}
