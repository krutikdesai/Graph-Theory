#include "Graph.h"
#include <climits>
#include <set>
#include <utility>

using namespace std;

void Dijkstra(Graph g1,int start){
    set<pair<int,int>> sdist;
    vector<int> dist(g1.V,INT_MAX);

    sdist.emplace(0,start);
    dist[start]=0;

    while(!sdist.empty()){
        int u = (*sdist.begin()).second;
        sdist.erase(sdist.begin());

        for(auto x : g1.adjList[u]){
                int v = x.first, weight = x.second;
            if(dist[v] > dist[u] + weight){
                if(dist[v]!= INT_MAX) {sdist.erase(sdist.find(make_pair(dist[v],v)));}
                dist[v] = dist[u] + weight;
                sdist.emplace(dist[v],v);
            }
        }
    }
    for(auto x:dist) {cout << x << endl;}
}

int main(){
    vector<Edge> edges =
    {
      {0,1,4},{0,7,8},{1,2,8},{1,7,11},{2,3,7},{2,8,2},{2,5,4},{3,4,9},{3,5,14},{4,5,10},{5,6,2},{6,7,1},{6,8,6},{7,8,7}
    };
    Graph g1(9,14);
    g1.udirGraph(edges);
    Dijkstra(g1,0);
    return 0;
}
