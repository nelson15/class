// Surface.h
// AUTHOR:  Corey Wetterer-Nelson
// DATE:    8-Nov-2017

//Class Surface
//Stores information about the NURBS surface being computed over

#include "run_functions.h"
#ifndef SURFACE_H
#define SURFACE_H
using namespace std;
class Surface
{
public:
  int id;  //surface ID (will probs be useful in multipatch setting)
  int p_u; //polynomial degree in u direction
  int p_v; //polynomial degree in v direction
  int n_dof_local; //number of degrees of freedom on an element (p_u+1)*(p_v+1)
  int n_dof_global;//number of degrees of global degrees of freedom on surface
  int n_u; //number of bases in u direction
  int n_v; //number of bases in v direction
  bool use_cyclic_u, use_cyclic_v; //use cyclic knot vector in direction
  bool use_bezier_u, use_bezier_v; //use bezier knot vector in direction
  bool use_endpoint_u, use_endpoint_v; //use endpoint (open) knot vector
  int num_elems_u; //number of elements in u direction
  int num_elems_v; //number of elements in v direction
  int num_elems;   //number of elements over the 2D surface
  vector<double> Xi_u; //knot vector in u direction
  vector<double> Xi_v; //knot vector in v direction
  vector< array <double,4> > CtrlPts; //list of control points+weights [x,y,z,w]
  bool ctrlPtsprojective;

  //IEN arrays. we will maintain a u and v direction 1D IEN along with the full
  // 2D IEN arrays
  vector< vector <int> > ien_u; //(num_elem_u x p_u+1)
  vector< vector <int> > ien_v; //(num_elem_v x p_v+1)
  vector< vector <int> > IEN; //2D IEN array

  //extracted control points (num_elems, n_dof_local, 4(x,y,z,w))
  vector< vector< array <double,4> > > CtrlPts_extracted;

  vector< vector< vector<double> > > C_u; //extraction operator in u direction
  vector< vector< vector<double> > > C_v; //extraction operator in v direction
  vector< vector< vector<double> > > C;   //extraction operator for surface

  int n_gauss_u; //number of gauss points in the u direction on an element
  int n_gauss_v; //number of gauss points in the v direction on an element
  int n_gauss; //= n_gauss_u * n_gauss_v

  //Bernstein basis (n_gauss,n_dof_local, 3(val, ddx_u, ddx_v))
  vector< vector< array<double,3> > >B;
  //////////////////////////////////////////////////////////////////////////////
  //Constructors
  Surface(); //default constructor, builds a flat plane with 4x4 nodes
  Surface(string geomFile, int id); //constructor takes a path to a .nrbpts file

  //////////////////////////////////////////////////////////////////////////////
  //Surface class methods
  int import_Geometry(string geomFile); //import a geometry from a .nrbpts file
  //int subdivide_surf(int uv, int index); //depricated
  int refine_Surface(int levels); //refine the surface recursively
  int print(bool ctrlpts = false, bool knots = false); // print the surface
  int getNumberOfElementsAndDOFs(); //get number of elements on surface
  int ready_analysis(bool Verbose); //make IEN array and extract geometry

  //////////////////////////////////////////////////////////////////////////////
  //knot vector methods
  int num_knots(int uv);
  int num_segments(int uv);
  int normalize_knots();
  int compute_knots();
  int makeknots(int uv);
  int calcknots(vector<double> *knots, int pnts, int order, int flag);
  int makecyclicknots(vector<double> *knots, int pnts, int order);

  //////////////////////////////////////////////////////////////////////////////
  //IEN functions
  int ien_1D(int uv); //builds a 1D ien array in the u or v direction (1 or 2)
  int ien_2D(); //builds the full IEN array for the surface
  int print_ien_1D(int uv); //print the 1D ien array in the uv (1 or 2)direction
  int print_ien_2D(); //print the 2D ien array

  //////////////////////////////////////////////////////////////////////////////
  //Surface refinement methods
  int add_knots_u(vector<double> knots_to_add);
  int add_knots_v(vector<double> knots_to_add);
  vector<double> cut_knots_half(int uv);
  int refine();
  int project_ctrlPts(); //project ctrl pts to projective space
  int deproject_ctrlPts(); //get ctrl pts out of projective space
  int print_ctrlPts_to_file();

  //////////////////////////////////////////////////////////////////////////////
  //extraction operator methods
  int extraction_1D(int uv); //create extraction operator in 1 direction
  int extraction_2D(); //build the extraction operator for all elements (2D)
  int print_Extraction(); //print the 2D extraction operator
  int print_Extraction_1D(int uv); //print 1D extraction operator
  int extract_Geometry(); //compute extracted control points and weights
  int print_extracted_geometry();//print the extracted control points

  //////////////////////////////////////////////////////////////////////////////
  //basis function functions
  int surf_basis(double xi1, double xi2);//not implemented yet...
  int shape_function(int e, double xi_u, double xi_v, double * J,
      vector<array<double, 4> > *R_x, vector<array<double, 3> > *Rxi,
      array<double,3>*wfxn, array<array<double,2>,3> *DF_plus,
      array<double,3> * x);
};
#endif //SURFACE_H
