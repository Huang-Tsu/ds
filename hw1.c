#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define ENCODE 0
#define DECODE 1
#define MAX_LEN 11

void Encode();
//void Decode();
int PowDIY(int x, int n);

int main(){
	int mode;

	scanf("%d", &mode);

	if(mode == ENCODE)
		Encode();
	//else
		//Decode();

	return 0;
}
void Encode(){
	int n, m;
	int i, j;
	char input_str[MAX_LEN];
	int str_len;
	int chunck_len;
	int sum;
	int cofficient;

	scanf("%d%d", &n, &m);
	scanf("%s", input_str);
	str_len = strlen(input_str);
	chunck_len = str_len/n;


	char n_str_chuncks[n][MAX_LEN];
	int n_num_chuncks[n];

	for(i=0; i<n; i++){
		for(j=0; j<chunck_len; j++){
			n_str_chuncks[i][j] = input_str[i*chunck_len+j]; 	
		}
		n_str_chuncks[i][j] = '\0';
		n_num_chuncks[i] = atoi(n_str_chuncks[i]);
	}

	for(i=0; i<n; i++){
		for(j=0; j<n; j++){
			if(i != j)
				printf("0 ");
			else
				printf("1 ");
		}
		printf("%d\n", n_num_chuncks[i]);
	}
	for(i=1; i<=m; i++){
		sum = 0;
		for(j=0; j<n; j++){
			cofficient = PowDIY(i, j);
			printf("%d ", cofficient); 			
			sum += cofficient*n_num_chuncks[j];
		}
		printf("%d\n", sum);
	}
}
//void Decode();
int PowDIY(int x, int n){
	int sum = 1;
	for(int i=0; i<n; i++){
		sum *= x; 
	}
	return sum;
}
