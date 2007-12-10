#include "graph.h"

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

Tree graph_init(int V){
  int j;
  Tree T;
  T = malloc(sizeof *T);
  T->V = V;
  T->E = 0;
  T->maxWT=0.0;
  T->sumWT=0.0;
  T->adj = malloc(V*sizeof(link));
  T->degree = malloc(V*sizeof(int));  
  for(j=0;j<V;j++){
    T->adj[j] = NULL;
    T->degree[j]=0;
  }
  T->root=NULL;
  return T;
}

void graph_insertE(Edge e, Tree T){
  int u = e.u, v = e.v;
  double wt=e.wt;

  if(wt > T->maxWT) T->maxWT=wt;
  T->sumWT += wt;
  if(u==v) return;
  T->adj[u] = vert(v,wt,T->adj[u]);
  T->degree[u]++;
  T->adj[v] = vert(u,wt,T->adj[v]);
  T->degree[v]++;
  T->E++;
}

void graph_insertE2(int u, int v, double wt, Tree T){
  if(wt > T->maxWT) T->maxWT=wt;
  T->sumWT += wt;
  if(u==v) return;
  T->adj[u] = vert(v,wt,T->adj[u]);
  T->degree[u]++;
  T->adj[v] = vert(u,wt,T->adj[v]);
  T->degree[v]++;
  T->E++;
}
/* void graph_insertE_id(int u, int v, Tree T){ */
/*   T->adj[u] = vert(v,T->adj[u]); */
/*   T->adj[v] = vert(u,T->adj[v]); */
/*   T->E++; */
/* } */


void graph_free(Tree T){
  int v;
  link t;
  for(v=0; v<T->V; v++){
    for(t=T->adj[v]; t!=NULL; t=t->next){
      free(t);
    }
  }
  free(T->adj);
  free(T->degree);  
  free(T);
}



vdist  * nodew_el(int id, double wt){
  vdist *vd = (vdist *)malloc(sizeof(vdist));
  vd->id=id;
  vd->wt= wt; 
  return vd;
}


int wt_cmp(void *x, void *y)
{
  vdist *a, *b;
  a = (vdist *)x;
  b = (vdist *)y;

  if (a->wt < b->wt)
    return -1;
  if (a->wt == b->wt)
    return 0;
  return 1;
}


void Tree_dijkstra(Tree T, int source, int *st, double *wt){
  int v, w;
  link t;
  vdist *vd_el;
  struct fibheap *pq;
  char * fep;
 
  pq = fh_makeheap();
  fh_setcmp(pq, wt_cmp);
  fep =(void *) malloc(T->V*sizeof(char));
  /* fibpnt=malloc(T->V*sizeof(struct fibheap *)); */
  vd_el=nodew_el(-1,-1.0);
/*   nd_wts=(struct vdist *) malloc(T->V*sizeof(struct *vdist)); */
/*   wt = (double *) R_alloc(T->V, sizeof(double)); */
/*   st = (int *) R_alloc(T->V, sizeof(int)); */
  
  pq = fh_makeheap();
  fh_setcmp(pq, wt_cmp);
  /* PQinit(); */
  /* priority = wt; */
  for (v = 0; v < T->V; v++) {
    st[v] = -1;
    if(v != source){
      wt[v] = T->sumWT;
    /* nd_wts[v] = nodew_el(v,T->sumWT); */
      fep[v] = fh_insert(pq, (void *)nodew_el(v,T->sumWT));
    }
    else{
      wt[v] = 0.0;
      fep[v]= fh_insert(pq, (void *)nodew_el(v,0.0));
    }
    /* PQinsert(v); */
  }

  while (fh_min(pq) != NULL){
    v = ((vdist *)fh_min(pq))->id;
    if (wt[v] != T->sumWT){
      for (t = T->adj[v]; t != NULL; t = t->next){
	w = t->v;
        if ((wt[v] + t->wt) < wt[w]){
          wt[w] = wt[v] + t->wt;
          vd_el->wt=wt[w];
          vd_el->id=w;
	  vd_el = (vdist *)fh_replacedata(pq,fep[w],(void *) vd_el);
        /* PQdec(w); */
          st[w] = v;
        }
      }
    }
  }
  /* Clean up */
 fh_deleteheap(pq); 
 free(fep);
 free(vd_el);
}



/* #define GRAPHpfs GRAPHmst */
/* static int fr[maxV]; */
/* static double *priority; */
/* int less(int i, int j) */
/*   { return priority[i] < priority[j]; } */
/* #define P (wt[v] + t->wt) */
/* void GRAPHpfs(Graph G, int st[], double wt[])  { */
/*   link t; */
/*   int v, w; */
/*   PQinit(); */
/*   priority = wt; */
/*   for (v = 0; v < G->V; v++){ */
/*       st[v] = -1; */
/*       fr[v] = -1; */
/*   } */
/*   fr[0] = 0; */
/*   PQinsert(0); */
/*   while (!PQempty()) */
/*     { */
/*       v = PQdelmin(); st[v] = fr[v]; */
/*       for (t = G->adj[v]; t != NULL; t = t->next) */
/*         if (fr[w = t->v] == -1){ */
/*            wt[w] = P; */
/*            PQinsert(w); */
/*            fr[w] = v; */
/*         } */
/*         else if ((st[w] == -1) && (P < wt[w])){ */
/*           wt[w] = P; */
/*           PQdec(w); */
/*           fr[w] = v; */
/*         } */
/*     } */
/* } */
