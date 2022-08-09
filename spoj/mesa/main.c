#include <stdio.h>
#include <stdlib.h>

// graph representation:
// https://www.ime.usp.br/~pf/algoritmos_para_grafos/aulas/graphdatastructs.html

#define vertex int

typedef struct graph {
   int V; 
   int A; 
   int **adj; 
} *Graph;

static int **MATRIXint( int, int, int);

Graph GRAPHinit( int V) { 
   Graph G = malloc( sizeof *G);
   G->V = V; 
   G->A = 0;
   G->adj = MATRIXint( V, V, 0);
   return G;
}

static int **MATRIXint( int r, int c, int val) { 
   int **m = malloc( r * sizeof (int *));
   for (vertex i = 0; i < r; ++i) 
      m[i] = malloc( c * sizeof (int));
   for (vertex i = 0; i < r; ++i)
      for (vertex j = 0; j < c; ++j)
         m[i][j] = val;
   return m;
}

void GRAPHinsertArc( Graph G, vertex v, vertex w) { 
   if (G->adj[v][w] == 0) {
      G->adj[v][w] = 1; 
      G->A++;
   }
}

void GRAPHremoveArc( Graph G, vertex v, vertex w) { 
   if (G->adj[v][w] == 1) {
      G->adj[v][w] = 0; 
      G->A--;
   }
}

void GRAPHshow( Graph G) { 
   for (vertex v = 0; v < G->V; ++v) {
      printf( "%2d:", v);
      for (vertex w = 0; w < G->V; ++w)
         if (G->adj[v][w] == 1) 
            printf( " %2d", w);
      printf( "\n");
   }
}


int main(int argc, char const *argv[])
{
    int n, m, i;
    Graph g;

    scanf("%d %d", &n, &m);

    g = GRAPHinit(n);

    for(i=0; i<m; i++){
        int u, v;
        scanf("%d %d", &u, &v);
        GRAPHinsertArc(g, --u, --v);
    }

    GRAPHshow(g);

    return 0;
}