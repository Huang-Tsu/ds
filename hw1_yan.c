#include    <stdio.h>
#include    <stdlib.h>
#include    <math.h>
#include    <string.h>

int Pow(int x, int n);
void SwapRow(double *row1, double *row2, int row_len);
int **devidestr(char *string, int n, int **num){
    int x, i;
    char *ptr;
    
    x = strlen(string)/n;
    char pat[x+1];
    ptr = string;
    for(i=0;i<n;i++){
        strncpy(pat, ptr, x);
				pat[x] = '\0';
					//printf("%s\n", pat);
        num[i] = (int *) malloc(x * sizeof(int));
        *num[i] = atoi(pat);
        ptr+=x;
        memset(pat, 0, sizeof(pat));
    }
    return num;
}

int my_copy(int **num, int n, int total){
    int i, j;
    int cnt=0;
    int **equation;
    
    equation = (int **) malloc(total * sizeof(int *));
    for(i=0;i<total;i++){
        equation[i] = (int *) malloc((n + 1) * sizeof(int));
    }
    for(i=0;i<total;i++){
        if(i < n){
            equation[i][i] = 1;
            for(j=0;j<n;j++){
                if(j != i) equation[i][j] = 0;
            }
            equation[i][j] = *num[i];
        }
        else{
            for(j=0;j<n;j++){
                equation[i][j] = Pow(i - n + 1, j);
                cnt+=equation[i][j] * (*num[j]);
            }
            equation[i][j] = cnt;
            cnt=0;
        }
    }
    for(i=0;i<total;i++){  
        for(j=0;j<n;j++){  
            printf("%d ",equation[i][j]);  
        }
        printf("%d\n",equation[i][j]);
    }
			for(i=0; i<total; i++){
				free(equation[i]);
			}
		free(equation);
    return 0;
}

int my_gaussian(double **matrix, int equaNum){
    int i, j, k;
    int x=0, y=0;
    double temp;
		double coefficient; 
    
    for(x=0; x<equaNum; x++){
        //檢查pivot是否為0 是就要跟後面換
        while(matrix[x][x]==0){
            i = x + 1;
            while(matrix[i][x]==0) i++;
            
						/*
            if(i >= equaNum){
                x++;
                continue;
            }
						*/
						/*
									puts("Find leading one");
									for(int h=0; h<equaNum; h++){
										for(int s=0; s<equaNum+1; s++){
											printf("%d ", (int)matrix[h][s]);
										}
										puts("");
									}
										puts("-----------");
										*/
            
            //找完開始互換
            for(j=x;j<equaNum+1;j++){  
                temp = matrix[i][j];  
                matrix[i][j] = matrix[x][j];  
                matrix[x][j] = temp;  
            }
        }
        //除掉倍數pivot變1
        for(j=equaNum; j>=x; j--){  
            matrix[x][j] /= matrix[x][x];  
        }  
				/*
									puts("after introduce leading one");
									for(int h=0; h<equaNum; h++){
										for(int s=0; s<equaNum+1; s++){
											printf("%d ", (int)matrix[h][s]);
										}
										puts("");
									}
										puts("-----------");
										*/
        
        //開始消去
        for(i=0;i<equaNum;i++){
            if(i == x) continue;
            for(j=equaNum;j>=x;j--){
								if(matrix[i][x] == 0)
									continue;

								coefficient = matrix[i][x];
                matrix[i][j] -= matrix[x][j]*coefficient;
            }
        }
									puts("after gauss");
									for(int h=0; h<equaNum; h++){
										for(int s=0; s<equaNum+1; s++){
											printf("%d ", (int)matrix[h][s]);
										}
										puts("");
									}
										puts("-----------");
    }
    // for(i=0;i<equaNum;i++){  
    //     for(j=0;j<equaNum+1;j++){  
    //         printf("%d ",matrix[i][j]);  
    //     }
    //     printf("\n");
    // }
    for(i=0;i<equaNum;i++){
        printf("%d", (int)matrix[i][equaNum]);
    }
    printf("\n");
    return 0;
}

int main(){
    int mode;
    int equaNum;
    int i, j, n, m;
    char string[1024];
    double **matrix;
    int **num;
    
    scanf("%d", &mode);
    if(mode == 0){
        scanf("%d", &n);
        scanf("%d", &m);
        scanf("%s", string);
        
        num = (int **) malloc(n * sizeof(int *));
        num = devidestr(string, n, num);
        // for(i=0;i<n;i++){
        //     printf("%d\n", *num[i]);
        // }
        
        my_copy(num, n, n+m);
						for(i=0; i<n; i++){
							free(num[i]);
						}
				free(num);
    }
    else{
        scanf("%d", &equaNum);
        matrix = (double **) malloc(equaNum * sizeof(double *));
        for(i=0;i<equaNum;i++){
            matrix[i] = (double *) malloc((equaNum + 1) * sizeof(double));
        }
        for(i=0;i<equaNum;i++){
            for(j=0;j<equaNum+1;j++){
                scanf("%lf", &matrix[i][j]);
            }
        }
        
        // for(i=0;i<equaNum;i++){  
        //     for(j=0;j<3;j++){  
        //         printf("%d ",matrix[i][j]);  
        //     }
        //     printf("\n");
        // }
				/*
									puts("After input data");
									for(int h=0; h<equaNum; h++){
										for(int s=0; s<equaNum+1; s++){
											printf("%d ", (int)matrix[h][s]);
										}
										puts("");
									}
										puts("-----------");
										*/
        my_gaussian(matrix, equaNum);
				for(i=0; i<equaNum; i++){
					free(matrix[i]);
				}
				free(matrix);
    }
    return 0;
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
