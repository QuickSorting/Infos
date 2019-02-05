#include <bits/stdc++.h>

using namespace std;

const long long N = 107;
const long long mod = 1e9 + 7;

pair<long long, bool> dp[N][N];
string s;

long long solve(long long l, long long r){
	//cout << l << " " << r << "\n";

	if(l > r){
		return 1;
	}

	if(dp[l][r].second){
		return dp[l][r].first;
	}

	dp[l][r].second = true;

	dp[l][r].first = solve(l+1, r);

	for(int i = r; i > l; i--){
		if(s[i] == s[l]){
			dp[l][r].first += solve(l+1, i-1);
		}
	}
	dp[l][r].first += 1;

	dp[l][r].first %= mod;

	return dp[l][r].first;
}

int main (){
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> s;

	cout << solve(0, s.size() - 1) - 1 << "\n";

	return 0;
}
