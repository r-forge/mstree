#define P (wt[v] + t->wt)
void GRAPHpfs(Tree T, int s, int *st, double *wt){
  int v, w;
  link t;
  struct fibheap *pq;

  pq = fh_makeheap();
  fh_setcmp(pq, wt_cmp);
  /* PQinit(); */
  /* priority = wt; */
  for (v = 0; v < G->V; v++) {
    st[v] = -1; 
    wt[v] = Inf;
    PQinsert(v);
  }
  wt[s] = 0.0;
  PQdec(s);
  while (!PQempty())
    if (wt[v = PQdelmin()] != maxWT)
      for (t = G->adj[v]; t != NULL; t = t->next)
	if (P < wt[w = t->v]){
	  wt[w] = P; 
	  PQdec(w); 
	  st[w] = v;
	}
}

#define GRAPHpfs GRAPHmst
static int fr[maxV];
static double *priority;
int less(int i, int j)
  { return priority[i] < priority[j]; }
#define P (wt[v] + t->wt)
void GRAPHpfs(Graph G, int st[], double wt[])  { 
  link t; 
  int v, w;
  PQinit(); 
  priority = wt;
  for (v = 0; v < G->V; v++){ 
      st[v] = -1; 
      fr[v] = -1; 
  }
  fr[0] = 0;
  PQinsert(0);
  while (!PQempty())
    {
      v = PQdelmin(); st[v] = fr[v];
      for (t = G->adj[v]; t != NULL; t = t->next)
	if (fr[w = t->v] == -1){
	   wt[w] = P;
	   PQinsert(w); 
	   fr[w] = v;
	}
	else if ((st[w] == -1) && (P < wt[w])){
	  wt[w] = P; 
	  PQdec(w); 
	  fr[w] = v; 
	}
    }
}
