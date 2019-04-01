#include "Graph.h"
#include <climits>
using namespace std;

int FordFulkerson(Graph *g1,int src,int sink){
    int maxFlow = 0, flag=1;
    while(!((*g1).parent.find(sink) == (*g1).parent.end())||flag){
       flag=0;
       (*g1).BFS(src);
      int pathFlow = INT_MAX;
      for (auto itr = (*g1).parent.begin(); itr != (*g1).parent.end(); ++itr) {
           int wt=0, u = itr->second, v = itr->first;
           for(auto x: (*g1).adjList[u]) {if(x.first == v ){wt = x.second; break;}} // Just to find weight of Edge u -> v.
           pathFlow = min(pathFlow,wt);
       }

       for (auto itr = (*g1).parent.begin(); itr != (*g1).parent.end(); ++itr) {
           int u = itr->second, v = itr->first;
           for(auto x=(*g1).adjList[u].begin();x!=(*g1).adjList[u].end();x++) {if((*x).first == v ){(*x).second-=pathFlow; break;}}
           for(auto x=(*g1).adjList[v].begin();x!=(*g1).adjList[v].end();x++){if((*x).first == u ){(*x).second+=pathFlow; break;}}
       }
       maxFlow+=pathFlow;
     }
    return maxFlow;
}

int main(){
    vector<Edge> edges =
    {
      {0,1,3},{0,2,2},{2,1,3},{1,3,2},{2,4,3},{3,2,1},{3,5,3},{4,3,3},{4,5,2}      // Weight is the flow capacity of an edge.
    };
    Graph g1(6,9);

    g1.adjList.resize(g1.V);
    for(auto edge:edges){
        g1.adjList.at(edge.src).emplace_back(edge.dest,edge.weight);
        g1.adjList.at(edge.dest).emplace_back(edge.src,0);
    }
    for(int i=0;i<g1.V;i++){
        sort(g1.adjList[i].begin(),g1.adjList[i].end());
    }
    cout << FordFulkerson(&g1,0,5);
    return 0;
}
