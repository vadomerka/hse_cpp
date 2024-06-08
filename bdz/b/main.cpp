#include <bits/stdc++.h>
#include <vector>

using namespace std;

int main() {
    long long n, s, full_sum;
    cin >> n;
    vector<vector<long long>> dp (54, vector<long long> (11, 0));
    for (int i = 0; i < 9; i++) {
        dp[0][i] = 1;
    }
    dp[0][9] = 9;
    dp[0][10] = 9;
    for (int i = 1; i < 54; i++) {
        s = 0;
        for (int j = 0; j < 9; j++) {
            s += dp[i - 1][j];
        }
        for (int j = 0; j < 9; j++) {
            dp[i][j] = s;
            s -= dp[i - 1][j];
            dp[i][9] += dp[i][j];
        }
        dp[i][10] = dp[i - 1][10] + dp[i][9];
    }
    for (auto i : dp) {
        for (auto j : i) {
            cout << j << ' ';
        } cout << endl;
    }
    int i = 0;
    while (dp[i][10] <= n) {
        i++;
    }
    if (i == -1) {
        cout << n;
    }
    long long cur_s;
    for (int k = i; k > -1; k--) {
        int j = 0;
        if (k == 0) {
            cur_s = 0;
        } else {
            cur_s = dp[k - 1][9];
        }
        while (cur_s + dp[k][j] <= n && j < 8) {
            cur_s += dp[k][j];
            j++;
        }
        n -= cur_s;
        cout << j + 1 << ' ' << cur_s << endl;;
    }
}