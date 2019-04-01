#include "Graph.h"
using namespace std;

void altDFS(Graph *g1,int v,vector<int> *vec){
    for(auto x : (*g1).adjList[v]){
        if((*g1).parent.find(x.first) == (*g1).parent.end()){
            (*g1).parent.emplace(x.first,v);
            altDFS(g1,x.first,vec);
        }
    }
    (*vec).insert((*vec).begin(),v);

}

void topSort(Graph g1){
    vector<int> revCompOrder;
    for(int i=0; i<g1.V; ++i){
        if(g1.parent.find(i) == g1.parent.end()){
            g1.parent.emplace(i,NULL);
            altDFS(&g1,i,&revCompOrder);}
    }
    for(auto x:revCompOrder){
        cout << x << " ";
    }
}

int main(){
    vector<Edge> edges =
    {
      {2,3},{3,1},{4,0},{4,1},{5,0},{5,2}
    };
    Graph g1(6,6);
    g1.dirGraph(edges);
    topSort(g1);
    return 0;
}
