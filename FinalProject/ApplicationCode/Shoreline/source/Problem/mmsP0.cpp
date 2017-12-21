#include "run_functions.h"
int Problem::mmsP0_bc_and_g()
{
  for(i = 0; i < srf->n_u; i++)
  {
    for(j = 0; j < srf->n_v; j++)
    {
      I = i * srf->n_v + j;
      if(i == 0)
      {
        BC[I] = 1;
        g[I]  = 1;
      }
      if(i == srf->n_u || j == srf->n_v || j == 0)
      {
        BC[I] = 1;
        g[I]  = 0;
      }
    }
  }
  return 0; //success!
}

int Problem::mmsP0_forcing()
{
  fill(forcing.begin(), forcing.end(), 0.0); //no forcing
  return 0; //success!
}
