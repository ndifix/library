#include <vector>
#include <algorithm>
#include <queue>

namespace ndifix{

class Gragh{
	int V,E;
	std::vector<std::vector<std::pair<int,int>>> edge; //edge[from][i] ={to,cost}
	//only for 0-indexed
    std::vector<std::vector<int>> table;
	Gragh(int v,int e,int *from,int *to,int *cost){
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

class Node{
		public:
	int id, parent;
	long long sum;
	int max,min;
	int val;
  std::vector<int> childs;
	/*
	Node(int v){val=v;id=parent=sum=0;}
	Node(){val=0;id=parent=sum=0;}
	int lbound(int key){int s=0,e=childs.size();int mid;while(e-s>2){mid=(e+s)/2;if(childs[mid] < key)s=mid;else if(childs[mid] > key)e=mid;else if(childs[mid]==key)e=mid+1;}if(childs[s]>=key)return s;if(childs[s+1]>=key)return s+1;return s+2;}
  void chid(int n){id=n;}
  void chpar(int n){parent=n;}
  void addchld(int n){childs.push_back(n);std::sort(childs.begin(),childs.end());}
	void erasechld(int n){if(childs[lbound(n)]!=n)return;childs.erase(childs.begin()+lbound(n));}
	*/
};

class SegmentTree{
		private:
	int size, rank;
	std::vector<std::vector<Node>> nodes;
		public:
	SegmentTree(){}
	SegmentTree(int s){size=s;nodes.resize(1);nodes[0].resize(s);shrink();}
	SegmentTree(std::vector<Node> data){size=data.size();nodes.push_back(data);shrink();reset(0,nodes[0].size());}
	void shrink(){
		std::vector<ndifix::Node> buf;buf.resize(nodes[0].size());
		while(buf.size()!=1){
			buf.resize(buf.size()/2 + !!(buf.size()%2));nodes.push_back(buf);
		}
		rank=nodes.size();
	}
	void reset(int th){
		nodes[0][th].min=nodes[0][th].max=nodes[0][th].sum=nodes[0][th].val;th/=2;
		for(int i=1;i<rank;i++){
			nodes[i][th].min=(2*th+1>=nodes[i-1].size()?nodes[i-1][2*th].min:std::min(nodes[i-1][2*th].min,nodes[i-1][2*th+1].min));
			nodes[i][th].max=(2*th+1>=nodes[i-1].size()?nodes[i-1][2*th].max:std::max(nodes[i-1][2*th].max,nodes[i-1][2*th+1].max));
			nodes[i][th].sum=(2*th+1>=nodes[i-1].size()?nodes[i-1][2*th].sum:nodes[i-1][2*th].sum+nodes[i-1][2*th+1].sum);
			th/=2;
		}
		rank=nodes.size();
	}
	void reset(int s,int e){//[s,e)
		for(int j=s;j<e;j++)nodes[0][j].min=nodes[0][j].max=nodes[0][j].sum=nodes[0][j].val;
		s/=2;e=(e/2)+!!(e%2);
		for(int i=1;i<rank;i++){
			for(int j=s;j<e;j++){
				nodes[i][j].min=(2*j+1>=nodes[i-1].size()?nodes[i-1][2*j].min:std::min(nodes[i-1][2*j].min,nodes[i-1][2*j+1].min));
				nodes[i][j].max=(2*j+1>=nodes[i-1].size()?nodes[i-1][2*j].max:std::max(nodes[i-1][2*j].max,nodes[i-1][2*j+1].max));
				nodes[i][j].sum=(2*j+1>=nodes[i-1].size()?nodes[i-1][2*j].sum:nodes[i-1][2*j].sum+nodes[i-1][2*j+1].sum);
			}
			s/=2;e=(e/2)+!!(e%2);
		}
		rank=nodes.size();
	}
	void chnode(int th,int n){nodes[0][th].val=n;}

	void print(){for(int i=0;i<rank;i++){for(int j=0;j<nodes[i].size();j++){std::cout<<nodes[i][j]<<"   ";}std::cout<<endl;}}
};

}//end of namespace
