#include <stdlib.h>
#include <stdio.h>

//#define SUCCESS 1
//#define FAIL 0

typedef struct BitField BitField;

struct BitField{
	unsigned char bit0:1;		//number after colon means the bit of this variable
	unsigned char bit1:1;
	unsigned char bit2:1;
	unsigned char bit3:1;
	unsigned char bit4:1;
	unsigned char bit5:1;
	unsigned char bit6:1;
	unsigned char bit7:1;
};

int g_m, g_p;

//int Hash(int input);
//int SetBitField(int offset, int bit_number);

int main(){
	int n;
	int input;
	
	scanf("%d%d%d", &g_p, &g_m, &n);

	//g_test = (BitField*)calloc(g_m/8+1, sizeof(BitField));	//one bit_fielt is 8 bits, so we need m/8 + 1 bit_field
	BitField g_test[g_m/8+1];

		for(int i=0; i<g_m; i++){
			switch(i%8){
				case 0:
					g_test[i/8].bit0 = 0;
					break;

				case 1:
					g_test[i/8].bit1 = 0;
					break;

				case 2:
					g_test[i/8].bit2 = 0;
					break;

				case 3:
					g_test[i/8].bit3 = 0;
					break;

				case 4:
					g_test[i/8].bit4 = 0;
					break;

				case 5:
					g_test[i/8].bit5 = 0;
					break;

				case 6:
					g_test[i/8].bit6 = 0;
					break;

				case 7:
					g_test[i/8].bit7 = 0;
					break;
			}
		}
	for(int i=0; i<n; i++){
		scanf("%d", &input);
		printf("%d ", input);

		//input = Hash(input);
			input = ((input*input)%g_p)%g_m;
			switch(input%8){
				case 0:
					if(g_test[input/8].bit0 == 0){		//this place haven't been used
						g_test[input/8].bit0 = 1;
						puts("1");
					}
					else
						puts("0");
					break;

				case 1:
					if(g_test[input/8].bit1 == 0){		//this place haven't been used
						g_test[input/8].bit1 = 1;
						puts("1");
					}
					else
						puts("0");
					break;

				case 2:
					if(g_test[input/8].bit2 == 0){		//this place haven't been used
						g_test[input/8].bit2 = 1;
						puts("1");
					}
					else
						puts("0");
					break;

				case 3:
					if(g_test[input/8].bit3 == 0){		//this place haven't been used
						g_test[input/8].bit3 = 1;
						puts("1");
					}
					else
						puts("0");
					break;
					
				case 4:
					if(g_test[input/8].bit4 == 0){		//this place haven't been used
						g_test[input/8].bit4 = 1;
						puts("1");
					}
					else
						puts("0");
					break;

				case 5:
					if(g_test[input/8].bit5 == 0){		//this place haven't been used
						g_test[input/8].bit5 = 1;
						puts("1");
					}
					else
						puts("0");
					break;

				case 6:
					if(g_test[input/8].bit6 == 0){		//this place haven't been used
						g_test[input/8].bit6 = 1;
						puts("1");
					}
					else
						puts("0");
					break;

				case 7:
					if(g_test[input/8].bit7 == 0){		//this place haven't been used
						g_test[input/8].bit7 = 1;
						puts("1");
					}
					else
						puts("0");
					break;
			}
	}

			/*
		if(SetBitField(input/8, input%8))
			puts("1");
		else
			puts("0");
	}
	*/
	

	//free(g_test);

	return 0;
}
/*
inline int Hash(int input){
	return ((input*input)%g_p)%g_m;
}
*/
/*
int SetBitField(int offset, int bit_number){
	switch(bit_number){
		case 0:
			if((g_test+offset)->bit0 == 0){		//this place haven't been used
				(g_test+offset)->bit0 = 1;
				return SUCCESS;
			}
			else
				return FAIL;
		case 1:
			if((g_test+offset)->bit1 == 0){		//this place haven't been used
				(g_test+offset)->bit1 = 1;
				return SUCCESS;
			}
			else
				return FAIL;
		case 2:
			if((g_test+offset)->bit2 == 0){		//this place haven't been used
				(g_test+offset)->bit2 = 1;
				return SUCCESS;
			}
			else
				return FAIL;
		case 3:
			if((g_test+offset)->bit3 == 0){		//this place haven't been used
				(g_test+offset)->bit3 = 1;
				return SUCCESS;
			}
			else
				return FAIL;
		case 4:
			if((g_test+offset)->bit4 == 0){		//this place haven't been used
				(g_test+offset)->bit4 = 1;
				return SUCCESS;
			}
			else
				return FAIL;
		case 5:
			if((g_test+offset)->bit5 == 0){		//this place haven't been used
				(g_test+offset)->bit5 = 1;
				return SUCCESS;
			}
			else
				return FAIL;
		case 6:
			if((g_test+offset)->bit6 == 0){		//this place haven't been used
				(g_test+offset)->bit6 = 1;
				return SUCCESS;
			}
			else
				return FAIL;
		case 7:
			if((g_test+offset)->bit7 == 0){		//this place haven't been used
				(g_test+offset)->bit7 = 1;
				return SUCCESS;
			}
			else
				return FAIL;
	}
}
*/
