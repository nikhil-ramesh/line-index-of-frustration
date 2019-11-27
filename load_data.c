#include <stdio.h>
#include <stdlib.h>

int *load_1d_arr(char *fname,int sz)
{
	int *arr = (int *)calloc(sz,sizeof(int));
	FILE *fp = fopen(fname,"rb");
	if(fp == NULL){
		printf("File not found.\n");
		exit(0);
	}
	fread(arr,sizeof(int),sz,fp);
	fclose(fp);
	return arr;
}

int **load_2d_arr(char *fname,int sz)
{
	int **arr = (int **)calloc(sz,sizeof(int *));
	FILE *fp = fopen(fname,"rb");
	if(fp == NULL){
		printf("File not found.\n");
		exit(0);
	}
	for(int i=0; i<sz; i++){
		arr[i] = (int *)calloc(sz,sizeof(int));
		fread(arr[i],sizeof(int),sz,fp);
	}
	fclose(fp);
	return arr;
}

int ***load_2d_arr_pack(char *fname,int sz,int pack_sz)
{
	int ***arr_pack = (int ***)calloc(pack_sz,sizeof(int **));
	FILE *fp = fopen(fname,"rb");
	if(fp == NULL){
		printf("File not found.\n");
		exit(0);
	}
	for(int i=0; i<pack_sz; i++){
		arr_pack[i] = (int **)calloc(sz,sizeof(int *));
		for(int j=0; j<sz; j++){
			arr_pack[i][j] = (int *)calloc(sz,sizeof(int));
			fread(arr_pack[i][j],sizeof(int),sz,fp);
		}
	}
	fclose(fp);
	return arr_pack;
}
