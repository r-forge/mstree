#include <assert.h>
#include <stdio.h>
#include <math.h>
#include "pq.h"
#include "spantree.h"
#include "R.h"
#include "Rmath.h"

/* #include "fib-1.1/fib.h" */

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


typedef struct tnode *tlink;

struct tnode {
  int v;
  int depth;
  double wt;
  tlink Child;
  tlink Sib_Next;
  tlink Parent;
};

typedef struct tree *Tree;

struct tree{
  int V;
  int leaves;
  tlink root;
  tlink *vert_array;
};

typedef struct graph *Graph;

struct graph{
  int V;
  int E;
  int root;
  double maxWT;
  double sumWT;
  link *adj;
  int *degree;
};


typedef struct {
  int id;
  double wt;
}vdist;

typedef struct {
  int V;
  tlink head;
  tlink tail;
}tdiameter;

extern struct unf_dijk unf_dijk_fibonacci;

struct unf_dijk
  {
    void (*unf_run) (struct unf_mem *, Graph, int, int *, int *, double *);
  };


/* Graph Functions */
Edge * edge(int,int,int, double);
link vert(int,double,link);
Graph graph_init(int);
void graph_insertE(Edge, Graph);
void graph_insertE2(int u, int v, double wt, Graph G);
void graph_insertE3(int u, int v, double wt, Graph G);
void graph_free(Graph);
vdist * nodew_el(int, double);
void Graph_dijkstra_pq(struct pq_class *, struct unf_mem *, 
                      Graph, int, int *, int *, double *);

/* Tree Functions */

Tree tree_init(void);
Tree tree_init_plink(int *plink, double *weight, int n);
void insert_Tedge(Tree, int, int);
void insert_Tnode(Tree, int, int);
Tree reroot_Tree(int , Tree);
int * traverse(Tree);
tlink root(Tree);
int isLeaf(int, Tree);

