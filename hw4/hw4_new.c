#include <stdlib.h>
#include <stdio.h>

#define CONSTANT_A  0.61803398

int g_p, g_m;

unsigned int Hash(unsigned int input);
int main(){
	int n;
	unsigned int input;
	
	scanf("%d%d%d", &g_p, &g_m, &n);

	unsigned char *bit = (unsigned char*)calloc((g_m>>3)+1, sizeof(unsigned char));		//m>>3 = m/8

			//get data and process it
	for(int i=0; i<n; i++){
		scanf("%d", &input);
		printf("%d ", input);

			input = Hash(input);		//get hash valus of input

				//check whether this hash valus have appeared
			if(bit[input>>3] & (1<<(input&((1<<3)-1)))){	//input>>3 = input/8, input&((1<<3)-1) = input%8, => bit[input/8] & (1<<(input%8))
																										//如果input的第input%8個位元為1，代表已經出現過，與(1<<(input%8)) &之後的值非0
				puts("0");			
			}
			else{
				bit[input>>3] += (1<<(input&((1<<3)-1)));		//該位元還為0，&之後的結果為0，將該位元改為1
				puts("1");
			}
	}

	free(bit);

	return 0;
}
inline unsigned int Hash(unsigned int input){
		return (unsigned int)(g_m*((double)input*CONSTANT_A - (unsigned int)((double)input*CONSTANT_A)));
		//return ((input*input)%g_p)%g_m;
}
