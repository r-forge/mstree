#include "tree.h"

/* Basic Tree Functions */

Edge * edge(int u,int v, int eid, double wt){
  Edge *e;
  e = (Edge *) malloc(sizeof(e));
  e->u=u;
  e->v=v;
  e->eid=eid;
  e->wt=wt;
  return e;
}

link vert(int v, double wt, link next){
  link u =  malloc(sizeof *u);
  u->v=v;
  u->wt=wt;
  u->next = next;
  return u;
}

Graph graph_init(int V){
  int j;
  Graph G;
  G = malloc(sizeof *G);
  G->V = V;
  G->E = 0;
  G->maxWT=0.0;
  G->sumWT=0.0;
  G->adj = malloc(V*sizeof(link));
  G->degree = malloc(V*sizeof(int));  
  for(j=0;j<V;j++){
    G->adj[j] = NULL;
    G->degree[j]=0;
  }
  G->root=-1;
  return G;
}

void graph_insertE(Edge e, Graph G){
  int u = e.u, v = e.v;
  double wt=e.wt;

  if(wt > G->maxWT) G->maxWT=wt;
  G->sumWT += wt;
  if(u==v) return;
  G->adj[u] = vert(v,wt,G->adj[u]);
  G->degree[u]++;
  G->adj[v] = vert(u,wt,G->adj[v]);
  G->degree[v]++;
  G->E++;
}

void graph_insertE2(int u, int v, double wt, Graph G){
  if(wt > G->maxWT) G->maxWT=wt;
  G->sumWT += wt;
  if(u==v) return;
  G->adj[u] = vert(v,wt,G->adj[u]);
  G->degree[u]++;
  G->adj[v] = vert(u,wt,G->adj[v]);
  G->degree[v]++;
  G->E++;
}

void graph_insertE3(int u, int v, double wt, Graph G){
  if(wt > G->maxWT) G->maxWT=wt;
  G->sumWT += wt;
  if(u==v) return;
  G->adj[v] = vert(u,wt,G->adj[v]);
  G->degree[v]++;
  G->degree[u]++;
  G->E++;
}
/* void graph_insertE_id(int u, int v, Tree T){ */
/*   T->adj[u] = vert(v,T->adj[u]); */
/*   T->adj[v] = vert(u,T->adj[v]); */
/*   T->E++; */
/* } */


void graph_free(Graph G){
  int v;
  link t;
  for(v=0; v<G->V; v++){
    for(t=G->adj[v]; t!=NULL; t=t->next){
      free(t);
    }
  }
  free(G->adj);
  free(G->degree);  
  free(G);
}



vdist  * nodew_el(int id, double wt){
  vdist *vd = (vdist *)malloc(sizeof(vdist));
  vd->id=id;
  vd->wt= wt; 
  return vd;
}



void Graph_dijkstra_pq(struct pq_class *pq_class, struct unf_mem *mem, 
          Graph G, int source, int *far, int *st, double *wt){
  int v, w;
  double lng_dist=0;
  link t;
  struct pq *pq;
  
  assert (pq_class != NULL && mem != NULL);
  pq = pq_class->create (mem, G->V);
  for (v = 0; v < G->V; v++) {
    st[v] = -1;
    wt[v] = DBL_MAX;
  }
 wt[source] = 0.0;
 pq_class->decrease_key (pq,source, 0);
 while (pq_class->count (pq) > 0){
    v = pq_class->extract_min (pq);
    if (wt[v] != DBL_MAX){
      for (t = G->adj[v]; t != NULL; t = t->next){
	w = t->v;
        if ((wt[v] + t->wt) < wt[w]){
          wt[w] = wt[v] + t->wt;
	  pq_class->decrease_key (pq, w, wt[w]);
          st[w] = v;
        }
      }
    }
  }
  /* Clean up */
 pq_class->discard (pq);
 for (v = 0; v < G->V; v++) { 
   if(lng_dist < wt[v]){
     lng_dist = wt[v];
     *far = v;
   }
 }

}


void 
calc_dijk_fib_heap (struct unf_mem *mem, Graph G, int source, int *far, 
		    int *st, double *wt )
{
  extern struct pq_class unf_pq_fib_heap;
  return Graph_dijkstra_pq(&unf_pq_fib_heap, mem,G,source,far,st,wt);
}


struct unf_dijk unf_dijk_fibonacci =
  {
    calc_dijk_fib_heap,
  };


/* Tree algorithms and structures */

tlink tvert(int v){
  tlink t;
  t=(tlink) malloc(sizeof *t);
  t->v=v;
  t->depth=-1;
  t->Child=NULL;
  t->Rsib=NULL;
  t->Parent=NULL;
  return(t);
}

Tree tree_init(int V){
  Tree T;
  T = (Tree) malloc(sizeof *T);
  T->vert_array = malloc(V*sizeof(tlink));
  T->V=V;
  T->leaves = 0;
  T->root=NULL;
}

/* void dfsR(Graph G, Edge e, int *pre, Tree T, tlink t) */
/*   { link t; */
/*   tlink tt;  */
/*     int w = e.w; */
/*     pre[w] = cnt++; */
/*     for (t = G->adj[w]; t != NULL; t = t->next) */
/*       if (pre[t->v] == -1){ */
/* 	tt=tvert( */
/*       } */
/*       dfsR(G, EDGE(w, t->v), pre, T); */
/*   } */


Tree tree_init_plink(int *plink, double *weight, int n){
  int i, j;
  Tree T;
  Graph G;
  tlink  t; 

  T=tree_init(n);
  /* Pass 1 set up vert array */
  for(i=0; i<n; i++){
    T->vert_array[i]=tvert(i);
  }
  /* Pass 2 use the vert array and the parent info to set parents and children */
  for(i=0; i<n; i++){
    if(plink[i]>=0){
      T->vert_array[i]->Parent=T->vert_array[plink[i]];
      for(t=T->vert_array[plink[i]]->Child; t->Sib_Next !=NULL; t=t->Sib_Next)
	if(t=t->Sib_Next==NULL) t->Sib_Next = T->vert_array[i];
    }
    else {
      T->root=T->vert_array[i];
    }  

  }
 
  return(T);    
}

tlink root(Tree T){
  return(T->root);
}

/* int isLeaf(int v, Tree T){ */
/*   tlink t; */
  
/*   if(T->==1) return 1; */
/*   return 0; */
/* } */



/* void diamorder(Tree T, int pode, int antipode, int *st, double *wt,  */
/* 	       double *Elen, int *lorder){ */
/*   int i, depth; */
/*   link R, H, S; */
  
/*   R=root(pode); */
/*   lorder[0]=pode; */
/*   i = 1; */
/*   while(i<T->V){ */
/*     H=R; */
/*     R=T->adj[R->v]; */
/*     if(T->deg[H->v]==2){ */
/*       lorder[i]=H->v; */
/*       i++; */
/*     } */
/*     else{ */
      
/*     } */
/*   } */
/*   return;   */
/* } */

/* void radorder(){ */


/* } */
