#include <stdlib.h>
#include "R.h"
#include "sets.h"

UFob UFinit(int N)
  { 
    int i;
    UFob uf;
   
    uf=(UFob) R_alloc(1, sizeof(UFob));
    uf->id = (int *) R_alloc(N,sizeof(int)); 
    uf->sz = (int *) R_alloc(N,sizeof(int)); 
    for (i = 0; i < N; i++) 
      { uf->id[i] = i; uf->sz[i] = 1; }
    return(uf);
  }
static int find(UFob uf,int x)
  { 
    int i = x; 
    while (i != uf->id[i]) i = uf->id[i]; 
    return i; 
  }

int UFfind(UFob uf, int p, int q)
  { return (find(uf,p) == find(uf,q)); }

void UFunion(UFob uf, int p, int q)
  { int i = find(uf,p), j = find(uf,q);
    if (i == j) return;
    if (uf->sz[i] < uf->sz[j]){ 
      uf->id[i] = j; 
      uf->sz[j] += uf->sz[i]; 
    }
    else { 
      uf->id[j] = i; 
      uf->sz[i] += uf->sz[j]; 
    }
    return;
  }
