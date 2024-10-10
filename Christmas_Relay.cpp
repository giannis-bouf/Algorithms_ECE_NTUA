/*
Santa Claus just realized that the letters with the children's wishes from the country of Algorithms have not yet arrived in Rovaniemi. 
His helpers must ensure that the children's wishes reach him as soon as possible so that he can have their gifts ready for Christmas.

The country of Algorithms has N large cities 𝑉1,𝑉2,…,𝑉𝑁, where the children's letters from nearby areas have been collected. The road network of 
the country is quite simple and has a tree-like structure. Each city 𝑉𝑖 ​has a unique route to the capital 𝑉1, and Santa's helpers have calculated the exact distance 
𝐷𝑖 from 𝑉𝑖 to the next city along the route to the capital 𝑉1.

In each city 𝑉𝑖, a helper of Santa Claus is stationed. This helper needs 𝑃𝑖 seconds to load the letters and start moving with their sleigh, and 
𝑆𝑖 seconds to travel each kilometer along the route from 𝑉𝑖to 𝑉1.

Santa's instructions are clear: the helpers are not allowed to deviate from the route to the capital. A sleigh starting from city 𝑉𝑖
can only move along the route 𝑉𝑖→𝑉1. To speed up the process, when the sleigh from city 𝑉𝑖 reaches an intermediate city 
𝑉𝑗, it can either continue towards 𝑉1 or transfer the letters to the helper in city 𝑉𝑗, provided that the helper in 𝑉𝑗
can move faster. The helper in 𝑉𝑗 will then need 𝑃𝑗 seconds to start their sleigh and 𝑆𝑗 seconds for each kilometer from 𝑉𝑗 to 𝑉1.

All the helpers are ready to go! They need a plan that follows Santa's rules and ensures that the letters from each city 
𝑉2,…,𝑉𝑁 reach the capital 𝑉1 as quickly as possible (once they reach 𝑉1, all the letters are instantly delivered to Rovaniemi using Santa's 
own sleigh). So, you need to write a program that calculates the minimum time (in seconds) for the letters from each city 𝑉𝑖 to reach the capital 𝑉1.

Input:
Initially, your program will read from the standard input a positive integer N, the number of cities where the children's letters have been gathered. Each of the following 
N−1 lines will contain three positive integers 𝑉𝑖, 𝑉𝑗, 𝐷𝑖𝑗, which indicate that there is a road of length 𝐷𝑖𝑗 between cities 𝑉𝑖 and 𝑉𝑗. The next 𝑁−1
lines will contain two positive integers each. The pair of numbers 𝑃𝑖+1 and 𝑆𝑖+1 on the i-th line indicates that the sleigh starting from city 𝑉𝑖+1
needs 𝑃𝑖+1 seconds to start and 𝑆𝑖+1 seconds for each kilometer of the route from 𝑉𝑖+1 to 𝑉1.

You can assume that the road network will be connected and tree-like.

Output:
Your program should print to the standard output N−1 positive integers separated by a space. The i-th integer should correspond to the minimum 
time (in seconds) for the letters from city 𝑉𝑖+1 to be delivered to the capital 𝑉1. 
*/

#include <iostream>
#include <utility>
#include <vector>
#include <climits>

using namespace std;

void create_graph(vector<vector<pair<int,int>>>& distances, vector<pair<int,int>>& times,
                  int town, vector<pair<int,int>> prev, vector<vector<long>>& res, int arrived_from) {
    for (int i=0; i<prev.size(); i++) {
        long val = times[town].first + prev[i].second*times[town].second;
        //res[town][prev[i].first] = val;
        res[prev[i].first][town] = val;
    }
    for (int i=0; i<distances[town].size(); i++) {
        if (distances[town][i].first != arrived_from) {
            vector<pair<int,int>> prev1 = prev;
            for (int j=0; j<prev1.size(); j++)
                prev1[j].second += distances[town][i].second;
            prev1.emplace_back(town,distances[town][i].second);
            create_graph(distances, times, distances[town][i].first, prev1, res, town);
        }
    }
}

int minDistance(vector<long> dist, bool sptSet[], int towns)
{
    int min = INT_MAX, min_index;

    for (int v = 0; v < towns+1; v++)
        if (!sptSet[v] && dist[v] <= min)
            min = dist[v], min_index = v;

    return min_index;
}

vector<long> dijkstra(vector<vector<long>> graph, int src, int towns)
{
    vector<long> dist;
    bool sptSet[towns+1];

    for (int i = 0; i < towns+1; i++)
        dist.push_back(INT_MAX), sptSet[i] = false;

    dist[src] = 0;

    for (int count = 0; count < towns; count++) {
        int u = minDistance(dist, sptSet, towns);

        sptSet[u] = true;

        for (int v = 0; v < towns+1; v++)
            if (!sptSet[v] && graph[u][v]>0
                && dist[u] != INT_MAX
                && dist[u] + graph[u][v] < dist[v])
                dist[v] = dist[u] + graph[u][v];
    }

    return dist;
}

vector<long> quick_santa(vector<vector<pair<int,int>>>& distances, vector<pair<int,int>>& times, int towns) {
    vector<vector<long>> costs(towns+1);
    for (int i=0; i<towns+1; i++)
        for (int j=0; j<towns+1; j++)
            costs[i].push_back(0);

    create_graph(distances, times, 1, {}, costs, 0);
    return dijkstra(costs, 1, towns);
}

int main() {
    int towns;
    cin >> towns;

    vector<vector<pair<int,int>>> distances(towns+1);
    for (int i=0; i<towns-1; i++) {
        int t1, t2, dis;
        cin >> t1 >> t2 >> dis;
        distances[t1].emplace_back(t2,dis);
        distances[t2].emplace_back(t1,dis);
    }

    vector<pair<int, int>> times = {make_pair(0,0), make_pair(0,0)};
    for (int i=0; i<towns-1; i++) {
        int accelerating, travelling;
        cin >> accelerating >> travelling;
        times.emplace_back(accelerating, travelling);
    }

    vector<long> time = quick_santa(distances, times, towns);
        for (int j=2; j<towns+1; j++) {
            cout << time[j];
            if (j<towns) cout << " ";
        }
        cout << endl;

    return 0;
}
