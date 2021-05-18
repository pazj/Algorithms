

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>




#define HEAP_LEFT(nodo) ((nodo)+(nodo)+1)
#define HEAP_RIGHT(nodo) ((nodo)+(nodo)+2)
#define HEAP_PARENT(nodo) (((nodo)-1)>>1)

struct node;


typedef struct
{
	unsigned int source;
	unsigned int destination;
	double weight;
} edge;




typedef struct node
{
	edge* edges;
	unsigned int edge_count;
	unsigned int edge_space;
	int value;

	
	int distance;
	
	int heap_index;
	
	int previous;
} node;



typedef struct
{
	node* nodes;
	unsigned int node_count;
	unsigned int node_space;
} graph;

typedef int ( heap_compare )(graph*, unsigned int, unsigned int);
typedef struct
{
	unsigned int* nodes;
	unsigned int space;
	unsigned int count;
	heap_compare* compare;
	graph* g; 
} heap;

void heap_insert(heap*, const unsigned int );
heap* heap_make(heap_compare* cmp, graph* g)
{
	unsigned int i;
	heap* h = (heap*)malloc(sizeof(heap));
	h->nodes = (unsigned int*)malloc(sizeof(node) * ( g->node_count ) * 2);
	h->compare = cmp;
	h->space = g->node_count * 2; /* allocated */
	h->count = 0; /* used */
	h->g = g;
	for ( i = 0; i < g->node_count; i++ )
	{
		heap_insert(h, i);
	}
	return h;
}

bool heap_is_full(const heap* h)
{
	return h->count == h->space;
}

void heap_enlarge(heap* h)
{
	if ( h->space )
	{
		h->space *= 2;
	}
	else
	{
		h->space = 1;
	}
	h->nodes = (unsigned int*)realloc(h->nodes, sizeof(unsigned int) * ( h->space ));
}

void heap_heapify_up(heap* h, unsigned int key)
{
	unsigned int value = h->nodes[key],
		temp;
	while ( key != 0 && ( *h->compare )( h->g, value, h->nodes[HEAP_PARENT(key)] ) < 0 )
	{
		temp = h->nodes[HEAP_PARENT(key)];
		h->nodes[HEAP_PARENT(key)] = value;
		h->g->nodes[temp].heap_index = key;

		h->nodes[key] = temp;
		h->g->nodes[value].heap_index = HEAP_PARENT(key);
		key = HEAP_PARENT(key);
		value = h->nodes[key];

	}
}

void heap_heapify_down(heap* h)
{
	unsigned int pos = 0,
		newpos,
		temp;
	node** graph_nodes;

	graph_nodes = &h->g->nodes;

	while ( 1 )
	{
		if ( HEAP_LEFT(pos) <= h->count )
		{
			if ( HEAP_RIGHT(pos) <= h->count )
			{
				newpos = ( *h->compare )( h->g, h->nodes[HEAP_RIGHT(pos)], h->nodes[HEAP_LEFT(pos)] ) < 0 ? HEAP_RIGHT(pos) : HEAP_LEFT(pos);
			}
			else
			{
				newpos = HEAP_LEFT(pos);
			}
		}
		else
		{
			break; /* es una hoja, nada que hacer */
		}

		if ( ( *h->compare )( h->g, h->nodes[pos], h->nodes[newpos] ) > 0 )
		{
			temp = h->nodes[pos];
			( *graph_nodes )[temp].heap_index = newpos;
			( *graph_nodes )[h->nodes[newpos]].heap_index = pos;
			h->nodes[pos] = h->nodes[newpos];
			h->nodes[newpos] = temp;
		}
		else
		{
			break; /* la posicion es correcta */
		}
	}
}

void heap_insert(heap* h, const unsigned int key)
{
	if ( heap_is_full(h) )
	{
		heap_enlarge(h);
	}
	h->nodes[h->count] = key;
	h->g->nodes[key].heap_index = h->count;
	h->count++;
	heap_heapify_up(h, h->count - 1);
}

unsigned int heap_find_min(const heap* h)
{
	return h->nodes[0];
}

bool heap_is_empty(const heap* h);

unsigned int heap_delete_min(heap* h)
{
	unsigned int retval = h->nodes[0];

	h->nodes[0] = h->nodes[h->count - 1];
	h->count--;
	if ( heap_is_empty(h) )
	{
		free(h->nodes);
	}
	else
	{
		heap_heapify_down(h);
	}
	return retval;
}


void heap_destroy(heap* h)
{
	if ( !heap_is_empty(h) )
	{
		free(h->nodes);
	}
	free(h);
}

bool heap_is_empty(const heap* h)
{
	return h->count == 0;
}


graph* graph_make()
{
	graph* g = (graph*)malloc(sizeof(graph));
	g->node_space = 0;
	g->node_count = 0;
	g->nodes = NULL;
	return g;
}

/*
El grafo está lleno cuando está usando todo el espacio que se reservó
para él. Se puede pedir más.
*/
bool graph_is_full(graph* g)
{
	return g->node_space == g->node_count;
}


/*
Doblamos la cantidad de memoria usada, o reservamos un lugar si el grafo
está vacío.
*/
void graph_enlarge(graph* g)
{
	if ( g->node_space == 0 )
	{
		g->node_space = 1;
	}
	else
	{
		g->node_space *= 2;
	}
	g->nodes = (node*)realloc(g->nodes, sizeof(node) * ( g->node_space ));
}

void graph_add_node(graph* g, int vertex)
{
	unsigned int count;
	node *n;

	if ( graph_is_full(g) )
	{
		graph_enlarge(g);
	}

	count = g->node_count;
	n = &g->nodes[count];
	n->value = vertex;
	n->edges = NULL;
	n->edge_count = 0;
	n->edge_space = 0;
	n->distance = (int)INFINITY;
	n->heap_index = -1;
	n->previous = -1;
	g->node_count++;
}


void graph_add_edge(graph* g, unsigned int i, unsigned int j, double weight)
{
	edge *e;
	node *n;

	n = &g->nodes[i];
	if ( n->edge_space == n->edge_count )
	{
		if ( n->edge_space == 0 )
		{
			n->edge_space = 1;
		}
		else
		{
			n->edge_space *= 2;
		}
		n->edges = (edge*) realloc(n->edges, sizeof(edge) * ( n->edge_space ));
	}
	e = &n->edges[n->edge_count];
	e->source = i;
	e->destination = j;
	e->weight = weight;
	g->nodes[i].edge_count++;
}



double* distances;

int compare(graph* g, unsigned int i, unsigned int j)
{
	if ( g->nodes[i].distance == g->nodes[j].distance )
	{
		return 0;
	}
	if ( g->nodes[i].distance > g->nodes[j].distance )
	{
		return 1;
	}
	return -1;
}
void print(graph* g, int n)
{
	int sup_max = 0; 
	for ( int i = 1; i < n-1; i++)
	{	
		sup_max = g->nodes[i].distance;
		if(sup_max < g->nodes[i+1].distance) sup_max = g->nodes[i+1].distance;	
	}
	printf("%d\n", sup_max);
}
void dijkstra(graph* g, unsigned int source, int size)
{
	unsigned int u, v, edge_count;
	node *n, *d;
	edge *e;
	heap *Q;

	g->nodes[source].distance = 0;
	Q = heap_make(compare, g);

	while ( !heap_is_empty(Q) )
	{
		u = heap_delete_min(Q);
		//printf("%d - ", u);
		n = &g->nodes[u];
		edge_count = n->edge_count;
		for ( v = 0; v < edge_count; v++ )
		{
			e = &n->edges[v];
			d = &g->nodes[e->destination];
			if ( d->distance > n->distance + e->weight )
			{
				/*
				Relajo los vertices
				*/
				d->distance = n->distance + e->weight;
				/*
				Actualizo el nodo con la distancia optima a este
				*/
				d->previous = u;
				/*
				Actualizo la cola de prioridad (el vertice solo puede
				haber subido en prioridad, entonces solo hago heapify-up
				*/
				heap_heapify_up(Q, d->heap_index);
			}
		}
	}
	print(g, size);
	heap_destroy(Q);
}

int main()
{
	int N, edges_num, src, dest, weight;
	if ( scanf("%d", &N) > 1 ) return 0;
	//if ( ( N < 1 ) || N > 5000 ) return 0;
	
	graph* g;
	g = graph_make();
	
	for ( int i = 0; i < N; i++ )
	{		
		graph_add_node(g, i + 1);
	}

	
	while ( scanf("%d %d", &src, &edges_num) != EOF )
	{
		for(int i = 0; i < edges_num; i++){
			if ( scanf("%d %d", &dest, &weight) > 2 ) return 0;
			graph_add_edge(g, src-1, dest-1, weight);		
		}
				
	}
	dijkstra(g, 0, N);
	return 0;
}
