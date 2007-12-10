#include <stdlib.h>
#include <R.h>
#include "fib-1.1/fib.h"

typedef struct{
  int u, v, eid;
  double wt;
}Edge;

typedef struct node *link;

struct node {
  int v;
  double wt;
  link next;
};

typedef struct tree *Tree;

struct tree{
  int V;
  int E;
  double maxWT;
  double sumWT;
  link *adj;
  int *degree;
  link root;
};


typedef struct {
  int id;
  double wt;
}vdist;

/* typedef struct fibheap_el *fibElPnt; */

Edge * edge(int,int,int, double);
link vert(int,double,link);
Tree graph_init(int);
void graph_insertE(Edge, Tree);
void graph_insertE2(int u, int v, double wt, Tree T);
void graph_free(Tree);
vdist * nodew_el(int, double);
int wt_cmp(void *, void *);
void Tree_dijkstra(Tree, int, int *, double *);
