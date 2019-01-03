#include <bits/stdc++.h>

using namespace std;

const int N = 1e7 + 7;

long long a[N];
long long r[N];

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	long long n, k;

	cin >> n >> k;

	long long first, mul, add, mod;

	cin >> first >> mul >> add >> mod;

	for(int i = 0; i < n; i++)
	{
		a[i] = first;

		first = (a[i] * mul + add) % mod;
	}

	stack<long long> st;

	for(int i = 0; i < n; i++)
	{
		while(!st.empty() && a[ st.top() ] < a[i])
		{
			r[ st.top() ] = i-1;
			st.pop();
		}

		st.push(i);
	}

	while(!st.empty())
	{
		r[st.top()] = n-1;
		st.pop();
	}

	long long res = 0;

	for(int i = 0; i < n; i++)
		r[i] = min(i + k - 1, r[i]);

	long long curr_max = -1;

	for(int i = 0; i < n; i++)
	{
		res += max(0ll, r[i] - curr_max) * a[i];
		curr_max = max(curr_max, r[i]);
	}

	cout << res << "\n";

	return 0;
}
