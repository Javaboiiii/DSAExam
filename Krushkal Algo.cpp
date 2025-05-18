// 19.	Write a Program to implement Kruskal's algorithm to find minimum 
// spanning tree of a user defined graph. Use Adjacency Matrix/ List to 
// represent a graph.

#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

// Structure to represent an edge
struct Edge {
    int src, dest, weight;
    
    // Constructor
    Edge(int s, int d, int w) : src(s), dest(d), weight(w) {}
    
    // For sorting edges based on weight
    bool operator<(const Edge& other) const {
        return weight < other.weight;
    }
};

// Class for Disjoint Set Union (DSU)
class DisjointSet {
private:
    vector<int> parent, rank;
    
public:
    // Constructor
    DisjointSet(int n) {
        parent.resize(n);
        rank.resize(n, 0);
        
        // Initially, each vertex is its own parent
        for (int i = 0; i < n; i++) {
            parent[i] = i;
        }
    }
    
    // Find the parent of a vertex with path compression
    int find(int x) {
        if (parent[x] != x) {
            parent[x] = find(parent[x]);
        }
        return parent[x];
    }
    
    // Union of two sets by rank
    void unionSets(int x, int y) {
        int rootX = find(x);
        int rootY = find(y);
        
        if (rootX == rootY) return;
        
        // Union by rank
        if (rank[rootX] < rank[rootY]) {
            parent[rootX] = rootY;
        } else if (rank[rootX] > rank[rootY]) {
            parent[rootY] = rootX;
        } else {
            parent[rootY] = rootX;
            rank[rootX]++;
        }
    }
};

// Function to find MST using Kruskal's algorithm
void kruskalMST(vector<vector<int>>& graph, int V) {
    vector<Edge> edges;
    
    // Add all edges to the edges list
    for (int i = 0; i < V; i++) {
        for (int j = i + 1; j < V; j++) {
            if (graph[i][j] != 0) {
                edges.push_back(Edge(i, j, graph[i][j]));
            }
        }
    }
    
    // Sort edges by weight
    sort(edges.begin(), edges.end());
    
    // Create disjoint sets
    DisjointSet ds(V);
    
    vector<Edge> result;
    int totalWeight = 0;
    
    // Process edges in ascending order of weight
    for (const Edge& edge : edges) {
        int u = edge.src;
        int v = edge.dest;
        
        // If including this edge doesn't form a cycle
        if (ds.find(u) != ds.find(v)) {
            result.push_back(edge);
            totalWeight += edge.weight;
            ds.unionSets(u, v);
        }
    }
    
    // Print the MST
    cout << "Edges in the Minimum Spanning Tree:\n";
    for (const Edge& edge : result) {
        cout << "(" << edge.src << " - " << edge.dest << "): " << edge.weight << endl;
    }
    
    cout << "Total weight of MST: " << totalWeight << endl;
}

int main() {
    int V;
    cout << "Enter the number of vertices: ";
    cin >> V;
    
    vector<vector<int>> graph(V, vector<int>(V, 0));
    
    cout << "Enter the adjacency matrix (0 for no edge):\n";
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            cin >> graph[i][j];
        }
    }
    
    kruskalMST(graph, V);
    
    return 0;
}