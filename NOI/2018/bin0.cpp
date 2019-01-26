#include <bits/stdc++.h>

using namespace std;

const unsigned long long N = 64;

pair<unsigned long long, bool> dp[N][N][2][2];

unsigned long long num;

unsigned long long solve(unsigned long long left_d, unsigned long long left_z, bool started, bool equal){
	if(left_z < 0){
		return 0;
	}

	if(left_d == 0){
		if(left_z == 0 && started){
			return 1;
		}else{
			return 0;
		}
	}

	pair<unsigned long long, bool> &p = dp[left_d][left_z][started][equal];

	if(p.second && !equal){
		return p.first;
	}

	p.first = 0;
	p.second = true;

	unsigned long long curr_d = (1ll << (left_d-1)) & num;
	curr_d = (bool) curr_d;

	unsigned long long mx = equal ? curr_d : 1;

	for(unsigned long long i = 0; i <= mx; i++){
		unsigned long long new_z = left_z;
		bool new_equal = equal ? (i == curr_d) : 0;
		bool new_started = started ? 1 : (i == 1);

		if(i == 0 && started){
			new_z--;
		}

		p.first += solve(left_d - 1, new_z, new_started, new_equal);
	}

	//cout << left_d << " " << left_z << " " << started << " " << equal << " = " << p.first << "\n";

	return p.first;
}

unsigned long long solve(unsigned long long x, unsigned long long z){
	num = x;

	return solve(61, z, false, true);
}

int main (){
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	unsigned long long s, t, z;

	cin >> s >> t >> z;

	if(s > t){
		swap(s, t);
	}

	cout << solve(t, z) - solve(s-1, z) << "\n";

	return 0;
}