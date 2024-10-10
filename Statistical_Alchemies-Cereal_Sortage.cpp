/*
In the land of Algorithms, there have recently been concerns about the sufficiency of cereal products during the winter. In your effort to ease these concerns, 
and thus make new friends, you have gathered data on the availability of cereal products in the N largest supermarkets along the main commercial street of the capital. 
You know that in the warehouse of supermarket i, there are c₁ packages available. You notice that in some cases the available packages are sufficient, 
though they never exceed N, while in other cases, they are very few and may not be enough for the winter.

You do not want to draw conclusions from extreme cases of very high or very low availability. After much thought, you conclude that a good estimate 
of the availability of cereal products can be derived from the median of the available packages in at least K consecutive supermarkets, for an appropriately 
chosen value of K. In your attempt to approach the issue optimistically, you accept that the maximum value of these medians represents a representative 
estimate of the cereal product availability, and you want to write a program to calculate it.

Input Data:
Your program will initially read from standard input two positive integers, the number N of supermarkets for which you know the cereal product availability 
and the minimum number K of consecutive supermarkets that you must take into account for your estimation. In the next line, N positive integers c₁, c₂, ..., cₙ 
will be given, separated by a space. The integer cᵢ corresponds to the availability of cereal product packages at supermarket i.

Output Data:
Your program must print to the standard output a positive integer, which represents the maximum median value that can be achieved for a segment of the main 
commercial street with at least K consecutive supermarket positions. It is reminded that the median of a sequence of K numbers is the value at 
position ⌊(K + 1)/2⌋ of the corresponding sorted (in ascending order) sequence.
*/

#include <iostream>
#include <vector>
#include <bits/stdc++.h>
using namespace std;

// Function to check if
// the median is possible or not.
bool good(vector<int> arr, int& N, int& K,
          int& median)
{
    int pre[N];
    for (int i = 0; i < N; i++) {
        if (arr[i] >= median)
            pre[i] = 1;
        else
            pre[i] = -1;

        if (i > 0)
            pre[i] += pre[i - 1];
    }

    // mx denotes the maximum
    // sum of a sub array having
    // length at least k.
    int mx = pre[K - 1];

    // mn denotes the minimum
    // prefix sum seen so far.
    int mn = 0;

    for (int i = K; i < N; i++) {
        mn = min(mn, pre[i - K]);
        mx = max(mx, pre[i] - mn);
    }
    if (mx > 0)
        return true;
    return false;
}

// Function to find the maximum median
// of a sub array having length at least K
int maxMedian(vector<int> arr, int N, int K)
{
    // l and r denote the left and right
    // boundary for binary search algorithm
    int l = 1, r = N + 1;

    // Variable to keep track
    // of maximum median
    int mx_median = -1;

    while (l <= r) {
        int mid = (l + r) / 2;
        if (good(arr, N, K, mid)) {
            mx_median = mid;
            l = mid + 1;
        }
        else
            r = mid - 1;
    }
    return mx_median;
}

// Driver function
int main()
{
    int N, K;
    vector<int> arr;
    cin >> N >> K;
    for (int i=0; i<N; i++) {
          int store;
          cin >> store;
          arr.push_back(store);
    }
     
    // Function Call
    cout << maxMedian(arr, N, K);
    return 0;
}
