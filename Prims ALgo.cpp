#include <iostream> 
#include <vector> 
#include <queue>

// 17.	Write a Program to implement Prim’s algorithm to find 
// minimum spanning tree of a user defined graph. Use Adjacency Matrix/List
//  to represent a graph.

using namespace std; 

int primAlgo(int V, vector<vector<pair<int, int>>> adjL, int startNode) { 
    int visited[V] = {0}; 
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>> > pq; 

    int sum = 0; 

    // weight, node 
    pq.push({0, startNode}) ; 

    while(!pq.empty()) { 
        pair<int, int> qnode = pq.top();  
        pq.pop(); 
        
        int node = qnode.second; 
        int wt = qnode.first;  

        if(visited[node] == 1) continue; 

        visited[node] = 1; 

        sum += wt; 

        for(auto it : adjL[node]) {  
            int adjNode = it.first; 
            int adjW = it.second; 

            if(visited[adjNode] != 1) pq.push({adjW, adjNode}); 
        }

        
    }

    return sum;

}

int main() { 
    int V = 5; // Number of vertices

    // Initialize adjacency list
    vector<vector<pair<int, int>>> adjL(V);

    // Add edges (u, v, weight)
    adjL[0].push_back({1, 2}); // Edge 0-1 with weight 2
    adjL[0].push_back({3, 6}); // Edge 0-3 with weight 6
    adjL[1].push_back({0, 2}); // Edge 1-0 with weight 2
    adjL[1].push_back({2, 3}); // Edge 1-2 with weight 3
    adjL[1].push_back({3, 8}); // Edge 1-3 with weight 8
    adjL[1].push_back({4, 5}); // Edge 1-4 with weight 5
    adjL[2].push_back({1, 3}); // Edge 2-1 with weight 3
    adjL[2].push_back({4, 7}); // Edge 2-4 with weight 7
    adjL[3].push_back({0, 6}); // Edge 3-0 with weight 6
    adjL[3].push_back({1, 8}); // Edge 3-1 with weight 8
    adjL[4].push_back({1, 5}); // Edge 4-1 with weight 5
    adjL[4].push_back({2, 7}); // Edge 4-2 with weight 7

    int startNode = 0; // Starting node for Prim's algorithm

    cout << "Minimum Spanning Tree Weight: " << primAlgo(V, adjL, startNode) << endl;

    return 0;
}