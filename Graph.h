#ifndef GRAPH_H_INCLUDED
#define GRAPH_H_INCLUDED

#include <vector>
#include <unordered_map>
#include <iostream>
#include <algorithm>
using namespace std;

struct Edge{
    int src,dest,weight=1;
};

class Graph{
    public:
        int V,E;
        vector<vector<pair<int,int>>> adjList;
        unordered_map<int,int> parent;

        Graph(int,int);
        void udirGraph(vector<Edge>);
        void dirGraph(vector<Edge>);
        void printGraph();
        void DFS(int);
        void BFS(int);

};

Graph::Graph(int V,int E){
    this->V = V;
    this->E = E;
}

void Graph::udirGraph(vector<Edge> edges){
    adjList.resize(V);
    for(auto edge:edges){
        adjList.at(edge.src).emplace_back(edge.dest,edge.weight);
        adjList.at(edge.dest).emplace_back(edge.src,edge.weight);
    }
    for(int i=0;i<V;i++){
        sort(adjList[i].begin(),adjList[i].end());
    }
}

void Graph::dirGraph(vector<Edge> edges){
    adjList.resize(V);
    for(auto edge:edges){
        adjList.at(edge.src).emplace_back(edge.dest,edge.weight);
    }
    for(int i=0;i<V;i++){
        sort(adjList[i].begin(),adjList[i].end());
    }
}

void Graph::printGraph(){
    for(int i=0;i<V;++i){
        cout << i << " -> ";
        for(auto x:adjList[i]){
            cout << "(" << x.first << "," << x.second << ") ";
        }
        cout << endl;
    }
}

void Graph::DFS(int start){
    cout << start << " ";
    parent.emplace(start,NULL);
    for(auto x : adjList[start]){
        if(parent.find(x.first) == parent.end()){
            parent.emplace(x.first,start);
            DFS(x.first);
        }
    }
}

void Graph::BFS(int start){
    unordered_map<int,int> height;
    height.emplace(start,0);
    parent.emplace(start,NULL);

    vector<int> sameLevel,next; int i=1;
    sameLevel.emplace_back(start);

    while(!sameLevel.empty()){
        next.clear();
        for(auto u: sameLevel){
            for(auto v : adjList[u]){
                if(height.find(v.first) == parent.end()){
                    parent.emplace(v.first,u);
                    height.emplace(v.first,i);
                    next.push_back(v.first);
                }
            }
        }
        sameLevel = next; ++i;
    }
        unordered_map<int, int>::iterator itr;
        for (itr = height.begin(); itr != height.end(); ++itr) {
            cout << itr->first << " - " << itr->second << endl;
        }
}

#endif // GRAPH_H

