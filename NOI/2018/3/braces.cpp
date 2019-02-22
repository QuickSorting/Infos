#include <bits/stdc++.h>

using namespace std;

const int N = 1007;
const int K = 207;

int dp[N][K];
string s;
int n;

int calc_dp[N][N];

void init_calc(){
	for(int i = 0; i < n; i++){
		int ret = 0, sum = 0;
		for(int j = i; j < n; j++){
			if(s[j] == '('){
				sum++;
			}
			else{
				if(sum){
					ret++;
					sum--;
				}
			}

			calc_dp[i][j] = ret;
		}
	}
}

int calc(int left, int right){
	return calc_dp[left][right];
}

void output_calc(int left, int right){
	vector<int> open;
	vector<int> for_output;

	for(int i = left; i <= right; i++){
		if(s[i] == '('){
			open.push_back(i);
		}
		else{
			if(!open.empty()){
				for_output.push_back(i + 1);
				for_output.push_back(open.back() + 1);
				open.pop_back();
			}
		}
	}

	sort(for_output.begin(), for_output.end());

	for(int x: for_output){
		cout << " " << x;
	}
}

void solve(int left, int l, int r, int optl, int optr){
	if (l > r){
        return ;
	}

    int mid = (l + r) / 2;
    pair<int, int> best = {N, -1};

    for(int i = max(optl, mid); i <= optr; i++){
    	int score = dp[i + 1][left - 1] + calc(mid, i);

    	if(score < best.first){
    		best.first = score;
    		best.second = i;
    	}
    }

    dp[mid][left] = best.first;
    if(dp[mid][left] >= N){
    	best.second = optr;
    }

    //cout << dp[mid][left] << " = " << mid << " " << left << "\n";
 
    solve(left, l, mid - 1, optl, best.second);
    solve(left, mid + 1, r, best.second, optr);
}

int cnt = 1;

void output1(int pos, int left){
	if(left <= 0){
		return ;
	}

	int x = N, which;

	for(int i = pos; i < n; i++){
		int ans = dp[i + 1][left - 1] + calc(pos, i);

		if(ans < x){
			x = ans;
			which = i;
		}
	}

	cout << cnt << ", [" << pos + 1 << ", " << which + 1 << "], " << calc(pos, which) * 2 << ":";

	output_calc(pos, which);

	cout << "\n";

	cnt++;
	output1(which + 1, left - 1);
}

void output2(int pos, int left){
	if(left <= 0){
		return ;
	}

	int x = N, which;

	for(int i = n-1; i >= pos; i--){
		int ans = dp[i + 1][left - 1] + calc(pos, i);

		if(ans < x){
			x = ans;
			which = i;
		}
	}

	cout << cnt << ", [" << pos + 1 << ", " << which + 1 << "], " << calc(pos, which) * 2 << ":";

	output_calc(pos, which);

	cout << "\n";

	cnt++;
	output2(which + 1, left - 1);
}


int main(){
	//ios::sync_with_stdio(false);
	//cin.tie(NULL);
	//cout.tie(NULL);

	int k;

	cin >> s >> k;
	n = s.size();

	init_calc();

	for(int i = 0; i < n; i++){
		dp[i][0] = N;
	}

	for(int i = 1; i <= k; i++){
		solve(i, 0, n-1, 0, n-1);
		dp[n][i] = N;
	}

	cout << dp[0][k] * 2 << "\n\n";

	cnt = 1;
	output1(0, k);
	
	cout << "\n";

	cnt = 1;
	output2(0, k);

	return 0;
}