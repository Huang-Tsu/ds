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
		int adj_cnt;
}*g_nodes;
struct Links{
	int exist;
	int select;
	int sender;
	int receiver;
	int adj_cnt;
	double affectance;
	double tolerance;
}*g_links;

int g_nodes_cnt, g_links_cnt, g_noise;
int g_possible_cnt;
double g_power;
int *g_select;
int g_select_cnt = 0;

int CheckFeasibility(int id);
void UpdateTolerance(int new_link_id);
void AddLinkToSolutionSet(int id);
void DeleteNode(int end1, int end2);
int FindMinAffectLink();
double GetTransmitPower(int sender, int receiver);

int main(){
	int useless_var;
	int min_adj_cnt = INT_MAX;
	int min_adj_cnt_id;
	int max_tolerance = 0;
	int max_tolerance_id;
	int next_link;
	int i;

	scanf("%d%d%lf%d", &g_nodes_cnt, &g_links_cnt, &g_power, &g_noise);
	g_possible_cnt = g_links_cnt;
		//alocate memory space for nodes, links, and solution set
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
			//initialize link
		g_links[i].tolerance = GetTransmitPower(g_links[i].sender, g_links[i].receiver) - g_noise;	//tolerance is p/di^3 - Noise, which shows the abality to transmit this link have
		g_links[i].exist = 1;
		g_links[i].select = 0;
		g_links[i].affectance = 0;
				g_nodes[g_links[i].sender].adj_cnt ++;
				g_nodes[g_links[i].receiver].adj_cnt ++;

			//discard link which don't capable enough to transmit
		if(g_links[i].tolerance <= 0){
			g_links[i].exist = 0;
			g_possible_cnt --;
				g_nodes[g_links[i].sender].adj_cnt --;
				g_nodes[g_links[i].receiver].adj_cnt --;
		}
	}
		
	for(i=0; i<g_links_cnt; i++){
		if(g_links[i].exist){
			g_links[i].adj_cnt = g_nodes[g_links[i].sender].adj_cnt + g_nodes[g_links[i].receiver].adj_cnt;
			if(g_links[i].adj_cnt < min_adj_cnt){
				min_adj_cnt = g_links[i].adj_cnt;
				min_adj_cnt_id = i;
			}
			/*
			else if(g_links[i].adj_cnt == min_adj_cnt){
				if(g_links[i].tolerance > g_links[min_adj_cnt_id].tolerance){
					min_adj_cnt = g_links[i].adj_cnt;
					min_adj_cnt_id = i;
				}
			}
			*/
		}
	}
		
	AddLinkToSolutionSet(min_adj_cnt_id);
	
	while(g_possible_cnt>0){
		/*
						for(i=0; i<g_links_cnt; i++){
							printf("%d:tol:%f, affect:%f, adj:%d\n", i, g_links[i].tolerance, g_links[i].affectance, g_links[i].adj_cnt);
						}
						*/
		next_link = FindMinAffectLink();
		if(next_link != -1){
				AddLinkToSolutionSet(next_link);
		}
	}
	/*
	for(i=0; i<g_links_cnt; i++){
		if(g_links[i].exist==1 && g_links[i].select==0){	//if this node exist and haven't been selected, chek whether it can be added to solution set
			if(CheckFeasibility(i))	//check whether it can be add to solution set.
				AddLinkToSolutionSet(i);	//if so, add it
		}
	}
	*/

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
	g_possible_cnt --;
	DeleteNode(g_links[id].sender, g_links[id].receiver);
	UpdateTolerance(id);
}
void DeleteNode(int end1, int end2){
	for(int i=0; i<g_links_cnt; i++){
			//check all the possible links(exist but haven't been selected), if they use a same node as newly added link, if so, discard it
		if(g_links[i].exist==1 && g_links[i].select==0){
			if(g_links[i].sender==end1||g_links[i].sender==end2 || g_links[i].receiver==end2||g_links[i].receiver==end2){
				g_links[i].exist = 0;
				g_possible_cnt --;
				g_nodes[g_links[i].sender].adj_cnt --;
				g_nodes[g_links[i].receiver].adj_cnt --;
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
				g_possible_cnt --;
				g_nodes[g_links[i].sender].adj_cnt --;
				g_nodes[g_links[i].receiver].adj_cnt --;
			}
				//update affectance of exist but not select link
			else if(g_links[i].select==0){
				g_links[i].affectance += GetTransmitPower(g_links[i].sender, g_links[id].receiver);	//compute how much newly selected link will be affect by this link
			}
				
		}
	}
}
int FindMinAffectLink(){
		//find a link with minimal affectance in possible link set
		//it will be the next link to be add to solution set
		//because we want to minimize the affectance to links in solution set
	int min_affectance_id;
	double min_affectance = (double)INT_MAX;
	int min_adj_cnt = INT_MAX;
	int min_adj_cnt_id;
	while(g_possible_cnt>0){
				min_adj_cnt = INT_MAX;
				min_adj_cnt_id = -1;
		for(int i=0; i<g_links_cnt; i++){
					if(g_links[i].exist && g_links[i].select==0){
						g_links[i].adj_cnt = g_nodes[g_links[i].sender].adj_cnt + g_nodes[g_links[i].receiver].adj_cnt;
						if(g_links[i].adj_cnt < min_adj_cnt){
							min_adj_cnt = g_links[i].adj_cnt;
							min_adj_cnt_id = i;
						}
						/*
						else if(g_links[i].adj_cnt == min_adj_cnt){
							if(g_links[i].affectance < g_links[min_adj_cnt_id].affectance){
								min_adj_cnt = g_links[i].adj_cnt;
								min_adj_cnt_id = i;
							}
						}
						*/
					}
					/*
			if(g_links[i].exist==1 && g_links[i].select==0){	//if this link exists and haven't been selected, and is not new node, then check it
				if(g_links[i].affectance < min_affectance){
					min_affectance = g_links[i].affectance;
					min_affectance_id = i;
				}
				else if(g_links[i].affectance == min_affectance){
					if(g_links[i].adj_cnt < g_links[min_affectance_id].adj_cnt){
						min_affectance = g_links[i].affectance;
						min_affectance_id = i;
					}
				}
			}
			*/
		}
			//check whether this link is feasible in solution set. If so, return it's id. If not, find link with minimal again
		if(min_adj_cnt == -1)
			return -1;
		if(CheckFeasibility(min_adj_cnt_id))
			return min_adj_cnt_id;
	}
	return -1;	
}
/*
void UpdateAffectance(int id){
		//update affectance of links in possible links set after adding a new link into solution set
		//the affected degree of newly selected link by link[i] is computed by the transmit power from link[i]'s sender to newly selected link's receiver
	for(int i=0; i<g_links_cnt_total; i++){
					if(g_links[i].run == 0){
		if(g_links[i].exist==1 && g_links[i].select==0){	//if this link exists and haven't been selected, then update
			//the affected degree of newly selected link by link[i] is computed by the transmit power from link[i]'s sender to newly selected link's receiver
			g_links[i].affectance += GetTransmitPower(g_links[i].sender, g_links[new_link_id].receiver);	//compute how much newly selected link will be affect by this link
					for(int j=i; j<g_links_cnt_total; j++){
						if(g_links[j].sender == g_links[i].sender){
							g_links[j].affectance = g_links[i].affectance;
							g_links[j].run = 1;
						}
					}
					//fprintf(stderr, "link:%d, affectance:%f\n", i, g_links[i].affectance);
		}
					}
							g_links[i].run = 0;
	}
}
*/
int CheckFeasibility(int id){
		//check whether this new_link will break the belence in solution set, if so, discard it
		//return value will be 1 or 0, 1 stand for feasible, 0 otherwise
	for(int i=0; i<g_select_cnt; i++){	//check all the links in solution set
					
			if(g_links[g_select[i]].tolerance <= GetTransmitPower(g_links[id].sender, g_links[g_select[i]].receiver)){  //send from new link to link in solution set
				g_links[id].exist = 0;		//if new link's power is greater than any link in solution set can tolerate, it will break the balance in solution set. So discard new link
				g_possible_cnt --;
				g_nodes[g_links[i].sender].adj_cnt --;
				g_nodes[g_links[i].receiver].adj_cnt --;
				return 0;	//return infeasible
			}
	}
		//if this new link pass all the test in solution set, it is feasible, that is, it can exist with all link in solution set
	return 1;		//return feasible
}
