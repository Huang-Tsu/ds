#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h> //for INT_MAX

typedef struct Links Links;
typedef struct Nodes Nodes;

struct Nodes{
	int x;
	int y;
}*g_nodes;
struct Links{
	int exist;
	int select;
	int sender;
	int receiver;
	double tolerance;
}*g_links;

int g_nodes_cnt, g_links_cnt, g_noise;
double g_power;
int *g_select;
int g_select_cnt = 0;

int CheckFeasibility(int id);
void UpdateTolerance(int new_link_id);
void AddLinkToSolutionSet(int id);
void DeleteNode(int end1, int end2);
double GetTransmitPower(int sender, int receiver);

int main(){
	int useless_var;
	int i;

	scanf("%d%d%lf%d", &g_nodes_cnt, &g_links_cnt, &g_power, &g_noise);
	g_nodes = (Nodes*)calloc(g_nodes_cnt, sizeof(Nodes));
	g_links = (Links*)calloc(g_links_cnt, sizeof(Links));
	g_select= (int*)calloc(g_links_cnt, sizeof(int));
	
		//input nodes
	for(i=0; i<g_nodes_cnt; i++){
		scanf("%d%d%d", &useless_var, &g_nodes[i].x, &g_nodes[i].y);
	}

		//input links
	for(i=0; i<g_links_cnt; i++){
		scanf("%d%d%d", &useless_var, &g_links[i].sender, &g_links[i].receiver);
		g_links[i].tolerance = GetTransmitPower(g_links[i].sender, g_links[i].receiver) - g_noise;	//tolerance is p/di^3 - Noise, which show the abality to transmit this link have
		g_links[i].exist = 1;
		g_links[i].select = 0;

		if(g_links[i].tolerance <= 0)
			g_links[i].exist = 0;
	}
	
	if(g_links[0].exist == 1)
		AddLinkToSolutionSet(0);

	for(i=1; i<g_links_cnt; i++){
		if(g_links[i].select==0 && g_links[i].exist==1){
			if(CheckFeasibility(i)==1)
				AddLinkToSolutionSet(i);
		}
	}

		//print result
	printf("%d\n", g_select_cnt);
	for(i=0; i<g_links_cnt; i++){
		if(g_links[i].select){
			printf("%d %d %d\n", i, g_links[i].sender, g_links[i].receiver);
		}
	}
	
	free(g_nodes);
	free(g_links);
	free(g_select);
	return 0;
}
double GetTransmitPower(int sender, int receiver){
		//count how much power will be transmitted from sender to receiver
	double distance = sqrt(pow(g_nodes[sender].x-g_nodes[receiver].x, 2) + pow(g_nodes[sender].y-g_nodes[receiver].y, 2));
	return g_power/pow(distance, 3.0);
}
void AddLinkToSolutionSet(int id){
	g_select[g_select_cnt++] = id;
	g_links[id].select = 1;
	DeleteNode(g_links[id].sender, g_links[id].receiver);
	UpdateTolerance(id);
}
void DeleteNode(int end1, int end2){
	for(int i=0; i<g_links_cnt; i++){
		if(g_links[i].exist==1 && g_links[i].select==0){
			if(g_links[i].sender==end1||g_links[i].sender==end2 || g_links[i].receiver==end2||g_links[i].receiver==end2){
				g_links[i].exist = 0;
			}
		}
	}
}
void UpdateTolerance(int id){
		//update tolerance of all the exist links(including links in possible links set and solution set)
	for(int i=0; i<g_links_cnt; i++){
		if(g_links[i].exist==1 && i!=id){
			g_links[i].tolerance -= GetTransmitPower(g_links[id].sender, g_links[i].receiver);
			if(g_links[i].tolerance <= 0){		//if this link's SINR value already less or equal to 0, discard it
				g_links[i].exist = 0;
			}
		}
	}
}
int CheckFeasibility(int id){
		//check whether this new_link will break the belence in solution set, if so, discard it
		//return value will be 1 or 0, 1 stand for feasible, 0 otherwise
	for(int i=0; i<g_select_cnt; i++){
					//from new link to checked node
			if(g_links[g_select[i]].tolerance <= GetTransmitPower(g_links[id].sender, g_links[g_select[i]].receiver)){
				g_links[id].exist = 0;		//discard new_link
				return 0;	//return infeasible
			}
	}
	return 1;		//return feasible
}
