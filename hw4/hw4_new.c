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
}*g_test;


//int Hash(int input);
//int SetBitField(int offset, int bit_number);

int main(){
	int n, m, p;
	unsigned int input;
	
	scanf("%d%d%d", &p, &m, &n);

	//g_test = (BitField*)calloc((m>>3)+1, sizeof(BitField));	//one bit_fielt is 8 bits, so we need m>>3 + 1 bit_field
	//BitField g_test[(m>>3)+1];
	unsigned char *bit = (unsigned char*)calloc((m>>3)+1, sizeof(unsigned char));;

	/*
		//initialize
	for(int i=0; i<m; i++){
		switch(i & ((1<<3)-1)){	//1<<3 = 8, i & ((1<<3)-1)即為取小於(1<<3)的位元為1的部分
			case 0:
				g_test[i>>3].bit0 = 0;
				break;

			case 1:
				g_test[i>>3].bit1 = 0;
				break;

			case 2:
				g_test[i>>3].bit2 = 0;
				break;

			case 3:
				g_test[i>>3].bit3 = 0;
				break;

			case 4:
				g_test[i>>3].bit4 = 0;
				break;

			case 5:
				g_test[i>>3].bit5 = 0;
				break;

			case 6:
				g_test[i>>3].bit6 = 0;
				break;

			case 7:
				g_test[i>>3].bit7 = 0;
				break;
		}
	}
	*/
			//get data and process it
	for(int i=0; i<n; i++){
		scanf("%d", &input);
		printf("%d ", input);
		//input = Hash(input);

			input = ((input*input)%p)%m;

			switch(input & ((1<<3)-1)){		//0b1000 = 8	-> input%8
				case 0:
					if(g_test[input>>3].bit0 == 0){		//this place haven't been used
						g_test[input>>3].bit0 = 1;
						puts("1");
						continue;
					}
					break;

				case 1:
					if(g_test[input>>3].bit1 == 0){		//this place haven't been used
						g_test[input>>3].bit1 = 1;
						puts("1");
						continue;
					}
					break;

				case 2:
					if(g_test[input>>3].bit2 == 0){		//this place haven't been used
						g_test[input>>3].bit2 = 1;
						puts("1");
						continue;
					}
					break;

				case 3:
					if(g_test[input>>3].bit3 == 0){		//this place haven't been used
						g_test[input>>3].bit3 = 1;
						puts("1");
						continue;
					}
					break;
					
				case 4:
					if(g_test[input>>3].bit4 == 0){		//this place haven't been used
						g_test[input>>3].bit4 = 1;
						puts("1");
						continue;
					}
					break;

				case 5:
					if(g_test[input>>3].bit5 == 0){		//this place haven't been used
						g_test[input>>3].bit5 = 1;
						puts("1");
						continue;
					}
					break;

				case 6:
					if(g_test[input>>3].bit6 == 0){		//this place haven't been used
						g_test[input>>3].bit6 = 1;
						puts("1");
						continue;
					}
					break;

				case 7:
					if(g_test[input>>3].bit7 == 0){		//this place haven't been used
						g_test[input>>3].bit7 = 1;
						puts("1");
						continue;
					}
					break;
			}
			puts("0");	//bit field have been used
	}

			/*
		if(SetBitField(input>>3, input%8))
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
