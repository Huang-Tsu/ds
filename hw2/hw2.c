#include <stdio.h>
#include <stdlib.h>

typedef struct Node Node;
struct Node{
	int weight;
	int parent;
	int child_cnt;
	int child_list_capacity;
	int *child_list;
}*g_nodes;

void ReadWeightAndInitNodes();
void ReadNodesRelation();
void BuildRelation(int temp_parent, int temp_child);
int CountTotalCost(Node *ptr);
inline int CountCurrentCost(int weight);

int g_packet_size;
int g_node_cnt;
int g_link_cnt;
int g_total_cost = 0;

int main(){
	scanf("%d%d%d", &g_node_cnt, &g_link_cnt, &g_packet_size);
	g_nodes = (Node*)calloc(g_node_cnt, sizeof(Node)+10);
		if(!g_nodes)
			exit(1);

	ReadWeightAndInitNodes();
	ReadNodesRelation();

	CountTotalCost(g_nodes);

		//print result
	printf("%d %d\n", g_node_cnt, g_total_cost);
	g_nodes[0].parent = 0;
	for(int i=0; i<g_node_cnt; i++){
		printf("%d %d\n", i, g_nodes[i].parent);
		free(g_nodes[i].child_list);
	}
	//free(.adj_list);
	free(g_nodes);

	return 0;
}
void ReadWeightAndInitNodes(){
	int useless_variable;
	for(int i=0; i<g_node_cnt; i++){
		scanf("%d%d", &useless_variable, &g_nodes[i].weight);
		g_nodes[i].parent = -1;
		g_nodes[i].child_cnt = 0;
		g_nodes[i].child_list_capacity = 0;
		g_nodes[i].child_list = NULL;
	}
}
void ReadNodesRelation(){
	int useless_variable, a, b;
	for(int i=0; i<g_link_cnt; i++){
		scanf("%d%d%d", &useless_variable, &a, &b);
		BuildRelation(a, b);
	}
}
void BuildRelation(int first, int second){
	if(g_nodes[second].parent != -1)	//already have a parent, don't do anything.
		return;

	Node *first_node = &g_nodes[first];	//let "first_node" be the alternative of "g_nodes[first]" because it's easier to be read.

	if(first_node->child_list_capacity == 0){	//check whether child_list have memory
			//allocate memory for child list
		first_node->child_list = calloc(10, sizeof(int));
		first_node->child_list_capacity = 10;
	}

	if(first_node->child_cnt+1 >= first_node->child_list_capacity){ //check whether child_list have enough memory for new child.
			//make the capacity of child_list one time larger
		first_node->child_list = (int*)realloc(first_node->child_list, first_node->child_list_capacity*2*sizeof(int));
			if(!first_node->child_list)
				exit(1);
		first_node->child_list_capacity *= 2;
	}
		//Finally, build relation between first and second
	first_node->child_list[first_node->child_cnt++] = second;
	g_nodes[second].parent = first;
}
int CountTotalCost(Node *ptr){
		//end condition
	if(ptr->child_cnt == 0){	//this node have no child. It means we reach leaf.
		g_total_cost += CountCurrentCost(ptr->weight);
		return ptr->weight;
	}

	for(int i=0; i<ptr->child_cnt; i++){ //count the total cost of the subtree of this node, and collect all of the sub-nodes weight.
		ptr->weight += CountTotalCost(&g_nodes[ptr->child_list[i]]);
	}

	if(ptr->parent != -1)	//check whether this node is not root node
		g_total_cost += CountCurrentCost(ptr->weight);
	
	return ptr->weight;
}
int CountCurrentCost(int weight){
	return weight%g_packet_size == 0? weight/g_packet_size : weight/g_packet_size+1;
}
