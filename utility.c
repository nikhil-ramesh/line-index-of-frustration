#include <math.h>
#include <stdio.h>

void get_ba(int *ba, int sz, int n)
{
	int pow_2_N = (int)pow(2,sz); 
	int pow_2_i = pow_2_N;
	for(int i=sz-1; i>=0; i--){
		pow_2_i = pow_2_i/2;
		if(pow_2_i > n)
			ba[i] = 0;
		else{
			ba[i] = 1;
			n = n - pow_2_i;
		}
	}
}

int get_int(int *ba, int sz)
{
	int val = 0;
	for(int i=0; i<sz; i++){
		val += ba[i]*(int)(pow(2,i));
	}
	return val;
}

int get_num_ones(int *ba, int sz)
{
	int num_ones = 0;
	for(int i=0; i<sz; i++){
		if(ba[i] == 1)
			num_ones++;
	}
	return num_ones;
}

/*
int main()
{
	int ba[4] = {1,0,1,0};
	printf("%d\n",get_num_ones(ba,3));
}
*/
