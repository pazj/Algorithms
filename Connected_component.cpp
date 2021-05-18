//2017053772_Paz_Carolina_Jimenez_Saucedo



#include <stdio.h>
#include <stdlib.h>

#define TRUE		1
#define FALSE		0




int numV;
int * list;
int * Qlist;
int * rep;

typedef struct _vertex;

typedef struct _vertex
{
	int groupname;
	int value;
	int rank;
	struct _vertex * parent;
} Vertex;


Vertex * vertex;


void MAKE_SET(Vertex * x, int value)
{
	x->value = value;
	x->parent = x;
	x->rank = 0;
}

Vertex * FIND_SET(Vertex * x)
{
	if(x != x->parent)
		x->parent = FIND_SET(x->parent);
	return x->parent;
}

void LINK(Vertex * x, Vertex * y)
{
	if(x->rank > y->rank){
		y->parent = x;			
	}
	else{
		x->parent = y;
		if(x->rank == y->rank){
			y->rank = y->rank + 1;
		}
	}
}

void UNION(Vertex * x, Vertex * y)
{
	LINK(FIND_SET(x), FIND_SET(y));
}

int SAME_COMPONENT(Vertex * x, Vertex * y)
{
	if(FIND_SET(x) == FIND_SET(y))
		return TRUE;
	else
		return FALSE;
}


int main(void)
{
	int * tmp_list;
	int v1, v2;
	int i=0, j=0, tmp=0;
	int order = 0;
	int compNUM = 0;

	scanf("%d", &numV);
	vertex = (Vertex*)malloc(sizeof(Vertex)*(numV+1));
	list = (int*)malloc(sizeof(int)*(numV+1));
	tmp_list = (int*)malloc(sizeof(int)*(numV+1));
	
	for(i=1; i<=numV; i++)
		MAKE_SET(&vertex[i], i);

	while(scanf("%d %d", &v1, &v2) != EOF){	
		if(FIND_SET(&vertex[v1]) != FIND_SET(&vertex[v2])){
			UNION(&vertex[v1], &vertex[v2]);
		}
	}
	for(i=1; i<=numV; i++){
		list[i] = FIND_SET(&vertex[i])->value;
		tmp_list[i] = FIND_SET(&vertex[i])->value;
	}

	for(i=1; i<=numV; i++)
	{
		tmp = list[i];
		if(tmp != 0)
		{
			compNUM ++;
			for(j=i+1; j<=numV; j++){
				if(tmp == list[j])
					list[j] = 0;
			}
		}
	}
	Qlist = (int*)malloc(sizeof(int)*(compNUM+1));
	order = 1;
	for(i=1; i<=numV; i++){
		if(list[i] != 0){
			Qlist[order++] = list[i];
		}
	}
	for(i=1; i<=numV; i++){
		for(j=1; j<=numV; j++){
			if(tmp_list[i] == Qlist[j]){
				list[i] = j;
			}
		}
	}
	
	printf("%d\n", compNUM);
	for(i=1; i<=numV; i++)
		printf("%d\n", list[i]);

	return 0;
}




