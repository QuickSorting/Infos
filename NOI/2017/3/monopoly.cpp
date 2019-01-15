#include <bits/stdc++.h>

using namespace std;

const long long N = 5e5 + 7;

long long a[N];

long long prefix[N], best[N];

long long range_sum(long long l, long long r)
{
	if(l == 0){
		return prefix[r];
	}

	return prefix[r] - prefix[l-1];
}

int main (){
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	long long n, m;

	cin >> n >> m;

	for(int i = 0; i < n; i++){
		cin >> a[i];
		a[i] = -a[i];
	}

	prefix[0] = a[0];

	for(int i = 1; i < n; i++){
		prefix[i] = prefix[i-1] + a[i];
	}

	best[n-1] = n-1;

	for(int i = n-2; i >= 0; i--){
		if(range_sum(i, i) > range_sum(i, best[i+1])){
			best[i] = i;
		}else{
			best[i] = best[i+1];
		}
	}

	int res = 1, ind = 1;

	for(int i = 0; i < n; i++){
		int l = i, r = n-1, mid;

		while(l != r){
			mid = (l + r + 1) / 2;

			if(range_sum(i, best[mid]) >= -m)
				l = best[mid];
			else{
				r = mid - 1;
			}
		}

		if(l - i + 1 > res){
			res = l - i + 1;
			ind = i + 1;
		}
	}

	cout << res << " " << ind << "\n";

	return 0;
}
