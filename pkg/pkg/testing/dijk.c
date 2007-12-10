/* Produced by texiweb from report.w on 2001/04/27 at 01:37. */

/* Copyright (c) 2001 Ben Pfaff <pfaffben@msu.edu>.  All rights reserved.

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

/* Modified by Nicholas Lewin-Koh 2002 for use with R
Change log:
March 26, 2002 
     Added R_pow in calc_distance to make use of IEEE Inf and friends
     Added calc_mst_dist for use with arbitary distance matrices 
March 28, 2002
     Added calc_lp_dist so that the spanning tree can optionally be
     calculated for any Minkowski metric
*/

#include <assert.h>
#include <stdio.h>
#include <math.h>
#include "pq.h"
#include "spantree.h"
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

/* Calculates the MST of the |n| |d|-dimensional points at |p|.
   Uses |mem| for memory allocation
   and an instance of |pq_class| as a priority queue. */

static dijk_result *
calc_sp(struct pq_class *pq_class,
	struct unf_mem *mem, const double *p, int s, 
	int n, double *wt) 
{
  struct pq *pq;
  unf_mst_result *mst;
  int *edges;

  assert (pq_class != NULL && mem != NULL && p != NULL 
	  && n > 0 && d > 0);

  pq = pq_class->create (mem, n);
  mst = mem->unf_alloc (sizeof *mst * (n - 1));
  edges = mem->unf_alloc (sizeof *edges * n);
  if (pq == NULL || mst == NULL || edges == NULL) 
    {
      if (pq != NULL)
	pq_class->discard (pq);
      mem->unf_free (mst);
      mem->unf_free (edges);
      return NULL;
    }
  pq_class->decrease_key (pq, 0, 0);
  int v, w;
  for (v = 0; v < n; v++){
    st
  }
  while (pq_class->count (pq) > 0) 
    {
      int u, v;

      u = pq_class->extract_min (pq);
      for (v = 0; v < n; v++)
	if (u != v) 
	  {
	    double key = pq_class->key (pq, v);

	    if (key != -DBL_MAX) 
	      {
		double cost = calc_lp_dist (p + d * u, p + d * v, 2.0, d);
/*  		double cost = calc_distance (p + d * u, p + d * v, d); */
		if (cost < key) 
		  {
		    edges[v] = u;
/*  		    dist[v] = sqrt(cost); */
		    dist[v] = cost;
		    pq_class->decrease_key (pq, v, cost);
		  }
	      }
	  }
    }

  {
    int i;

    for (i = 1; i < n; i++) 
      {
	mst[i - 1][0] = i;
	mst[i - 1][1] = edges[i];
      }
  }
  pq_class->discard (pq);
  mem->unf_free (edges);

  return mst;
}

static dijk_result *
calc_sp (struct pq_class *pq_class,
	  struct unf_mem *mem, const double *p, int n, double *dist) 
{
  struct pq *pq;
  unf_mst_result *mst;
  int *edges;

  assert (pq_class != NULL && mem != NULL && p != NULL 
	  && n > 0 );

  pq = pq_class->create (mem, n);
  mst = mem->unf_alloc (sizeof *mst * (n - 1));
  edges = mem->unf_alloc (sizeof *edges * n);
  if (pq == NULL || mst == NULL || edges == NULL) 
    {
      if (pq != NULL)
	pq_class->discard (pq);
      mem->unf_free (mst);
      mem->unf_free (edges);
      return NULL;
    }

  pq_class->decrease_key (pq, 0, 0);
  while (pq_class->count (pq) > 0) 
    {
      int u, v;

      u = pq_class->extract_min (pq);
      for (v = 0; v < n; v++)
	if (u != v) 
	  {
	    double key = pq_class->key (pq, v);

	    if (key != -DBL_MAX) 
	      {
 		double cost = p[((v*n)+u)];
		if (cost < key) 
		  {
		    edges[v] = u;
		    dist[v] = cost;
		    pq_class->decrease_key (pq, v, cost);
		  }
	      }
	  }
    }

  {
    int i;

    for (i = 1; i < n; i++) 
      {
	mst[i - 1][0] = i;
	mst[i - 1][1] = edges[i];
      }
  }
  pq_class->discard (pq);
  mem->unf_free (edges);

  return mst;
}

/* Prim's Algorithm MST with binary heap priority queue. */
static dijk_result *
calc_dijk_bin_heap (struct unf_mem *mem, const double *p, int n,
			int d, double *dist)
{
  extern struct pq_class unf_pq_bin_heap;

  return calc_sp (&unf_pq_bin_heap, mem, p, n, d, dist);
}

struct dijk dijk_binary = 
  { 
    calc_dijk_bin_heap, 
  };






