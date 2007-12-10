/* Author: 
   Nicholas Lewin-Koh <nikko@hailmail.net>.  
   All rights reserved.

   Redistribution and use in source and binary forms, with or without
   modification.

   There is NO WARRANTY, not even for MERCHANTABILITY or FITNESS FOR A
   PARTICULAR PURPOSE.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "spantree.h"
#include <R.h>

void mstree(int *n, int *p, int *alg, double *data, int *mst_list,
	    double *dist)
{
  unf_mst_result *mst;
  int i;
  struct unf_mst *mst_alg = &unf_mst_prim_binary;

  if (*alg == 1)
    mst_alg = &unf_mst_prim_binary;
  else if (*alg == 2)
    mst_alg = &unf_mst_prim_fibonacci;
  else if (*alg == 3)
    mst_alg = &unf_mst_prim_dist_fibonacci;
  else
    {
      Rprintf ("unknown MST algorithm `%d'\n", *alg);
	  
    }

  mst = mst_alg->unf_run (&unf_mem_malloc, data, *n,*p, dist);
  if (mst == NULL)
    {
      error("virtual memory exhausted\n");
    }


   
  for (i = 0; i < (*n)-1 ; i++)
    {
/*        if(mst[i][1]==0){ */
/*  	mst_list[0]=mst[i][0]+1; */
/*  	mst_list[mst[i][0]]=i+1; */
/*        } */
/*        else mst_list[mst[i][0]]=mst[i][1]+1; */

      mst_list[i]=mst[i][0]+1;
      mst_list[i+(*n-1)]=mst[i][1]+1;
     /*   Rprintf("%d,%d \n",mst[i][0]+1,mst[i][1]+1); */ 
    }

  free (mst);

  return;
}

void mstree_krusk(int *n, int *p, int *alg, double *data, int *mst_list,
		  int *nE, int *to, int *from, int *pind, double *dist)
{
  unf_mst_result *mst;
  int i;
  edges Elist;
  struct unf_mst_krusk *mst_alg = &unf_mst_krusk_sort;
  
  Elist.to = to;
  Elist.from = from;
  Elist.pind = pind;  
  Elist.nE = *nE;
  Elist.wt = (double *) R_alloc(*nE, sizeof(double));

  mst = mst_alg->unf_run (&unf_mem_malloc, &Elist, data, *n,*p, dist);
  if (mst == NULL)
    {
      error("virtual memory exhausted\n");
    }
 
  for (i = 0; i < (*n)-1 ; i++)
    {
      mst_list[i]=mst[i][0];
      mst_list[i+(*n-1)]=mst[i][1];

    }

  free (mst);

  return;
}



