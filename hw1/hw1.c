#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define ENCODE 0
#define DECODE 1
#define MAX_LEN 11

void Encode();
void Decode();
void SwapRow(double *row1, double *row2, int row_len);
int Pow(int x, int n);

int main(){
	int mode;

	scanf("%d", &mode);

	if(mode == ENCODE)
		Encode();
	else
		Decode();

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

	str_len = strlen(input_str);	//get input string length
	chunck_len = str_len/n;			//get the length of each chunck

	char n_str_chuncks[n][MAX_LEN];	
	int n_num_chuncks[n];

	for(i=0; i<n; i++){
			//first divide string into different character array
		for(j=0; j<chunck_len; j++){
			n_str_chuncks[i][j] = input_str[i*chunck_len+j]; 	
		}
			//then copy and interpret each character array into integer array
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
			cofficient = Pow(i, j);
			printf("%d ", cofficient); 			
			sum += cofficient*n_num_chuncks[j];
		}
		printf("%d\n", sum);
	}
}
void Decode(){
	int n;
	int i, j, k;
	double coefficient;

	scanf("%d", &n);
	double matrix[n][n+1];

	for(i=0; i<n; i++){
		for(j=0; j<n+1; j++){
			scanf("%lf", &matrix[i][j]);
		}
	}
		//start Gauss elimination
	for(i=0; i<n; i++){	//i point to the row now
			//find leading one
		if(matrix[i][i] == 0){
			for(j=i+1; j<n; j++){
				if(matrix[j][i] != 0){
					SwapRow(matrix[i], matrix[j], n+1); // swap(row1, row2, row len)
					break;
				}
			}
		}
			//introduce leading 1
		coefficient = matrix[i][i];
		for(j=i; j<n+1; j++){	//j point to the colum number of row now
			matrix[i][j] /= coefficient;
		}
			//reduce downward
		for(j=i+1; j<n; j++){	//j point to the number of changed row
			if(matrix[j][i] == 0)	//若要被消掉的列，有leading，1在的行為0，則直接進到下一列
				continue;

			coefficient = matrix[j][i];
			for(k=i; k<n+1; k++){	//k point to the colum number of changed row
				matrix[j][k] -= matrix[i][k]*coefficient;
			}
		}
	}
		//reduce row upward
	for(i=n-1; i>0; i--){	//i point to row number now
		for(j=i-1; j>=0; j--){	//j point to changed row number
			if(matrix[j][i] == 0)
				continue;

			coefficient = matrix[j][i];
			for(k=n; k>=i; k--){
				matrix[j][k] -= matrix[i][k]*coefficient;
			}
		}
	}
	for(i=0; i<n; i++){
		printf("%d", (int)matrix[i][n]);
	}
	puts("");
}
int Pow(int x, int n){
	int sum = 1;
	for(int i=0; i<n; i++){
		sum *= x; 
	}
	return sum;
}
void SwapRow(double *row1, double *row2, int row_len){
	double temp;
	for(int i=0; i<row_len; i++){
		temp = row1[i];
		row1[i] = row2[i];
		row2[i] = temp;
	}
}
