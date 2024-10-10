/*
Uncle Scrooge needs to increase his revenue in anticipation of the Christmas holidays and the gifts he will buy for his nephews! Thus, he decided to 
get involved (also) in the chocolate trade, which he believes can be particularly profitable at this time of year.

Uncle Scrooge has gathered information and has managed to accurately predict the price of chocolate (per ton, in the commodities market) for each of the N days 
remaining until Christmas. He has recorded the price sequence p(1), ..., p(N) and wants to find out when to buy and when to sell to maximize his profit. 
Every time, he will buy and sell the same amount of chocolate, so he is interested in maximizing the profit per ton. Additionally, in an effort to minimize expenses, 
fees, and to keep his involvement in the chocolate market discreet, he has decided that purchases and sales will alternate, and he will not make more than K trades until Christmas.

Thus, he needs to calculate the optimal number of purchases (and sales) M, where 0≤M≤K, the M days 𝑏1, ..., bM, and the M days s1, ..., sM when he will sell it. 
For the selected days, it holds that 1≤b1<s1<b2<s2<⋯<bM<sM≤N.

Uncle Scrooge’s goal is to maximize his total profit per ton of chocolate, which is equal to ∑ i=1 M (p(si)−p(bi)) (or equal to 0 if he does not perform any trades).

Looking forward to a generous Christmas bonus, you offer to help Uncle Scrooge with his new business venture. You need to write a program that calculates the maximum 
profit (per ton of chocolate) that Uncle Scrooge can make by performing at most K trades.

Input Data:
Initially, the program will read from standard input two positive integers representing the number of days **N** and the maximum number of trades K. On the next 
line, there will be N natural numbers (separated by space) representing the prices p(1), ..., p(N) of one ton of chocolate for each of the next N days.

Output Data:
The program must print to standard output (on the first line) the maximum profit (per ton of chocolate) that Uncle Scrooge can achieve if he performs at most K trades.
*/

#include <iostream>
#include <climits>
#include <vector>
#include <algorithm>

using namespace std;

int max_profit(vector<int> prices, int transactions) {
    int days = prices.size();
    int profits[days + 1][transactions + 1];

    // if zero transactions are made, profit is 0
    for (int i=0; i<transactions+1; i++)
        profits[0][i] = 0;

    // on day 1, profit is 0
    for (int i=0; i<days+1; i++)
        profits[i][0] = 0;

    // fill the array bottom-up by calculating the max possible profit on each day for
    // each number of transactions
    for (int t=1; t<transactions+1; t++) {
        int prev_prof = INT_MIN;
        for (int d=1; d<days; d++) {
            prev_prof = max(prev_prof, profits[d-1][t-1] - prices[d-1]);
            profits[d][t] = max(profits[d-1][t], prices[d] + prev_prof);
        }
    }

    return profits[days-1][transactions];
}

int main() {
    int n, k;
    vector<int> p;
    cin >> n >> k;

    for (int i=0; i<n; i++) {
        int price;
        cin >> price;
        p.push_back(price);
    }

    cout << max_profit(p, k) << endl;
    return 0;
}
