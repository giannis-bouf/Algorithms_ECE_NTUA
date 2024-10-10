/*
Every year, the President of the Republic of Algorithms takes his luxury car and goes on a trip around the country to enjoy the beautiful landscapes and 
connect with the residents. His itinerary is strictly predetermined and announced in advance so that residents can plan their activities and be able to watch 
the presidential convoy. For security reasons, as soon as the presidential car enters a road, the police prohibit entry to it. The prohibition remains in effect 
until the presidential car completes that part of the route and does not affect vehicles that entered the road earlier (regardless of the direction of movement 
of the vehicles and the presidential car). This year, you need to travel on the day of the presidential excursion and want to find out how to reach your destination 
on time. Therefore, you dig out the map of the country and get to work.

In the country, there are a total of N cities and M bidirectional roads. Each road e connects 2 different cities and takes d(e) minutes to travel (by any vehicle, 
regardless of traffic conditions). The President's route includes K different cities, c(1), c(2), ..., c(K-1), c(K) in that order. The President starts at minute 
t(1) = 0 from city c(1), arrives at city c(2) at minute t(2) = d(c(1), c(2)), arrives at city c(3) at minute t(3) = d(c(1), c(2)) + d(c(2), c(3)), and so on. If the 
President arrives at city c(j) at minute t(j), the road {c(j), c(j + 1)} cannot be used by other vehicles (in either direction) from minute t(j) until minute 
t(j) + d(c(j), c(j + 1)) − 1. The road can be used normally, in both directions, if a vehicle starts using it any time up to minute t(j) − 1 and any time from minute 
t(j) + d(c(j), c(j + 1)) and onward.

You will travel from city A to city B and will start your journey at minute T ≥ 0. You want to write a program that calculates the minimum duration of your journey, 
given the limited availability of some roads due to the presidential excursion.

Input Data:
Your program will read from standard input the first line, which contains two positive integers N and M, corresponding to the number of cities and the number of roads 
(the cities are numbered from 1 to N). The second line will contain 4 positive integers A, B, T, and K, which correspond to the starting point A, the destination B, 
the minute you start your journey, and the number of cities included in the President's route. The third line will contain positive integers corresponding to the cities 
c(1), c(2), ..., c(K) included in the route. In each of the following M lines, there will be 3 positive integers u, v, d(u, v) indicating that there is a road connecting 
cities u and v and takes d(u, v) minutes to travel. You can assume that the country of Algorithms is connected, that there is a road between every two consecutive cities
on the President's route, and that the President does not pass through the same road twice.

Output Data: 
Your program should print to standard output (on the first line) an integer corresponding to the minimum duration (in minutes) of your trip from city A to city B, 
given that your journey starts at minute T.
*/

#include <iostream>
#include <vector>
#include <climits>

using namespace std;

struct Road_Blockade {
    int start, finish;
    Road_Blockade(int s, int f): start(s), finish(f) {}
};

vector<vector<int>> adj_list_init(int size) {
    vector<vector<int>> graph; graph.reserve(size);
    vector<int> init_g(size, 0);
    for (int i=0; i<size; i++)
        graph.emplace_back(init_g);

    return graph;
}

vector<vector<Road_Blockade>> blockades_schedule(vector<int> pres_roads, vector<vector<int>> graph) {
    vector<vector<Road_Blockade>> blockades; blockades.reserve(graph.size());
    vector<Road_Blockade> init(graph.size(), Road_Blockade(0,0));
    for (int i=0; i<graph.size(); i++)
        blockades.push_back(init);

    int president_time = 0;
    for (int i=1; i<pres_roads.size(); i++) {
        blockades[pres_roads[i-1]][pres_roads[i]].start = president_time;
        blockades[pres_roads[i-1]][pres_roads[i]].finish =
                president_time+graph[pres_roads[i-1]][pres_roads[i]];
        blockades[pres_roads[i]][pres_roads[i-1]].start = president_time;
        blockades[pres_roads[i]][pres_roads[i-1]].finish =
                president_time+graph[pres_roads[i-1]][pres_roads[i]];
        president_time += graph[pres_roads[i-1]][pres_roads[i]];
    }

    return blockades;
}

int minDistance(vector<int> dist, bool sptSet[], int cities) {
    int min = INT_MAX, min_index;

    for (int v = 0; v < cities+1; v++)
        if (!sptSet[v] && dist[v] <= min)
            min = dist[v], min_index = v;

    return min_index;
}

int travelling_time(vector<vector<int>> graph, vector<vector<Road_Blockade>> blockades,
                    int src, int dst, int cities, int start) {
    vector<int> dist;
    bool sptSet[cities+1];

    for (int i = 0; i < cities+1; i++)
        dist.push_back(INT_MAX), sptSet[i] = false;

    dist[src] = start;

    for (int count = 0; count < cities; count++) {
        int u = minDistance(dist, sptSet, cities);

        sptSet[u] = true;

        for (int v = 0; v < cities+1; v++) {
            int delay;
            if (dist[u]>=blockades[u][v].start && dist[u]<blockades[u][v].finish)
                delay = blockades[u][v].finish - dist[u];
            else delay = 0;
            if (!sptSet[v] && graph[u][v] > 0
                && dist[u] != INT_MAX
                && dist[u] + graph[u][v] + delay < dist[v])
                dist[v] = dist[u] + graph[u][v] + delay;
        }
    }

    return dist[dst]-dist[src];
}

int main() {
    int N, M, A, B, T, K;
    cin >> N >> M >> A >> B >> T >> K;

    vector<vector<int>> graph = adj_list_init(N+1);

    vector<int> president_road;
    for (int i=0; i<K; i++) {
        int president_city;
        cin >> president_city;
        president_road.push_back(president_city);
    }

    for (int i=0; i<M; i++) {
        int c1, c2, time;
        cin >> c1 >> c2 >> time;
        graph[c1][c2] = time;
        graph[c2][c1] = time;
    }

    vector<vector<Road_Blockade>> blockades = blockades_schedule(president_road, graph);

    cout << travelling_time(graph, blockades, A, B, N, T) << endl;

    return 0;
}
