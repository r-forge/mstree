/* Copyright (c) 2002 Nicholas Lewin-Koh <kohnicho@comp.nus.edu.sg>.  
   All rights reserved.

   Redistribution and use in source and binary forms, with or without
   modification, are permitted provided that the following conditions are
   met:

     - Redistributions of source code must retain the above copyright
       notice, this list of conditions, and the following disclaimer.

     - Redistributions in binary form must reproduce the above copyright
       notice, this list of conditions, and the following disclaimer in
       the documentation and/or other materials provided with the
       distribution.

   There is NO WARRANTY, not even for MERCHANTABILITY or FITNESS FOR A
   PARTICULAR PURPOSE. */

#include <assert.h>
#include <stdio.h>
#include <math.h>
/*  #include "pq.h" */
#include "spantree.h"
#include "sets.h"
#include "R.h"
#include "Rmath.h"

/* Calculates and returns the distance between points |a| and |b|, 
   each in |d| dimensions. */
static double 
calc_distance (const double *a, const double *b, int d) 
{
  double sum = 0.0;

  assert (a != NULL && b != NULL && d >= 0);
  while (d--) 
    {
      double diff = *a++ - *b++;
      sum += R_pow(diff,2);
    }

  return sum;
}

static double 
calc_lp_dist(const double *a, const double *b, double lp, int d) 
{
  double sum = 0.0, diff=0.0, max=0.0;

  assert (a != NULL && b != NULL && d >= 0);
  if(R_FINITE(lp)){
    while (d--) 
      {
	diff = fabs(*a++ - *b++);
	sum += R_pow(diff,lp);
      }
 /*     Rprintf("%f sum \n",sum); */
    return(R_pow(sum,(1/lp)));
  }
  else if(ISNA(lp)||ISNAN(lp)){
    error("lp is NA or NAN");
  }
  else{
    max=0.0;
    while (d--) 
      {
	diff = fabs(*a++ - *b++);
	if(max<=diff) max=diff;
      }
    return(max);    
  }
  return(R_PosInf);
}

static unf_mst_result *
calc_mst_dist (struct unf_mem *mem, edges *Elist,
	       const double *p, int n, int d, double *dist) 
{
/*    struct pq *pq; */
  unf_mst_result *mst;
  int i, k;
  UFob uf;

  assert (mem != NULL && p != NULL && n > 0 && d > 0);

  mst = mem->unf_alloc (sizeof *mst * (n - 1));
  if (mst == NULL) 
    {
      mem->unf_free (mst);
      return NULL;
    }

  for(i=0;i<Elist->nE;i++){
    Elist->wt[i]=calc_lp_dist (p + d * (Elist->from[i]-1), 
			       p + d * (Elist->to[i]-1), 2.0, d);
  }

  rsort_with_index (Elist->wt,Elist->pind,Elist->nE);
  uf=UFinit(n);

  for(i=0,k=0;i<Elist->nE && k < n-1; i++){
    if(!UFfind(uf,(Elist->from[Elist->pind[i]]-1),
	      (Elist->to[Elist->pind[i]]-1))){
      UFunion(uf,(Elist->from[Elist->pind[i]]-1),
	      (Elist->to[Elist->pind[i]]-1));
      mst[k][0] = Elist->from[Elist->pind[i]];
      mst[k][1] = Elist->to[Elist->pind[i]];
      dist[k] = Elist->wt[i];
      k++;
    }
  }
  return mst;
}
static unf_mst_result *
calc_mst_krusk_sort (struct unf_mem *mem, edges *Elist, const double *p, int n,
		     int d, double *dist)
{
  return calc_mst_dist (mem, Elist, p, n, d, dist);
}

struct unf_mst_krusk unf_mst_krusk_sort = 
  { 
    calc_mst_krusk_sort, 
  };

/* Kruskal's Algorithm MST with binary heap priority queue. */
/*  static unf_mst_result * */
/*  calc_mst_krusk_bin_heap (struct unf_mem *mem, const double *p, int n, */
/*  			int d, double *dist) */
/*  { */
/*    extern struct pq_class unf_pq_bin_heap; */

/*    return calc_mst (&unf_pq_bin_heap, mem, p, n, d, dist); */
/*  } */

/*  struct unf_mst unf_mst_krusk_binary =  */
/*    {  */
/*      calc_mst_krusk_bin_heap,  */
/*    }; */

/*  static unf_mst_result * */
/*  calc_mst_krusk_dist_bin_heap (struct unf_mem *mem, const double *p, int n, */
/*  			int d, double *dist) */
/*  { */
/*    extern struct pq_class unf_pq_bin_heap; */

/*    return calc_mst_dist (&unf_pq_bin_heap, mem, p, n, d, dist); */
/*  } */

/*  struct unf_mst unf_mst_krusk_binary =  */
/*    {  */
/*      calc_mst_krusk_dist_bin_heap,  */
/*    }; */

