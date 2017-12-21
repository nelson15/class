// Extraction_1D.cpp
// AUTHOR:  Corey Wetterer-Nelson
// DATE:    29-Nov-2017

//Function Extraction_1D()
//computes the extraction operator for a 1D set of B-spline bases

//INPUTS:
//  direction = 0 or 1, u or v respectively

//OUTPUTS:
// C_op = list of element extraction matrices
//#define DEBUG_EX
#include "run_functions.h"

int Surface::extraction_1D(int uv)
{
  int p, num_elem;
  bool use_cyclic;
  vector<double> * Xi;
  vector< vector<vector<double> > > * C_op;
  vector< vector<vector<double> > > * C_op2;

  vector<double> Xi_expanded;
  vector< vector< vector<double> > > C_expanded;
  C_op = &C_expanded;

  //////////////////////////////////////////////////////////////////////////////
  //get the info in the desired direction
  switch(uv) //pick the direction
  {
    case 2: //v direction
      Xi_expanded = Xi_v;
      p = this->p_v;
      C_op = &(this->C_v);
      C_op2 = &(this->C_v);
      num_elem = this->num_elems_v;
      use_cyclic = this->use_cyclic_v;
      break;

    default:
      //u direction
      Xi_expanded = Xi_u;
      p = this->p_u;
      C_op = &(this->C_u);
      C_op2 = &(this->C_u);
      num_elem = this->num_elems_u;
      use_cyclic = this->use_cyclic_u;
  }
  //////////////////////////////////////////////////////////////////////////////
  //pad knot vector
  if(use_cyclic) //need to pad the knot vector
  {
    vector< vector< vector<double> > > C_expanded;
    C_op = &C_expanded;
    //assume linearly spaced knots
    double disp = Xi_expanded[1] - Xi_expanded[0];
    for(int i = 0; i < p; i++)
    {
      Xi_expanded.insert(Xi_expanded.begin(), Xi_expanded[0] - disp);
      Xi_expanded.push_back(Xi_expanded.back() + disp);
    }
    for(int i = 0; i < p; i++)//make the knot vector open
    {
      Xi_expanded.insert(Xi_expanded.begin(), Xi_expanded[0]);
      Xi_expanded.push_back(Xi_expanded.back());
    }
    num_elem += 2*p; //added p ghost elements to front and back of knots

  }
  Xi = &Xi_expanded;
  //////////////////////////////////////////////////////////////////////////////
  //get extracting!

  #ifdef DEBUG_EX
  cout << "extracting in " << uv << " direction." << endl;
  cout << "Knot Vector" << endl;
  for(auto & x: *Xi)
  {
    cout << x << ", ";
  }
  cout << endl;
  cout << "p = " << p << endl;
  cout << "num_elem = " << num_elem << endl;
  #endif

  int a = p;//first element
  int b = a+1;
  int nb = 0; //number of elements
  int i, mult, r, save, s;//some indices and iterators needed below
  double numer = 0; double alpha;

  vector<double> alphas;
  alphas.resize(p-1);

  //resize C_op to fit the element extraction operators (all p+1 x p+1)
  C_op->resize(num_elem, vector<vector<double> >(p+1,vector<double>(p+1)));

  #ifdef DEBUG_EX
  cout << "Size of C: " << C_op->size() << ", " << C_op->at(0).size()
       << ", " << C_op->at(0)[0].size() << endl;
  #endif

  set_Identity(&(C_op->at(0)), p+1); //set first extraction op to identity

  #ifdef DEBUG_EX
  cout << "First op set to identity" << endl;
  #endif

  while(b < Xi->size())
  {
    if(nb+1 < num_elem)
    {
      set_Identity(&(C_op->at(nb+1)),p+1); //initialize next operator
    }
    #ifdef DEBUG_EX
    cout << nb << " op set to identity" << endl;
    #endif

    i = b;
    //Scoot over to next unrepeated knot
    while (b < Xi->size() && Xi->at(b) == Xi->at(b-1)){ b++; }
    mult = b - i + 1; //get multiplicity of last knot

    if(mult < p)
    {
      numer = Xi->at(b) - Xi->at(a); //Correct!
      //cout << "numer " << numer << endl;
      fill(alphas.begin(), alphas.end(), 0.0);
      for(int j = mult+1; j < p+1; j++)//compute alphas from Bohm's Algorithm
      {

        alphas[j-mult-1] = numer/(Xi->at(a+j) - Xi->at(a));
      }

      r = p-mult;//compute the number of added knots
      for( int j = 1; j < r+1; j++)
      {
        save = r - j;//get the region of overlap
        s = mult + j;
        for(int k = p; k >= s; k--)
        {
          alpha = alphas[k-s];
          for(int l = 0; l < p+1; l++)//application of Bohm's Algorithm
          {
            C_op->at(nb)[l][k] = alpha * C_op->at(nb)[l][k]
                            + (1-alpha) * C_op->at(nb)[l][k-1];
          }
        }
        if(b < Xi->size() && nb+1 < num_elem)
        {
          for(int l = 0; l < j+1; l++)//update overlapping coefficients
          {
            C_op->at(nb+1)[save+l][save] = C_op->at(nb)[p-j + l][p];
          }
        }
      }
    }
    if(b < Xi->size())
    {
      a = b;
      b++;
      nb++;
    }
  }//end while(b < Xi->size())

  //////////////////////////////////////////////////////////////////////////////
  //for the cyclic knot vector case, we added p elements to the front and
  //back of the knot vector, so we end up with 2p extra extraction operators
  //we need to cut out the middle ones we want
  if(use_cyclic)
  {
    //cout << "Casting cyclic operator to stored op" << endl;
    C_op2->resize(num_elem - 2*p, vector<vector<double> >(p+1,vector<double>(p+1)));
    for(int e = p; e < num_elem - p; e++) //num_elem reflects the expanded Xi
    {
      for(int i = 0; i < p+1; i++)
      {
        for(int j = 0; j < p+1; j++)
        {
          C_op2->at(e-p)[i][j] = C_op->at(e)[i][j];
        }
      }
    }
  }
  return 0;//success!
}//end function


////////////////////////////////////////////////////////////////////////////////
//sets a matrix to the identity matrix
//assume square matrix with dimension m
//sort of quick and dirty, but will get the job done
int set_Identity(vector<vector<double> > * A, int m)
{
  for(int i = 0; i < m; i++)
  {
    for(int j = 0; j < m; j++)
    {
      if( i == j ){ A->at(i)[j] = 1.0; }
      else{ A->at(i)[j] = 0.0; }
    }
  }
  return 0; //success!
}
