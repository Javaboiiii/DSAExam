// 18.	Write a Program to implement Dijkstra’s algorithm to find shortest 
// distance between two nodes of a user defined graph. Use Adjacency
//  Matrix/List to represent a graph.

#include <iostream> 
#include <vector>
#include <climits>
#include <queue>

using namespace std;

vector<int> djisktraAlgo(vector<vector<pair<int, int>>> adjL, int startNode, int n) { 
    vector<int> ans(n, INT_MAX);  

    // wt, node 
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;  

    pq.push({0, startNode}); 
    ans[0] = 0; 

    while(!pq.empty()) { 
        auto it = pq.top(); 

        int node = it.second; 
        int wt = it.first; 

        pq.pop();

        if(ans[node] < wt) continue;

        for(auto it : adjL[node]) {  
            int adjNode = it.first; 
            int adjwt = it.second; 

            int finalwt = adjwt + wt; 

            if(ans[adjNode] > finalwt) { 
                ans[adjNode] = finalwt; 
                pq.push({finalwt, adjNode}); 
            }
        }

    }

    return ans; 

}

int main() { 
    int n = 5; // Number of nodes

    // Initialize adjacency list
    vector<vector<pair<int, int>>> adjL(n);

    // Add edges (u, v, weight)
    adjL[0].push_back({1, 2}); // Edge 0 -> 1 with weight 2
    adjL[0].push_back({3, 6}); // Edge 0 -> 3 with weight 6
    adjL[1].push_back({2, 3}); // Edge 1 -> 2 with weight 3
    adjL[1].push_back({3, 8}); // Edge 1 -> 3 with weight 8
    adjL[1].push_back({4, 5}); // Edge 1 -> 4 with weight 5
    adjL[2].push_back({4, 7}); // Edge 2 -> 4 with weight 7
    adjL[3].push_back({4, 9}); // Edge 3 -> 4 with weight 9

    int startNode = 0; // Starting node for Dijkstra's algorithm

    // Call Dijkstra's algorithm
    vector<int> shortestDistances = djisktraAlgo(adjL, startNode, n);

    // Print the shortest distances from the start node
    cout << "Shortest distances from node " << startNode << ":\n";
    for (int i = 0; i < n; i++) {
        cout << "Node " << i << ": " << shortestDistances[i] << endl;
    }

    return 0;
}