#include <iostream> 
#include <queue> 

using namespace std; 

// 15.	Write a Program to accept a graph (directed or undirected) from user 
// and represent 
// it with Adjacency List and perform BFS and DFS traversals on it.

void bfs(vector<vector<int>> adjL, int startNode, int n) { 
    queue<int> q; 
    int visited[n] = {0}; 

    q.push(startNode); 

    visited[startNode] = 1; 

    while(!q.empty()) { 
        int size = q.size(); 
        for(int i = 0; i < size; i ++) { 
            int node = q.front(); 
            q.pop(); 
            cout << node << " "; 
            for(auto it : adjL[node]) { 
                if(visited[it] != 1) { 
                    q.push(it); 
                    visited[it] = 1; 
                }
            }
        }
    }
}

void dfs(vector<vector<int>> adjL, vector<int>& visited, int currNode) {  
    visited[currNode] = 1; 

    cout << currNode << " "; 

    for(auto it : adjL[currNode]) { 
        if(visited[it] != 1) dfs(adjL, visited, it); 
    }
}

int main() { 
    int n = 4; // Number of nodes

    // Initialize adjacency list
    vector<vector<int>> adjL(n);
    adjL[0] = {1, 2}; // Node 0 is connected to Node 1 and Node 2
    adjL[1] = {0, 3}; // Node 1 is connected to Node 0 and Node 3
    adjL[2] = {0, 3}; // Node 2 is connected to Node 0 and Node 3
    adjL[3] = {1, 2}; // Node 3 is connected to Node 1 and Node 2

    int startNode = 0; // Starting node for traversal

    cout << "BFS Traversal: ";
    bfs(adjL, startNode, n); 
    cout << endl;

    cout << "DFS Traversal: ";
    vector<int> visited(n, 0); 
    dfs(adjL, visited, startNode); 
    cout << endl;

    return 0;
}