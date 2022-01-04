#include <stdlib.h>
#include <stdio.h>

#define GOLDEN_RATIO  0.61803398		//Golden ratio, for hash function

unsigned int g_p, g_m;

unsigned int Hash(unsigned int input);
int main(){
	int n;
	unsigned int input;
	
	scanf("%d%d%d", &g_p, &g_m, &n);

	unsigned char *bits = (unsigned char*)calloc((g_m>>3)+1, sizeof(unsigned char));		//m>>3 = m/8. caculate how many byte(char) do we need

			//get data and process it
	for(int i=0; i<n; i++){
		scanf("%d", &input);
		printf("%d ", input);

		input = Hash(input);		//get hash valus of input

			//check whether this hash valus have appeared
		if(bits[input>>3] & (1<<(input&((1<<3)-1)))){	//input>>3 = input/8, input&((1<<3)-1) = input%8, => bit[input/8] & (1<<(input%8))
																									//如果input的第input%8個位元為1，代表已經出現過，與(1<<(input%8)) &之後的值非0
			puts("0");			
		}
		else{
			bits[input>>3] += (1<<(input&((1<<3)-1)));		//該位元還為0，則&之後的結果為0，將該位元改為1
			puts("1");
		}
	}

	free(bits);

	return 0;
}
inline unsigned int Hash(unsigned int input){
		//m(table_size)乘上一個0~1之間的數A, 此A由input value來決定，決定的方法為:
		//將input_value*golden_ratio, 取其小數部分(即input_value*golden扣掉整數部分)
	return (unsigned int)(g_m*((double)input*GOLDEN_RATIO - (unsigned int)((double)input*GOLDEN_RATIO)));
}
