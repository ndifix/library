#include <bits/stdc++.h>
#define inf 1e9
#define mod 1e9+7
int StringToInt(std::string s){
	int ret=0;	if(s.size()>9||s.size()==0) return 0;
	for(int i=0; i<s.size(); i++)
		if(s[i]<'0' && s[i]>'9') return 0;
	ret=s[0]-'0';
	for(int i=1; i<s.size(); i++){	ret*=10;	ret+=s[i]-'0';	}
	return ret;	} //string型をint型に変換
std::string ExtractString(std::string s, int begin, int end){
	std::string t;
	for(int i=begin; i<end; i++) t+=s[i];
	return t; }// [beg, end)を抽出
struct gragh{
	int V,E;
	std::vector<std::vector<std::pair<int,int>>> edge; //edge[from][i] ={to,cost}
	//only for 0-indexed 
	gragh(int v,int e,int *from,int *to,int *cost){
		V=v;E=e;	std::pair<int,int>p;
		for(int i=0;i<e;i++){
			//if(edge.size()<=from[i])edge.resize(from[i]+1);
			edge.resize(v);
			p.first=to[i];	p.second=cost[i];	edge[from[i]].push_back(p);
			p.first=from[i]; p.second=cost[i];	edge[to[i]].push_back(p);
		} }
	int dijkstra(int start,int goal){
		int done[V];	for(int i=0;i<V;i++)done[i]=0;	done[start]=1;
		int vertex[V];	for(int i=0;i<V;i++)vertex[i]=inf;	vertex[start]=0;
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
	int bellmanFord(){

	}};