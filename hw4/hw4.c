#include <stdlib.h>
#include <stdio.h>

typedef struct BitField BitField;

struct BitField{
	unsigned char test1:1;
	unsigned char test2:1;
	unsigned char test3:1;
	unsigned char test4:1;
	unsigned char test5:1;
	unsigned char test6:1;
	unsigned char test7:1;
	unsigned char test8:1;
}*g_test;

int main(){
	int n, m, p;
	
	scanf("%d%d%d", &n, &m, &p);

	g_test = (BitField*)calloc(n, sizeof(BitField));
	

	return 0;
}
