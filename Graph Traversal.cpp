// 15.	Write a Program to accept a graph (directed or undirected) from user and 
// represent it with Adjacency Matrix and perform BFS and DFS traversals on it.

#include <iostream> 
#include <queue> 

using namespace std; 

void bfs(int** adjM, int startNode, int n) {  
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
            for(int j = 0; j < n; j ++) { 
                if(adjM[node][j] == 1 && visited[j] != 1) { 
                    q.push(j); 
                    visited[j] = 1; 
                }
            }
        }
    }   
}

void dfs(int** adjM, int startNode, int n, vector<int>& visited, int currNode) {   
    if(currNode == -1) { 
        currNode = startNode; 
    }
    
    visited[currNode] = 1;  

    cout << currNode << " "; 
    for(int i = 0; i < n; i ++) { 
        if(adjM[currNode][i] && visited[i] != 1)
            dfs(adjM, startNode, n, visited, i); 
    }
}


int main() {
    int n = 4; // Number of nodes

    // Dynamically allocate adjacency matrix
    int** adjM = new int*[n];
    for (int i = 0; i < n; i++) {
        adjM[i] = new int[n];
    }

    // Initialize adjacency matrix
    int temp[4][4] = {
        {0, 1, 1, 0}, 
        {1, 0, 0, 1}, 
        {1, 0, 0, 1}, 
        {0, 1, 1, 0}  
    };

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            adjM[i][j] = temp[i][j];
        }
    }

    int startNode = 0;

    cout << "BFS Traversal: ";
    bfs(adjM, startNode, n); 
    cout << endl;

    cout << "DFS Traversal: ";
    vector<int> visited(n, 0); 
    dfs(adjM, startNode, n, visited, -1); 
    cout << endl;

    for (int i = 0; i < n; i++) {
        delete[] adjM[i];
    }
    delete[] adjM;

    return 0;
}