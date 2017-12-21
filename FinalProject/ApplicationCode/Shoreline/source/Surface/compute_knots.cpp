#include "run_functions.h"
//much of these functions are largely based on those from the Blender source
//code

int Surface::num_knots(int uv)//function returns number of knots
{
  if(uv == 1){return this->p_u + this->n_u + (this->p_u -1)*this->use_cyclic_u;}
  if(uv == 2){return this->p_v + this->n_v + (this->p_v -1)*this->use_cyclic_v;}
  else{return 0;}
}
int Surface::num_segments(int uv)//function returns number of elements
{
  if(uv == 1){return this->n_u - !this->use_cyclic_u;}
  if(uv == 2){return this->n_v - !this->use_cyclic_v;}
  else{return 0;}
}

//Normalize knot vectors to be from 0 to 1
int Surface::normalize_knots()
{
  double kuMax = Xi_u.back();
  double kvMax = Xi_v.back();

  for(auto & x : Xi_u){x = x/kuMax;}
  for(auto & x : Xi_v){x = x/kvMax;}
  return 0;//success!
}

int Surface::compute_knots()
{
  int err = 0;
  err += makeknots(1);
  err += makeknots(2);
  return err; //hopefully 0

}

int Surface::makeknots(int uv)
{
  int err = 0;
  int flag;
  if (uv == 1)
  {
    //empty out the original knot
    if (!this->Xi_u.empty()) {this->Xi_u.reserve(0);}
    this->Xi_u.reserve(4 + this->num_knots(1));

    flag = this->use_endpoint_u + (this->use_bezier_u << 1);
    if (this->use_cyclic_u)
    {
      //cout << "u knot is cyclic \n";
      /* cyclic should be uniform */
      err += calcknots(&this->Xi_u, this->n_u, this->p_u, 0);
      //cout << "knot allocated \n";
      //cout << "Xi_u \n";
      //for(auto & xi : this->Xi_u){cout << xi << endl;}
      err += makecyclicknots(&this->Xi_u, this->n_u, this->p_u);
      //cout << "u knot is made cyclic \n";
    }
    else {
      //cout << "u knot is not cyclic \n";
      err += calcknots(&this->Xi_u, this->n_u, this->p_u, flag);
    }
  }
  else if (uv == 2)
  {
    //empty out the original knot
    if (!this->Xi_v.empty()) {this->Xi_v.reserve(0);}
    this->Xi_v.reserve(4 + this->num_knots(2));

    flag = this->use_endpoint_v + (this->use_bezier_v << 1);
    if (this->use_cyclic_v)
    {
      //cout << "v knot is cyclic \n";
      /* cyclic should be uniform */
      err += calcknots(&this->Xi_v, this->n_v, this->p_v, 0);
      err += makecyclicknots(&this->Xi_v, this->n_v, this->p_v);
      //cout << "v knot is made cyclic \n";
    }
    else {
      //cout << "v knot is not cyclic \n";
      err += calcknots(&this->Xi_v, this->n_v, this->p_v, flag);
    }
  }
  return err;
}

int Surface::calcknots(vector<double> *knots, int pnts, int order, int flag)
{
  /* knots: number of pnts NOT corrected for cyclic */
  int pnts_order = pnts + order+1;
  double k;
  int a;
  //cout << "flag is " << flag << endl;
  //cout << "knot vector is size: " << knots->size() << endl;
  switch (flag)
  {
    case 1:
      k = 0.0;
      for (a = 1; a <= pnts_order; a++)
      {
        knots->push_back(k);
        if (a >= order + 1 && a <= pnts)
          k += 1.0;
      }
      break;
    case 2:
      /* Warning, the order MUST be 3 or 4,
      * if this is not enforced, the displist will be corrupt */
      if (order == 4)
      {
        k = 0.34;
        for (a = 0; a < pnts_order; a++)
        {
          knots->push_back( floorf(k) );
          k += (1.0 / 3.0);
        }
      }
      else if (order == 3) {
        //cout << "case 2, order 3" << endl;
        k = 0.6;
        for (a = 0; a < pnts_order; a++)
        {
          if (a >= order && a <= pnts)
                 k += 0.5;
          knots->push_back( floorf(k) );

        }
        cout << endl;
      }
      else
      {
        printf("bez nurb curve order is not 3 or 4, should never happen\n");
        return 1; //error!
      }
      break;
    default:
      for (a = 0; a < pnts_order; a++) {
        knots->push_back((double)a);
        cout << a << endl;
      }
      break;
  }
  return 0; //success!
}

int Surface::makecyclicknots(vector<double> *knots, int pnts, int order)
/* pnts, order: number of pnts NOT corrected for cyclic */
{
  int a, b, order2, c;

  if (knots->empty())
  {
    cout << "empty knot vector, cannot convert to cyclic." << endl;
    return 1;
  } //empty knot vector! can't make it cyclic

  order2 = order - 1;

  /* do first long rows (order -1), remove identical knots at endpoints */
  if (order > 2) {
    b = pnts + order2;
    for (a = 1; a < order2; a++)
    {
      if (knots->at(b) != knots->at(b - a)) {break;}
    }
    if (a == order2) {knots->at(pnts + order - 2) += 1.0;}
  }

  b = order;
  c = pnts + order + order2;
  for (a = pnts + order2; a < c; a++) {
    if(a < knots->size())
    {
      knots->at(a) = knots->at(a - 1) + (knots->at(b) - knots->at(b - 1));
    }
    else if(a >= knots->size())
    {
      knots->push_back( knots->at(a - 1) + (knots->at(b) - knots->at(b - 1)) );
    }
    b--;
  }
  return 0;//success!
}
