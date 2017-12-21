//testing out shape_function
double J;
vector<array<double, 4> > R_x;
vector<array<double, 3> > Rxi;
array<array<double,2>,3> DF;
array<double,3> x;
array<double,3> wfxn;

double qptu = slvr.quad_pt[0];
double qptv = slvr.quad_pt[1];
int e = 0;
cout << "Quad Point for testing: (" << qptu << ", " << qptv << ")" << endl;
srf.shape_function(e,qptu, qptv, &J, &R_x, &Rxi, &wfxn, &DF, &x);

cout << " J = " << J << endl;


cout << "R_x" << endl;
for(auto & r : R_x)
{
  for(auto & ri :r)
  {
    cout << ri << ", ";
  }
  cout << endl;
}
