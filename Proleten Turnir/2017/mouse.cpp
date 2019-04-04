#include <bits/stdc++.h>

using namespace std;

const long long N = (1 << 20);

long long a[N], temp[N];

long long solve(long long l, long long r){
	if(l == r){
		return 0;
	}

	long long mid = (l + r) / 2;

	long long res = solve(l, mid) + solve(mid + 1, r);

	int i = l, j = mid + 1, curr = l;
	long long add1 = 0, add2 = 0;

	while(i <= mid && j <= r){
		if(a[i] < a[j]){
			add1 += r - j + 1;
			temp[curr] = a[i];
			i++;
		}
		else{
			add2 += mid - i + 1;
			temp[curr] = a[j];
			j++;
		}
		curr++;
	}

	for(; i <= mid; i++, curr++){
		temp[curr] = a[i];
	}
	for(; j <= r; j++, curr++){
		temp[curr] = a[j];
	}

	for(i = l; i <= r; i++){
		a[i] = temp[i];
	}

	return res + min(add1, add2);
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	long long k, n;

	cin >> k;
	n = (1 << k);

	for(long long i = 1; i <= n; i++){
		cin >> a[i];
	}

	cout << solve(1, n) << "\n";

	return 0;
}
/*
2
4 2 3 1
*/
