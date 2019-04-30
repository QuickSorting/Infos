#include <bits/stdc++.h>

using namespace std;

const long long mod = 1e15 + 37;
const long long base = 127;
const int N = 5e6 + 7;

string a[3];

struct my_vector{
	long long arr[N];
	int cnt;

	my_vector(){
		cnt = 0;
	}

	inline int size(){
		return cnt;
	}

	void push_back(long long x){
		arr[cnt] = x;
		cnt++;
	}
};

my_vector v[2];

void brute_force(int idx, int l, int r, long long ans = 0){
	if(l > r){
		v[idx].push_back(ans);
		return;
	}

	for(int i = 0; i < 3; i++){
		long long ans2 = ans;
		ans2 *= base;
		ans2 += a[i][l];
		ans2 %= mod;

		brute_force(idx, l + 1, r, ans2);
	}
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	int n;

	cin >> n;

	for(int i = 0; i < 3; i++){
		cin >> a[i];
	}

	if(n < 14){
		brute_force(0, 0, n - 1);

		sort(v[0].arr, v[0].arr + v[0].size());

		cout << v[0].arr[0] << "\n";

		return 0;
	}

	brute_force(0, 0, n / 2 - 1 + n % 2);
	brute_force(1, n / 2 + n % 2, n - 1);

	for(long long &x: v[0].arr){
		for(int i = 0; i < n / 2; i++){
			x *= base;
			x %= mod;
		}
	}

	sort(v[0].arr, v[0].arr + v[0].size());
	sort(v[1].arr, v[1].arr + v[1].size());

	long long mn = (v[0].arr[0] + v[1].arr[0]) % mod;

	int j = v[1].size() - 1;

	for(int i = 0; i < v[0].size(); i++){
		while((v[0].arr[i] + v[1].arr[j]) >= mod && j >= 0){
			j--;
		}
		if(j != v[1].size() - 1){
			j++;
		}

		//cout << v[0][i] << " " << v[1][j] << " " << j  << endl;

		long long t = v[0].arr[i] + v[1].arr[j];

		if(t >= mod){
			t -= mod;
		}

		mn = min(t, mn);
	}

	cout << mn << "\n";

	return 0;
}
