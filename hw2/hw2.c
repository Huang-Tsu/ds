#include <stdio.h>
#include <stdlib.h>

#define NODE_ID 0
#define NODE_WEIGHT 1

int main(){
	int node_cnt;
	int packet_size;
	int link_cnt;
	int i;

	scanf("%d%d%d", &node_cnt, &link_cnt, &packet_size);
	int nodes[node_cnt][2];

	for(i=0; i<node_cnt; i++){
		scanf("%d%d", nodes[i][NODE_ID], nodes[i][NODE_WEIGHT]);
	}

	return 0;
}
