#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct Links Links;
typedef struct Nodes Nodes;

struct Nodes{
	int x;
	int y;
}*g_nodes;
struct Links{
	Nodes sender;
	Nodes receiver;
	double tolerance;
	double affectance;
}*g_links;

int *g_solution_links_id;
int g_solution_link_cnt = 0;
int g_links_cnt;
int g_nodes_cnt;
int g_noise;
double g_power;

double GetTolerance(Links);

int main(){
	int i;
	int max_tolerance = 0;
	int max_link;

	scanf("%d%d%lf%d", &g_nodes_cnt, &g_nodes_cnt, &g_power, &g_noise);

	g_nodes = (*Nodes)calloc(g_nodes_cnt, sizeof(Nodes));
	g_links = (*Links)calloc(g_links_cnt, sizeof(Links));
	g_

		//input nodes
	for(i=0; i<g_nodes_cnt, i++){
		scanf("%d%d", &g_nodes[i].x, &g_nodes[i].y);
	}
		//input links
	for(i=0; i<g_links_cnt, i++){
		scanf("%d%d", &g_links[i].sender, &g_links[i].receiver);
		g_links[i].tolerance = GetTolerance(g_links[i]);	//tolerance is p/di^3, which show the abality this link have to transmit
		g_links[i].affectance = 0;				//affectance is how much this link affect the links in solution set

		if(g_links[i].tolerance > max_tolerance){
			max_tolerance = g_links[i].tolerance;
			max_link = i;
		}
	}

	return 0;
}
double GetTolerance(Links link){
		//count how much one 
	double distance = sqrt(pow(link.sender.x-link.receiver.x, 2) + pow(link.sender.y-link.receiver.y, 2))
	return g_power/pow(distance, 3);
}
