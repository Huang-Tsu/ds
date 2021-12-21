#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h> //for INT_MAX
	#include <unistd.h>

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

int *g_select_links;
int g_select_links_cnt = 0;
int g_links_cnt_total;
int g_links_cnt_now;
int g_nodes_cnt;
int g_noise;
double g_power;

double GetTransmitPower(int sender_id, int receiver);
void DeleteNode(int link_id);
void UpdateAffectance(int new_link_id);
void UpdateTolerance(int new_link_id);
void AddLinkToSolutionSet(int new_link_id);
int CheckFeasibility(int new_link_id);
int FindMinAffectLink();

int main(){
	int i;
	int max_tolerance = 0;
	int max_link;
	int next_link_id;
	int useless_var;

	scanf("%d%d%lf%d", &g_nodes_cnt, &g_links_cnt_total, &g_power, &g_noise);
	g_links_cnt_now = g_links_cnt_total;

	g_nodes = (Nodes*)calloc(g_nodes_cnt, sizeof(Nodes));
	g_links = (Links*)calloc(g_links_cnt_total, sizeof(Links));
	g_select_links = (int*)calloc(g_links_cnt_total, sizeof(int));

		//input nodes
	for(i=0; i<g_nodes_cnt; i++){
		scanf("%d%d%d", &useless_var, &g_nodes[i].x, &g_nodes[i].y);
	}
		//input links
	for(i=0; i<g_links_cnt_total; i++){
		scanf("%d%d%d", &useless_var, &g_links[i].sender, &g_links[i].receiver);
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

	//g_solution_links_id[g_solution_link_cnt++] = max_link;
		//add a max link into solution set
		//after being selected into solution, delete node in the set of possible link
	AddLinkToSolutionSet(max_link);
	next_link_id = FindMinAffectLink();

	while(g_links_cnt_now){
		AddLinkToSolutionSet(next_link_id);
		next_link_id = FindMinAffectLink();
	}
	
		//print result
	printf("%d\n", g_select_links_cnt);
	for(i=0; i<g_links_cnt_total; i++){
		if(g_links[i].select){
			printf("%d %d %d\n", i, g_links[i].sender, g_links[i].receiver);
		}
	}
	
	free(g_nodes);
	free(g_links);
	free(g_select_links);
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
			if(g_links[i].exist){
				g_links[i].exist = 0;
				g_links_cnt_now --;
			}
		}
	}
}
void UpdateAffectance(int new_link_id){
		//update affectance of links in possible links set after adding a new link into solution set
		//the affected degree of newly selected link by link[i] is computed by the transmit power from link[i]'s sender to newly selected link's receiver
	for(int i=0; i<g_links_cnt_total; i++){
		if(g_links[i].exist==1 && g_links[i].select==0){	//if this link exists and haven't been selected, then update
			//the affected degree of newly selected link by link[i] is computed by the transmit power from link[i]'s sender to newly selected link's receiver
			g_links[i].affectance += GetTransmitPower(g_links[i].sender, g_links[new_link_id].receiver);	//compute how much newly selected link will be affect by this link
		}
	}
}
void UpdateTolerance(int new_link_id){
		//update tolerance of all the exist links(including links in possible links set and solution set)
	for(int i=0; i<g_links_cnt_total; i++){
		if(g_links[i].exist==1 && i!=new_link_id){
			g_links[i].tolerance -= GetTransmitPower(g_links[new_link_id].sender, g_links[i].receiver);
			if(g_links[i].tolerance <= 0){		//if this link's SINR value already less or equal to 0, discard it
				g_links[i].exist = 0;
					g_links_cnt_now --;
					//debugger
				if(g_links[i].select == 1){
					fprintf(stderr, "UpdateTolerance() 出錯了!\n");
				}
			}
		}
	}
}
void AddLinkToSolutionSet(int new_link_id){
	g_select_links[g_select_links_cnt++] = new_link_id;
	g_links[new_link_id].select = 1;
	g_select_links_cnt ++;
	DeleteNode(g_links[new_link_id].sender);
	DeleteNode(g_links[new_link_id].receiver);
	UpdateTolerance(new_link_id);
	UpdateAffectance(new_link_id);
}
int CheckFeasibility(int new_link_id){
		//check whether this new_link will break the belence in solution set, if so, discard it
		//return value will be 1 or 0, 1 stand for feasible, 0 otherwise
	for(int i=0; i<g_select_links_cnt; i++){
					//from new link to checked node
			if(g_links[g_select_links[i]].tolerance < GetTransmitPower(g_links[new_link_id].sender, g_links[g_select_links[i]].receiver)){
				g_links[new_link_id].exist = 0;		//discard new_link
				g_links_cnt_now --;
				return 0;	//return infeasible
			}
	}
	return 1;		//return feasible
}
int FindMinAffectLink(){
		//find a link with minimal affectance in possible link set
		//it will be the next link to be add to solution set
		//because we want to minimize the affectance to links in solution set
	int min_affectance_id;
	double min_affectance = (double)INT_MAX;
	while(g_links_cnt_now){
		for(int i=0; i<g_links_cnt_total; i++){
			if(g_links[i].exist==1 && g_links[i].select==0){	//if this link exists and haven't been selected, and is not new node, then check it
				if(g_links[i].affectance < min_affectance){
					min_affectance = g_links[i].affectance;
					min_affectance_id = i;
				}
			}
		}
			//check whether this link is feasible in solution set. If so, return it's id. If not, find link with minimal again
		if(CheckFeasibility(min_affectance_id))
			break;
		else 
			continue;
	}
	return min_affectance_id;	
}
