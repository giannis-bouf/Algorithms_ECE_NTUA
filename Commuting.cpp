/*
In the distant Land of Algorithms, there are N cities connected by M bidirectional avenues. Each avenue connects two cities. The movement along the avenues 
is so fast that we can consider it instantaneous! Thus, it is common for residents to live in a different city from the one where they work.

The avenues are old and require daily maintenance, resulting in their closure after a certain time. We know that the i-th avenue closes for maintenance 
at time tᵢ > 0, and thus can be used for travel only during the time intervals t ∈ [0, tᵢ]. Of course, the avenues are designed so that at time 0, everyone can get to work.

You have been assigned the task of improving the transportation in the country. The money you have available is sufficient for K roadworks. Each roadwork 
involves either the complete reconstruction of an existing avenue or the creation of a new one in its place. After this, the corresponding avenue will no longer 
require maintenance and can be used for travel at any time. The goal of these projects is to maximize the last time T* at which it is ensured that everyone 
can get to work (or equivalently, to ensure that the connectivity of the country is the same as the connectivity at time 0). This is important because residents will 
not need to leave for work before time T*, allowing them more time to rest.

You must calculate the maximum time T* that can be achieved with K roadworks.

Input Data: 
Your program will read from standard input three positive integers N, M, and K, which correspond to the number of cities, the number of avenues, 
and the number of roadworks. In each of the next M lines, three positive integers aᵢ, bᵢ, and tᵢ will be given, indicating that there is an avenue connecting cities 
aᵢ and bᵢ and closes for maintenance at time tᵢ. There will be at most one avenue connecting each pair of cities.

Output Data: 
Your program should print to standard output (on the first line) a positive integer, the maximum time T* at which it is ensured that everyone can get to work, 
if we carry out the roadworks in an optimal way. If the roadworks can ensure unlimited rest time for the residents, the program should print only one line with the word “infinity”.
*/

#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <climits>

using namespace std;

struct Road {
    int source, destination, construction_time;
    Road(int src, int dst, int t): source(src), destination(dst), construction_time(t) {}
};

bool less_roads(const Road& r1, const Road r2) {
    return r1.construction_time > r2.construction_time;
}

vector<vector<int>> adj_list_init(int size) {
    vector<vector<int>> graph; graph.reserve(size);
    vector<int> init_g(size, 0);
    for (int i=0; i<size; i++)
        graph.emplace_back(init_g);

    return graph;
}

bool isConnected(const vector<vector<int>>& graph, int start, int end) {
    int size = graph.size();
    vector<bool> visited(size, false);
    stack<int> s;

    s.push(start);
    visited[start] = true;

    while (!s.empty()) {
        int current = s.top();
        s.pop();

        for (int i=0; i<size; i++) {
            if (!visited[i] && graph[current][i]>0) {
                if (i == end) return true;
                s.push(i);
                visited[i] = true;
            }
        }
    }

    return false;
}

int main() {
    int N, M, K;
    cin >> N >> M >> K;

    vector<vector<int>> graph = adj_list_init(N+1);
    priority_queue<Road, vector<Road>, decltype(&less_roads)> min_road_heap(&less_roads);

    for (int i=0; i<M; i++) {
        int c1, c2, time;
        cin >> c1 >> c2 >> time;
        graph[c1][c2] = time;
        graph[c2][c1] = time;

        min_road_heap.push(Road(c1,c2,time));
    }

    while (!min_road_heap.empty()) {
        graph[min_road_heap.top().source][min_road_heap.top().destination] = 0;
        graph[min_road_heap.top().destination][min_road_heap.top().source] = 0;

        if (!isConnected(graph, min_road_heap.top().source, min_road_heap.top().destination)) {
            if (K > 0) {
                K--;
                graph[min_road_heap.top().source][min_road_heap.top().destination] = INT_MAX;
                graph[min_road_heap.top().destination][min_road_heap.top().source] = INT_MAX;
            } else break;
        }

        min_road_heap.pop();
    }

    if (min_road_heap.empty()) cout << "infinity" << endl;
    else cout << min_road_heap.top().construction_time << endl;

    return 0;
}
