// Surface.cpp
// AUTHOR:  Corey Wetterer-Nelson
// DATE:    8-Nov-2017

//Class Surface
//Stores information about the NURBS surface being computed over
#include "run_functions.h"
using namespace std;
////////////////////////////////////////////////////////////////////////////////
//default constructor makes a flat plate single element surface
Surface::Surface()
{
  this->id = 0;
  this->p_u = 2;
  this->p_v = 2;
  this->n_u = 3;
  this->n_v = 3;
  this->num_elems_u = 1;
  this->num_elems_v = 1;
  string type = "linear";
  //knotVecCreate(num_elems_u, p_u, 0.0, 1.0, 1.0, type, &this->Xi_u);
  //knotVecCreate(num_elems_v, p_v, 0.0, 1.0, 1.0, type, &this->Xi_v);

  //need to define the control points...

}

////////////////////////////////////////////////////////////////////////////////
//standard constructor: import geometry from file
Surface::Surface(string geomFile, int id)
{
  this->id = id;
  int err = import_Geometry(geomFile);
  if(err)
  {
    throw runtime_error("Geometry Import Failed");
  }
  //compute the knot vectors for the surface
  compute_knots();
  cout << "Knot vectors generated for Surface " << id << endl;

  //get a handful of parameters of the surface (number of elements, DOF's etc)
  getNumberOfElementsAndDOFs();
  cout << "Number of elements and DOF's generated for Surface " << id << endl;

  //normalize the knot vectors to be from 0 to 1
  normalize_knots();
  cout << "Knots normalized for Surface " << id << endl;

  //pad endpoint knot vectors to make them open
  //pad_knots();
  //cout << "Endpoint knots made open for Surface " << id << endl;

  ready_analysis(true);
}

////////////////////////////////////////////////////////////////////////////////
//print the defining parameters of the surface: p_u,p_v,n_u,n_v and ctrlpts
int Surface::print(bool ctrlpts, bool knots)
{
  cout << "NURBS Surface: ID " << this->id << endl;
  cout << "===================" << endl;
  cout << "p_u = " << this->p_u;
  cout << ", p_v = " << this->p_v << endl;
  cout << "n_u = " << this->n_u;
  cout << ", n_v = " << this->n_v << endl;
  cout << "num_elems_u = " << this-> num_elems_u;
  cout << ", num_elems_v = " << this-> num_elems_v << endl << endl;

  cout << "cyclic_u: " << this->use_cyclic_u << endl;
  cout << "cyclic_v: " << this->use_cyclic_v << endl;
  cout << "bezier_u: " << this->use_bezier_u << endl;
  cout << "bezier_v: " << this->use_bezier_v << endl;
  cout << "endpnt_u: " << this->use_endpoint_u << endl;
  cout << "endpnt_v: " << this->use_endpoint_v << endl << endl;

  if(ctrlpts)
  {
    cout << "Control Points: " << endl;
    for(auto & k : this->CtrlPts)
    {
      cout << "( " << k[0] << ", " << k[1] << ", "
           << k[2] << ", " << k[3] << " )" << endl;
    }
  }

  if(knots)
  {
    cout << "Xi_u" << endl << "====" << endl;
    for(auto & xi : this->Xi_u) {cout << xi << endl;}
    cout << endl;
    cout << "Xi_v" << endl << "====" << endl;
    for(auto & xi : this->Xi_v) {cout << xi << endl;}
  }
  return 0;//success!
}

////////////////////////////////////////////////////////////////////////////////
//import_Geometry() reads in a .nrbpts file and sets the Surface object to that
//                  read in surface.
int Surface::import_Geometry(string geomFile)
{
  ifstream infile;
  infile.open(geomFile);

  if(!infile.is_open())
  {
    cerr << "File not opened" <<endl;
    //return 1;
  }

  string tmp1;
  string tmp2;
  istringstream is1;
  istringstream is2;

  //////////////////////////////////////////////////////////////////////////////
  //read out the polynomial order (first line)
  getline(infile, tmp1, ',');
  getline(infile, tmp2, '\n');
  is1.str(tmp1);
  is2.str(tmp2);
  is1 >> this->p_u;
  is2 >> this->p_v;

  //////////////////////////////////////////////////////////////////////////////
  //read out the number of control points (second line)
  getline(infile, tmp1, ',');
  getline(infile, tmp2, '\n');
  is1.str(tmp1);
  is2.str(tmp2);
  is1.clear();//clear any flags set in the is stringstream
  is2.clear();
  is1 >> this->n_u;
  is2 >> this->n_v;
  // this->n_u = stod(tmp1);
  // this->n_v = stod(tmp2);

  //////////////////////////////////////////////////////////////////////////////
  //read in use cyclic (third line)
  getline(infile, tmp1, ','); //read in u and v flags
  getline(infile, tmp2, '\n');
  transform(tmp1.begin(), tmp1.end(), tmp1.begin(), ::tolower); //lowercase
  transform(tmp2.begin(), tmp2.end(), tmp2.begin(), ::tolower);
  is1.str(tmp1); //set the string stream
  is2.str(tmp2);
  is1.clear();//clear any flags set in the is stringstream
  is2.clear();
  is1 >> std::boolalpha >> this->use_cyclic_u;
  is2 >> std::boolalpha >> this->use_cyclic_v;

  //////////////////////////////////////////////////////////////////////////////
  //read in use bezier (fourth line)
  getline(infile, tmp1, ','); //read in u and v flags
  getline(infile, tmp2, '\n');
  transform(tmp1.begin(), tmp1.end(), tmp1.begin(), ::tolower); //lowercase
  transform(tmp2.begin(), tmp2.end(), tmp2.begin(), ::tolower);
  is1.str(tmp1); //set the string stream
  is2.str(tmp2);
  is1.clear();//clear any flags set in the is stringstream
  is2.clear();
  is1 >> std::boolalpha >> this->use_bezier_u;
  is2 >> std::boolalpha >> this->use_bezier_v;

  //////////////////////////////////////////////////////////////////////////////
  //read in use endpoint (fifth line)
  getline(infile, tmp1, ','); //read in u and v flags
  getline(infile, tmp2, '\n');
  transform(tmp1.begin(), tmp1.end(), tmp1.begin(), ::tolower); //lowercase
  transform(tmp2.begin(), tmp2.end(), tmp2.begin(), ::tolower);
  is1.str(tmp1); //set the string stream
  is2.str(tmp2);
  is1.clear();//clear any flags set in the is stringstream
  is2.clear();
  is1 >> std::boolalpha >> this->use_endpoint_u;
  is2 >> std::boolalpha >> this->use_endpoint_v;

  //////////////////////////////////////////////////////////////////////////////
  //read in control points (rest of the file)
  string x,y,z,w;
  vector< array<double,4> > data;
  array <double,4> ctrlpt;
  //read out the control points
  while(infile.good())
  {
    getline(infile, x, ',');
    getline(infile, y, ',');
    getline(infile, z, ',');
    getline(infile, w, '\n');
    //cout << x << ", " << y << ", " << z << ", " << w << endl;
    try
    {
      ctrlpt[0] = stod(x);
      ctrlpt[1] = stod(y);
      ctrlpt[2] = stod(z);
      ctrlpt[3] = stod(w);
      data.push_back(ctrlpt);
    }
    catch(const invalid_argument &e) {}
  }

  if(this->CtrlPts.size() > 0) //if the CtrlPts has data, delete it all
  {
    this->CtrlPts.reserve(0);
  }

  for(auto & k : data)
  {
    this->CtrlPts.push_back(k);
  }
  infile.close();
  cout << "Geometry read, file closed." << endl << endl;
  return 0;//success!
}

////////////////////////////////////////////////////////////////////////////////
//just computes the number of elements on surface along with number of DOF's on
// the whole surface and on any given element
int Surface::getNumberOfElementsAndDOFs()
{
  //count the knot spans in Xi_u
  double xiLast = this->Xi_u[0];
  int nelemU = 0;
  for(auto & xi : this->Xi_u)
  {
    if(xi != xiLast)
    {
      nelemU++;
    }
    xiLast = xi;
  }
  this->num_elems_u = nelemU;

  //count the knot spans in Xi_v
  xiLast = this->Xi_v[0];
  int nelemV = 0;
  for(auto & xi : this->Xi_v)
  {
    if(xi != xiLast)
    {
      nelemV++;
    }
    xiLast = xi;
  }
  this->num_elems_v = nelemV;

  this->num_elems = this->num_elems_u * this->num_elems_v;

  //also compute the number of degrees of freedom on an element
  this->n_dof_local = (this->p_u+1)*(this->p_v+1);
  this->n_dof_global = this->CtrlPts.size();
  //get the number of global dofs in each direction
  this->n_u = this->Xi_u.size() - this->p_u - 1;
  this->n_v = this->Xi_v.size() - this->p_v - 1;

  return 0;
}
