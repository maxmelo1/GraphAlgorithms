#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// graph representation:
// https://www.ime.usp.br/~pf/algoritmos_para_grafos/aulas/graphdatastructs.html

// bipartite graph
// https://www.ime.usp.br/~pf/algoritmos_para_grafos/aulas/bipartite.html

#define vertex int
#define MAX_VERTEX 100

int color[MAX_VERTEX];

typedef struct graph {
   int V; 
   int A; 
   int **adj; 
} *Graph;

int **MATRIXint( int, int, int);
bool dfsRtwoColor( Graph, vertex, int);
bool UGRAPHtwoColor(Graph);

Graph GRAPHinit( int V) { 
   Graph G = malloc( sizeof *G);
   G->V = V; 
   G->A = 0;
   G->adj = MATRIXint( V, V, 0);
   return G;
}

int **MATRIXint( int r, int c, int val) { 
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
      G->adj[w][v] = 1;
      G->A++;
   }
}

void GRAPHremoveArc( Graph G, vertex v, vertex w) { 
   if (G->adj[v][w]) {
      G->adj[v][w] = 0; 
      G->A--;
   }
}

void GRAPHshow(Graph G) { 
   for (vertex v = 0; v < G->V; ++v){
      printf( "%2d:", v);
      for (vertex w = 0; w < G->V; ++w)
         if (G->adj[v][w] == 1) 
            printf( " %2d", w);
      printf( "\n");
   }
}

bool UGRAPHtwoColor(Graph G){
   for (vertex v = 0; v < G->V; ++v)
      color[v] = -1; // incolor
   for (vertex v = 0; v < G->V; ++v)
      if (color[v] == -1) // começa nova etapa
         if (dfsRtwoColor( G, v, 0) == false) 
            return false;
   return true;
}

bool dfsRtwoColor( Graph G, vertex v, int c){ 
   color[v] = c;
   for (int w = 0; w < G->V; w++) {
      
      if(! G->adj[v][w])
         continue;
      
      if (color[w] == -1) {
         if (! dfsRtwoColor( G, w, 1-c)) 
            return false;
      }
      else { // v-w é de avanço ou de retorno
         if (color[w] == c) // base da recursão
            return false;
      }
   }
   return true;
}


int main(int argc, char const *argv[])
{
   int n, m, i, ii=0;
   Graph g;

   while(scanf("%d %d", &n, &m)==2){
      g = GRAPHinit(MAX_VERTEX);

      if (n == 0 && m == 0) break;

      for(i=0; i<m; i++){
         int u, v;
         scanf("%d %d", &u, &v);
         GRAPHinsertArc(g, --u, --v);
      }

      //GRAPHshow(g);

      bool bip = UGRAPHtwoColor(g);
      
      printf("Instancia %d\n%s\n\n", ++ii, (bip? "sim": "nao"));
   }

    return 0;
}

