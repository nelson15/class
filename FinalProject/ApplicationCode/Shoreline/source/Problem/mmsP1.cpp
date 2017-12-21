#include "run_functions.h"
int Problem::mmsP1_bc_and_g()
{
  for(i = 0; i < srf->n_u; i++)
  {
    for(j = 0; j < srf->n_v; j++)
    {
      I = i * srf->n_v + j;
      if(i == 0 ||i == srf->n_u || j == srf->n_v || j == 0)
      {
        BC[I] = 1;
      }
    }
  }
  return 0; //success!
}

int Problem::mmsP1_forcing()
{
  for(int i = 0; i < forcing.size(); i++)
  {
    forcing[i] = 1;
  }
  return 0; //success!
}
