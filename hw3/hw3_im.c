#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h> //for INT_MAX

typedef struct Links Links;
typedef struct Nodes Nodes;

struct Nodes{
	int x;
	int y;
		int adj_links_cnt;
}*g_nodes;
struct Links{
	int exist;
	int select;
	int sender;
	int receiver;
		int adj_links_cnt;
	double tolerance;
}*g_links;

int g_nodes_cnt, g_links_cnt, g_noise;
	int g_possible_cnt;
double g_power;
int *g_select;
int g_select_cnt = 0;

int CheckFeasibility(int id);
void DeleteLink(int link_id);
int FindMinAdjLink();
void UpdateTolerance(int new_link_id);
void AddLinkToSolutionSet(int id);
void DeleteNodesOfLink(int end1, int end2);
double GetTransmitPower(int sender, int receiver);

int main(){
	int useless_var;
	int i;
		int next_link;

	scanf("%d%d%lf%d", &g_nodes_cnt, &g_links_cnt, &g_power, &g_noise);
	g_possible_cnt = g_links_cnt;
		//alocate memory space for nodes, links, and solution set
	g_nodes = (Nodes*)calloc(g_nodes_cnt, sizeof(Nodes));
	g_links = (Links*)calloc(g_links_cnt, sizeof(Links));
	g_select= (int*)calloc(g_links_cnt, sizeof(int));
	
		//input nodes
	for(i=0; i<g_nodes_cnt; i++){
		scanf("%d%d%d", &useless_var, &g_nodes[i].x, &g_nodes[i].y);
		g_nodes[i].adj_links_cnt = 0;
	}

		//input links
	for(i=0; i<g_links_cnt; i++){
		scanf("%d%d%d", &useless_var, &g_links[i].sender, &g_links[i].receiver);
						g_nodes[g_links[i].sender].adj_links_cnt ++;
						g_nodes[g_links[i].receiver].adj_links_cnt ++;

			//initialize link
		g_links[i].tolerance = GetTransmitPower(g_links[i].sender, g_links[i].receiver) - g_noise;	//tolerance is p/di^3 - Noise, which shows the abality to transmit this link have
		g_links[i].exist = 1;
		g_links[i].select = 0;

			//discard link which don't capable enough to transmit
		if(g_links[i].tolerance <= 0)
			DeleteLink(i);
	}
	/*
						for(i=0; i<g_nodes_cnt; i++){
							printf("%d:%d\n", i, g_nodes[i].adj_links_cnt);
						}
						puts("----");
			for(i=0; i<g_links_cnt; i++){
				if(g_links[i].exist){
					g_links[i].adj_links_cnt = g_nodes[g_links[i].sender].adj_links_cnt + g_nodes[g_links[i].receiver].adj_links_cnt;
						if(g_links[i].adj_links_cnt < min_adj_links_cnt){
								puts("ok");
							min_adj_links_cnt = g_links[i].adj_links_cnt;
							min_adj_links_id = i;
						}
				}
			}
			*/
			/*
						for(i=0; i<g_links_cnt; i++){
							printf("%d:%d\n", i, g_links[i].adj_links_cnt);
							printf("\t%f\n", g_links[i].tolerance);
						}
	
			AddLinkToSolutionSet(min_adj_links_id);
			*/

	/*		original
	for(i=0; i<g_links_cnt; i++){
		if(g_links[i].exist==1 && g_links[i].select==0){	//if this node exist and haven't been selected, chek whether it can be added to solution set
			if(CheckFeasibility(i))	//check whether it can be add to solution set.
				AddLinkToSolutionSet(i);	//if so, add it
		}
	}
	*/
				//new
			while(g_possible_cnt > 100){
				if((next_link=FindMinAdjLink())	!= -1)
				AddLinkToSolutionSet(next_link);
			}
	/*
				if((next_link=FindMinAdjLink())	!= -1)
				AddLinkToSolutionSet(next_link);
				*/

			for(i=0; i<g_links_cnt; i++){
				if(g_links[i].exist==1 && g_links[i].select==0){	//if this node exist and haven't been selected, chek whether it can be added to solution set
					if(CheckFeasibility(i))	//check whether it can be add to solution set.
						AddLinkToSolutionSet(i);	//if so, add it
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
	double distance = sqrt(pow(g_nodes[sender].x-g_nodes[receiver].x, 2) + pow(g_nodes[sender].y-g_nodes[receiver].y, 2));	//((Xsender - Xreceiver)^2 + (Ysender - Yreceiver)^2)^(1/2)
	return g_power/pow(distance, 3.0);
}
void AddLinkToSolutionSet(int id){
	g_select[g_select_cnt++] = id;	//add this link to solution set
	g_links[id].select = 1;				//mark it as being selected
	DeleteNodesOfLink(g_links[id].sender, g_links[id].receiver);
	UpdateTolerance(id);
}
void DeleteNodesOfLink(int end1, int end2){
	for(int i=0; i<g_links_cnt; i++){
			//check all the possible links(exist but haven't been selected), if they use a same node as newly added link, if so, discard it
		if(g_links[i].exist==1 && g_links[i].select==0){
			if(g_links[i].sender==end1||g_links[i].sender==end2 || g_links[i].receiver==end2||g_links[i].receiver==end2){
				DeleteLink(i);
			}
		}
	}
}
void DeleteLink(int link_id){
		//delete a link, and update the value of adjacent_links_count of the nodes this link connect to 
	g_links[link_id].exist = 0;
	g_possible_cnt --;
	g_nodes[g_links[link_id].sender].adj_links_cnt --;
	g_nodes[g_links[link_id].receiver].adj_links_cnt --;
}
void UpdateTolerance(int id){
		//update tolerance of all the exist links(including links in possible links set and solution set)
	for(int i=0; i<g_links_cnt; i++){
		if(g_links[i].exist==1 && i!=id){
			g_links[i].tolerance -= GetTransmitPower(g_links[id].sender, g_links[i].receiver);
			if(g_links[i].tolerance <= 0){		//if this link's SINR value already less or equal to 0, discard it
				DeleteLink(i);
			}
		}
	}
}
int CheckFeasibility(int id){
		//check whether this new_link will break the belence in solution set, if so, discard it
		//return value will be 1 or 0, 1 stand for feasible, 0 otherwise
	for(int i=0; i<g_select_cnt; i++){	//check all the links in solution set
					
			if(g_links[g_select[i]].tolerance <= GetTransmitPower(g_links[id].sender, g_links[g_select[i]].receiver)){  //send from new link to link in solution set
				DeleteLink(id);		//if new link's power is greater than any link in solution set can tolerate, it will break the balance in solution set. So discard new link
				return 0;	//return infeasible
			}
	}
		//if this new link pass all the test in solution set, it is feasible, that is, it can exist with all link in solution set
	return 1;		//return feasible
}
		int FindMinAdjLink(){
			int min_adj_links_cnt = 2147483647;
			int min_adj_links_id = -1;
			while(g_possible_cnt > 100){
						min_adj_links_cnt = 2147483647;
					for(int i=0; i<g_links_cnt; i++){
						if(g_links[i].exist==1 && g_links[i].select==0){	//check the link which exist but haven't been selected
							g_links[i].adj_links_cnt = g_nodes[g_links[i].sender].adj_links_cnt + g_nodes[g_links[i].receiver].adj_links_cnt;	//update the total(combine two nodes) adjacent_links_cnt of this link
							if(g_links[i].adj_links_cnt < min_adj_links_cnt){
								min_adj_links_cnt = g_links[i].adj_links_cnt;
								min_adj_links_id = i;
							}
							else if(g_links[i].adj_links_cnt==min_adj_links_cnt && g_links[i].tolerance > g_links[min_adj_links_id].tolerance){
								min_adj_links_cnt = g_links[i].adj_links_cnt;
								min_adj_links_id = i;
							}
						}
					}
					if(CheckFeasibility(min_adj_links_id))
						return min_adj_links_id;
			}
			return -1;
		}
