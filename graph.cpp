#include <vector>
#include <algorithm>
#include <queue>

struct gragh{
	int V,E;
	std::vector<std::vector<std::pair<int,int>>> edge; //edge[from][i] ={to,cost}
	//only for 0-indexed
    std::vector<std::vector<int>> table;
	gragh(int v,int e,int *from,int *to,int *cost){
		V=v;E=e;	std::pair<int,int>p;
		for(int i=0;i<e;i++){
			//if(edge.size()<=from[i])edge.resize(from[i]+1);
			edge.resize(v);
			p.first=to[i];	p.second=cost[i];	edge[from[i]].push_back(p);
			p.first=from[i]; p.second=cost[i];	edge[to[i]].push_back(p);//無向グラフ
		} }
	int dijkstra(int start,int goal){
		int done[V];	for(int i=0;i<V;i++)done[i]=0;	done[start]=1;
		int vertex[V];	for(int i=0;i<V;i++)vertex[i]=1000000000;	vertex[start]=0;
		std::queue<int> que;	que.push(start);
		int from, to, cost;
		while(que.size()!=0){
			from=que.front();
			for(int i=0; i<edge[from].size(); i++){
				to=edge[from][i].first;	cost=edge[from][i].second;
				if( vertex[to]>vertex[from]+cost){
					vertex[to]=vertex[from]+cost;
					que.push(to);
				}
			}
			que.pop();
		}
		return vertex[goal];	}
    void init_table(){
        table.resize(V);for(int i=0;i<V;i++)table[i].resize(V);
        for(int i=0;i<V;i++)for(int j=0;j<V;j++)table[i][j]=1000000000;
        for(int i=0;i<V;i++)table[i][i]=0;
        for(int i=0;i<edge.size();i++){
        for(int j=0;j<edge[i].size();j++){
            table[i][edge[i][j].first] = edge[i][j].second;
        }}
        
        for(int k=0;k<V;k++)
        for(int i=0;i<V;i++)
        for(int j=0;j<V;j++)
            table[i][j] = std::min(table[i][j], table[i][k]+table[k][j]);
    }
    int W(int s,int g){
        if(table.size()==0)init_table();

    }
	int bellmanFord(){

	}
    };