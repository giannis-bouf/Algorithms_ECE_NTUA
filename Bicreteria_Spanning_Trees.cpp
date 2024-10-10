/*
Recently, a debate has erupted in the land of Algorithms regarding the usefulness and efficiency of various algorithmic techniques. Among the most 
uncompromising are the supporters of Greed and the supporters of Binary Search. The President of the country is trying to calm things down and explain 
that all techniques are useful and that the efficient solution of complex algorithmic problems usually requires a combination of algorithmic techniques. 
As an example, he proposes the calculation of a spanning tree that maximizes the ratio of the total profit to the total weight of the edges it includes.

More specifically, we consider an undirected connected graph G(V, E) with |V| = N vertices and |E| = M edges. Each edge e offers a profit p(e) and incurs a weight w(e) 
if it is included in the selected spanning tree of G. The goal is to compute a spanning tree T of G that maximizes the ratio {sum_{e in T} p(e)}/{sum_{e in T} w(e)}. 
The President of the country claims that efficiently solving this problem requires a smart combination of algorithmic techniques, and he asks you to write a program 
that confirms this claim.

Input Data:
Your program will initially read from standard input two positive integers, the number N of vertices and the number M of edges of a connected graph. In each of the 
next M lines, four positive integers u(e), v(e), p(e), w(e) will be provided, representing an edge e. The first two integers specify the vertices u(e) and v(e) 
(with u(e) \neq v(e) ) that form the endpoints of edge e. The next two integers specify the profit p(e) and the weight w(e) of edge e.

Output Data:
Your program must print to standard output two integers: the total profit p(T) = sum_{e in T} p(e) and the total weight w(T) = sum_{e in T} w(e) of the spanning tree 
T of G that maximizes the ratio {p(T)}/{w(T)}. Specifically, your program must print the integers {p(T)}/{{gcd}(p(T), w(T))} and {w(T)}/{{gcd}(p(T), w(T))}, separated 
by a space (the division by the greatest common divisor handles the case where there is more than one optimal spanning tree).
*/

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

int gcd(int a, int b) {
    if (b == 0) {
        return a;
    }
    return gcd(b, a % b);
}

// DSU data structure
// path compression + rank by union
class DSU {
    int* parent;
    int* rank;

public:
    DSU(int n)
    {
        parent = new int[n];
        rank = new int[n];

        for (int i = 0; i < n; i++) {
            parent[i] = -1;
            rank[i] = 1;
        }
    }

    // Find function
    int find(int i)
    {
        if (parent[i] == -1)
            return i;

        return parent[i] = find(parent[i]);
    }

    // Union function
    void unite(int x, int y)
    {
        int s1 = find(x);
        int s2 = find(y);

        if (s1 != s2) {
            if (rank[s1] < rank[s2]) {
                parent[s1] = s2;
            }
            else if (rank[s1] > rank[s2]) {
                parent[s2] = s1;
            }
            else {
                parent[s2] = s1;
                rank[s1] += 1;
            }
        }
    }
};

struct Edge {
    int u, v; float profit, weight;

    // Comparator function for sorting edges based on weight
    bool operator>(const Edge& other) const {
        return profit > other.profit;
    }

    bool operator<(const Edge& other) const {
        return weight < other.weight;
    }
};

bool compare(Edge e1, Edge e2, float c) {
    return (e1.profit - c*e1.weight > e2.profit - c*e2.weight);
}

class Graph {
public:
    vector<Edge> edgelist;
    int V;

    Graph(int V) { this->V = V; }

    // Function to add edge in a graph
    void addEdge(int x, int y, float p, float w) {
        Edge edge = {x, y, p, w};
        edgelist.push_back(edge);
    }

    float mst_max_profit() {
        // Sort all edges
        sort(edgelist.begin(), edgelist.end(), greater<Edge>());

        // Initialize the DSU
        DSU s(V);
        float ans = 0;
        for (auto edge : edgelist) {

            // Take this edge in MST if it does
            // not forms a cycle
            if (s.find(edge.u) != s.find(edge.v)) {
                s.unite(edge.u, edge.v);
                ans += (float)edge.profit;
            }
        }
        return ans;
    }

    float mst_min_weight() {
        // Sort all edges
        sort(edgelist.begin(), edgelist.end(), less<Edge>());

        // Initialize the DSU
        DSU s(V);
        float ans = 0;
        for (auto edge : edgelist) {
            // Take this edge in MST if it does
            // not forms a cycle
            if (s.find(edge.u) != s.find(edge.v)) {
                s.unite(edge.u, edge.v);
                ans += (float)edge.weight;
            }
        }
        return ans;
    }
};

void kruskals_mst(Graph g) {
    float left = 0, right = g.mst_max_profit()/g.mst_min_weight();
    float mid;
    float term_profits=0, term_weights=0;
    while (right - left > 0.1) {
        mid = (left + right) / 2;
        // Sort all edges
        sort(g.edgelist.begin(), g.edgelist.end(), [mid](const Edge& e1, const Edge& e2) {
            return compare(e1, e2, mid);
        });

        // Initialize the DSU
        DSU s(g.V);
        float profits = 0, weights = 0;
        for (auto edge : g.edgelist) {
            // Take this edge in MST if it does
            // not forms a cycle
            if (s.find(edge.u) != s.find(edge.v)) {
                s.unite(edge.u, edge.v);
                profits += edge.profit, weights += edge.weight;
            }
        }
        term_profits = profits, term_weights = weights;
        if (profits - mid*weights > 0) left = mid;
        else right = mid;
    }
    int gcd_value = gcd((int)term_profits, (int)term_weights);
    cout <<  term_profits/gcd_value << " " << term_weights/gcd_value << endl;
}

// Driver code
int main()
{
    int n, m;
    cin >> n >> m;
    Graph graph(n+1);

    // Add edges to the graph with weight and profit
    for (int i=0; i<m; i++) {
        int u, v; float p, w;
        cin >> u >> v >> p >> w;
        graph.addEdge(u, v, p, w);
    }

    kruskals_mst(graph);

    return 0;
}
