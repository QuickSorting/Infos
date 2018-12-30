#include <bits/stdc++.h>

using namespace std;

const int N = 100;

struct point
{
	int x, y;

	friend bool operator<(point lhs, point rhs)
	{
		if(lhs.x == rhs.x)
			return lhs.y < rhs.y;

		return lhs.x < rhs.x;
	}

	friend istream& operator>>(istream &input, point &p)
	{
		input >> p.x >> p.y;

		return input;
	}
};

pair<point, point> p[N];
map<pair<int, int>, int> mp;

int gcd(int a, int b)
{
	if(a < b)
		swap(a, b);

	while(b != 0)
	{
		int c = b;

		b = a % b;
		a = c;
	}

	return a;
}

int main ()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	int n;

	cin >> n;

	for(int i = 0; i < n; i++)
	{
		cin >> p[i].first >> p[i].second;

		if(p[i].second < p[i].first)
			swap(p[i].first, p[i].second);
	}

	for(int i = 0; i < n; i++)
	{
		int diff_x = p[i].first.x - p[i].second.x;
		int diff_y = p[i].first.y - p[i].second.y;
		int d = __gcd(diff_x, diff_y);

		diff_x /= d;
		diff_y /= d;

		mp[ {diff_x, diff_y} ] ++;
	}

	cout << mp.size() << "\n";

	return 0;
}
