#include <stdio.h>
#include <stdlib.h>

int g_parent[100006], g_weight[100005], g_visited[100005]; 
int g_level[100005];

struct Vector{
	int *child_list;
	int child_cnt;
	int capacity;
}vector[100005];

void InitNode(int node_idx);
void PushBack(int idx1, int idx2);
int CountCurrentCost(int weight);

//-------queue--------
int g_queue[100005];
int g_head=-1, g_tail=-1;
int IsEmpty(){
	return g_head==g_tail;
}
void PushToQueue(int input){
	g_queue[++g_tail] = input;
}
int Pop(){
	return g_queue[++g_head];
}
//-------end---------

int g_packet_size;	//will be used by function, so let it be global variable

int main(){
	int node_cnt, link_cnt;
	int node1, node2;
	int useless_variable;
	int total_cost = 0;
	int node_now;
	int child_now;
	int max_level = 0;
	scanf("%d%d%d", &node_cnt , &link_cnt, &g_packet_size);
		//readweight
	for(int i=0; i<node_cnt; i++){
		scanf("%d%d", &useless_variable, &g_weight[i]);	
	}
		//build adjacent list
	for(int i=0; i<link_cnt; i++){
		scanf("%d%d%d", &useless_variable, &node1, &node2);
		if(!vector[node1].child_cnt) //if node1 of vector is empty, initialize it
			InitNode(node1);
		if(!vector[node2].child_cnt)
			InitNode(node2);
		
			//build relation between node1 node2.
		PushBack(node1, node2);	
		PushBack(node2, node1);
	}

			//build tree
			//using BST
		PushToQueue(0);
		g_visited[0] = 1;
		while(!IsEmpty()){	//when queue is not empty, execute
			node_now = Pop();	//pop one node from queue, and add every child of this node into queue
				for(int j=0; j<vector[node_now].child_cnt; j++){
					child_now = vector[node_now].child_list[j];
					if(!g_visited[child_now]){			//check whether this child have not been visited
						g_visited[child_now] = 1;
						g_level[child_now] = g_level[node_now]+1;	//set level
						max_level = g_level[child_now]>max_level? g_level[child_now] : max_level; //renew max_level
						g_parent[child_now] = node_now;
						PushToQueue(child_now);		//push this child into queue
					}	
				}
		}
		
			//Count total cost
		g_head = g_tail = -1; //reset idxes of queuq, because we will use it later.
		for(int i=max_level; i>0; i--){
			for(int j=0; j<node_cnt; j++){	//push nodes of level i into queue
				if(g_level[j] == i)
					PushToQueue(j);
			}
			while(!IsEmpty()){	//each time pop one node from queue, and count the coust of its weight, then add its weight to itsparent.
				node_now = Pop();
				if(node_now == 0)
					break;

				total_cost += CountCurrentCost(g_weight[node_now]);	//count the cost of current node.
				g_weight[g_parent[node_now]] += g_weight[node_now];	//increase the weight of parent by the weight of node_now.
			}
		}

			//print result
		printf("%d %d\n", node_cnt, total_cost);
		for(int i=0; i<node_cnt; i++){
			printf("%d %d\n", i, g_parent[i]);
		}
	return 0;
}
void InitNode(int idx){
	vector[idx].child_list = (int*)calloc(10, sizeof(int));	//initialize child_list
	vector[idx].capacity = 10;
}
void PushBack(int idx1, int idx2){
	if(vector[idx1].child_cnt+1 > vector[idx1].capacity){   //check whether child_list have enough memory for new child.
			//make the capacity of child_list one time larger
		vector[idx1].child_list = (int*)realloc(vector[idx1].child_list, vector[idx1].capacity*2*sizeof(int));
		vector[idx1].capacity *= 2;
	}
	vector[idx1].child_list[vector[idx1].child_cnt++] = idx2;		//add idx2 into the child list of idx1
}
int CountCurrentCost(int weight){
	return weight%g_packet_size == 0? weight/g_packet_size : weight/g_packet_size+1; //if we can not divide weight by packet_size, then return result+1
}
