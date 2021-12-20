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
	int exist;
	int select;
	int sender;
	int receiver;
	double tolerance;
	double affectance;
}*g_links;

//int *g_solution_links_id;
//int g_solution_link_cnt = 0;
int g_links_cnt_total;
int g_links_cnt_now
int g_nodes_cnt;
int g_noise;
double g_power;

double GetTransmitPower(int sender_id, int receiver);
void DeleteNode(int link_id);
void UpdateAffectance(int new_link_id);
void UpdateTolerance(int new_link_id);

int main(){
	int i;
	int max_tolerance = 0;
	int max_link;

	scanf("%d%d%lf%d", &g_nodes_cnt, &g_links_cnt_total, &g_power, &g_noise);
	g_links_cnt_now = g_links_cnt_total;

	g_nodes = (Nodes*)calloc(g_nodes_cnt, sizeof(Nodes));
	g_links = (Links*)calloc(g_links_cnt_total, sizeof(Links));
	//g_solution_links_id = (int*)calloc(g_links_cnt, sizeof(int));

		//input nodes
	for(i=0; i<g_nodes_cnt; i++){
		scanf("%d%d", &g_nodes[i].x, &g_nodes[i].y);
	}
		//input links
	for(i=0; i<g_links_cnt_total; i++){
		scanf("%d%d", &g_links[i].sender, &g_links[i].receiver);
		g_links[i].tolerance = GetTransmitPower(g_links[i].sender, g_links[i].receiver) - g_noise;	//tolerance is p/di^3 - Noise, which show the abality to transmit this link have
		g_links[i].affectance = 0;				//affectance is how much this link affect the links in solution set
		g_links[i].exist = 1;
		g_links[i].select = 0;

			//find a link with max tolerance
		if(g_links[i].tolerance > max_tolerance){
			max_tolerance = g_links[i].tolerance;
			max_link = i;
		}
	}

		//add a max link into solution set
	//g_solution_links_id[g_solution_link_cnt++] = max_link;
		//after being selected into solution, delete node in the set of possible link
	g_links[max_link].select = 1;
	DeleteNode(g_links[max_link].sender);
	DeleteNode(g_links[max_link].receiver);
	UpdateTolerance(max_link);
	UpdateAffectance(max_link);
	
	return 0;
}
double GetTransmitPower(int sender, int receiver){
		//count how much power will be transmitted from sender to receiver
	double distance = sqrt(pow(g_nodes[sender].x-g_nodes[receiver].x, 2) + pow(g_nodes[sender].y-g_nodes[receiver].y, 2));
	return g_power/pow(distance, 3);
}
void DeleteNode(int link_id){
		//link_id is a link being selected, we want to delete all the link who also connect to the node of selected link 
	for(int i=0; i<g_links_cnt_total; i++){
		if(g_links[i].sender==g_links[link_id].sender ||
			 g_links[i].receiver==g_links[link_id].receiver){
			g_links[i].exist = 0;
		}
	}
}
void UpdateAffectance(int new_link_id){
	for(int i=0; i<g_links_cnt_total; i++){
		if(g_links[i].exist == 1){
			g_links[i].affectance += GetTransmitPower(g_links[i].sender, g_links[new_link_id].receiver);	//compute how much newly selected link will be affect by this link
			//the affected degree of newly selected link by link[i] is computed by the transmit power from link[i]'s sender to newly selected link's receiver
		}
	}
}
void UpdateTolerance(int new_link_id){
	for(int i=0; i<g_links_cnt_total; i++){
		if(g_links[i].exist == 1){
			g_links[i].tolerance -= GetTransmitPower(g_links[new_link_id].sender, g_links[i].receiver);
		}
	}
}
