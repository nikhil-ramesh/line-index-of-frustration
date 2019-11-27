#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "utility.h"
#include "load_data.h"
#include "store_data.h"


struct edge
{
	int start_node;
	int end_node;
	int sign;          //+1 for '+' and -1 for '-'
};
typedef struct edge edge;

void *adj_mat_to_edge_list(void *inp_adj_mat, int num_nodes, int *num_edges)
{
	int **adj_mat = (int **)inp_adj_mat;
	edge *edge_list = (edge *)calloc(num_nodes*num_nodes,sizeof(edge));
	for(int i=0; i<num_nodes; i++){
		for(int j=0; j<num_nodes; j++){
			if(adj_mat[i][j] != 0){
				edge_list[*num_edges].start_node = i;
				edge_list[*num_edges].end_node = j;
				edge_list[*num_edges].sign = adj_mat[i][j];
				*num_edges+=1;
			}
		}
	}
	return (void *)edge_list;
}


void *edge_list_to_adj_mat(void *inp_edge_list, int num_edges, int num_nodes)
{
	int **adj_mat = (int **)calloc(num_nodes,sizeof(int *));
	edge *edge_list = (edge *)inp_edge_list;
	for(int i=0; i<num_nodes; i++){
		adj_mat[i] = (int *)calloc(num_nodes,sizeof(int));
	}

	for(int i=0; i<num_edges; i++){
		edge e = edge_list[i];
		adj_mat[e.start_node][e.end_node] = e.sign;
	}
	return (void *)adj_mat;
}


edge make_edge(int node_one, int node_two, int **adj_mat)
{
	edge e;
	e.start_node = node_one;
	e.end_node = node_two;
	e.sign = adj_mat[node_one][node_two];
	return e;
}



int get_num_f_edges(int *partition, int num_nodes, edge *edge_list, int num_edges)
{
	int num_f_edges = 0;
	for(int i=0; i<num_edges; i++){
		edge e = edge_list[i];
		if(partition[e.start_node] != partition[e.end_node] && e.sign > 0)
			num_f_edges += 1;
		else if(partition[e.start_node] == partition[e.end_node] && e.sign < 0)
			num_f_edges += 1;
	}
	return num_f_edges;
}

int get_f_idx(int *opt_partition, void *inp_edge_list, int num_nodes, int num_edges)
{
	int num_iters = (int)pow(2,num_nodes);
	edge *edge_list = (edge *)inp_edge_list;
	int f_idx = num_edges;
	for(int i=0; i<num_iters; i++){
		int *partition = (int *)calloc(num_nodes,sizeof(int));
		get_ba(partition,num_nodes,i);
		int num_f_edges = get_num_f_edges(partition,num_nodes,edge_list,num_edges);
		if(f_idx > num_f_edges){
			f_idx = num_f_edges;
			for(int j=0; j<num_nodes; j++){
				opt_partition[j] = partition[j];
			}
		}
		free(partition);
	}
	return f_idx;
}

void print_adj_mat(int **w_mat,int num_nodes)
{
	printf("Adjacency Matrix\n");
	for(int i=0; i<num_nodes; i++){
		for(int j=0; j<num_nodes; j++){
			printf("%d ",w_mat[i][j]);
		}
		printf("\n");
	}
}

int main()
{
	int num_nodes = 10;
	int **w_mat = load_2d_arr("sample_w_mat.bin",num_nodes);
	print_adj_mat(w_mat,num_nodes);
	int num_edges = 0;
	void *edge_list = adj_mat_to_edge_list((void *)w_mat,num_nodes,&num_edges);
	int *opt_partition = (int *)calloc(num_nodes,sizeof(int));
	int f_idx = get_f_idx(opt_partition,edge_list,num_nodes,num_edges);
	printf("The line index of frustration of the input graph is %d\n",f_idx);
}



