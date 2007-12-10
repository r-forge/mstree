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

#ifndef SPANTREE_H
#define SPANTREE_H

#include <stddef.h>

/* Elist class*/
typedef struct{
  int *to;
  int *from;
  int *pind;
  int nE;
  double *wt;
} edges;

/* Provided class implementations. */
extern struct unf_mem unf_mem_malloc;
extern struct unf_mst unf_mst_prim_binary;
extern struct unf_mst unf_mst_prim_fibonacci;
extern struct unf_mst unf_mst_prim_dist_fibonacci;
/*  extern struct unf_mst unf_mst_krusk_binary; */
/*  extern struct unf_mst unf_mst_krusk_fibonacci; */
/*  extern struct unf_mst unf_mst_krusk_dist_fibonacci; */
extern struct unf_mst_krusk unf_mst_krusk_sort;

typedef int unf_mst_result[2];

struct unf_mst 
  {
    unf_mst_result *(*unf_run) (struct unf_mem *, 
				const double *, int, int, int *, double *);
  };

struct unf_mst_krusk 
  {
    unf_mst_result *(*unf_run) (struct unf_mem *, edges *, 
				const double *, int, int, double *);
  };

/* Memory allocator class. */
struct unf_mem 
  {
    void *(*unf_alloc) (size_t);
    void (*unf_free) (void *);
  };



/* Low-level routines. */
int unf_run_mst (struct unf_mem *, struct unf_mst *, 
		 int *, int *, const double *, int, int, int *, double *);

int unf_run_mst_krusk (struct unf_mem *, struct unf_mst *, 
		 int *, int *, const double *, int, int, double *);

#endif /* spantree.h */
