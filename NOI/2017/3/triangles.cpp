#include <bits/stdc++.h>

using namespace std;

map<long long, set<long long> > row, col;

int main (){
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	long long n, q;

	cin >> n >> q;

	for(long long i = 0; i < n; i++){
		long long x, y;

		cin >> x >> y;

		row[x].insert(y);
		col[y].insert(x);
	}

	for(long long i = 0; i < q; i++){
		long long type, x, y;

		cin >> type >> x >> y;

		if(type == 1){
			row[x].insert(y);
			col[y].insert(x);

			continue;
		}

		if(type == 2){
			row[x].erase(y);
			col[y].erase(x);

			continue;
		}

		if(type == 3){
			if(row[x].empty() || col[y].empty()){
				cout << "0\n";

				continue;
			}

			long long mx_row, mx_col;

			mx_row = max(y - *row[x].begin(), *row[x].rbegin() - y);
			mx_col = max(x - *col[y].begin(), *col[y].rbegin() - x);

			long long res = mx_row * mx_col;

			if(res & 1){
				cout << res / 2 << ".5\n";
			}
			else{
				cout << res / 2 << "\n";
			}
		}
	}

	return 0;
}
