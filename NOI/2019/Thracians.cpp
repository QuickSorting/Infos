#include <bits/stdc++.h>

using namespace std;

const unsigned long long base = 31;
const int N = 5007;
const int R = 107;

unsigned long long real_hash = 0, curr[R][N], curr2[R][N];
char pr_ch[N];
int ans = 0;

int main(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	int r, c;

	cin >> r >> c;

	for(int i = 0; i < r; i++){
		for(int j = 0; j < c; j++){
			char ch;

			cin >> ch;

			real_hash *= base;
			real_hash += (ch - 'a' + 1);
		}
	}

	//cout << real_hash << "\n";

	int n, m;

	cin >> n >> m;

	if(r > n || c > m){
		cout << "0\n";

		return 0;
	}

	unsigned long long power = 1, power2 = 1;

	for(int i = 0; i < c; i++){
		power *= base;
	}

	for(int i = 0; i < r; i++){
		power2 *= power;
	}

	for(int i = 1; i <= r; i++){
		int idx = i % r + 1;
		int pr_idx = (i - 1) % r + 1;

		for(int j = 1; j <= c; j++){
			cin >> pr_ch[j];

			curr[idx][j] = (unsigned long long)curr[idx][j - 1];
			curr[idx][j] *= (unsigned long long)base;
			curr[idx][j] += (unsigned long long)(pr_ch[j] - 'a' + 1);
		}

		curr2[idx][c] = (unsigned long long)curr2[pr_idx][c];
		curr2[idx][c] *= (unsigned long long)power;
		curr2[idx][c] += (unsigned long long)curr[idx][c];

		for(int j = c + 1; j <= m; j++){
			cin >> pr_ch[j];

			curr[idx][j] = (unsigned long long)curr[idx][j - 1];
			curr[idx][j] *= (unsigned long long)base;
			curr[idx][j] -= (unsigned long long)(pr_ch[j - c] - 'a' + 1) * power;
 			curr[idx][j] += (unsigned long long)(pr_ch[j] - 'a' + 1);

 			curr2[idx][j] = (unsigned long long)curr2[pr_idx][j];
			curr2[idx][j] *= (unsigned long long)power;
			curr2[idx][j] += (unsigned long long)curr[idx][j];
		}
	}

	for(int j = c; j <= m; j++){
		//cout << curr2[1][j] << endl;
		if(curr2[1][j] == real_hash){
			ans++;
		}
	}

	for(int i = r + 1; i <= n; i++){
		int idx = i % r + 1;
		int pr_idx = (i - 1) % r + 1;

		for(int j = 1; j <= c; j++){
			cin >> pr_ch[j];

			if(j == c){
				curr2[idx][c] = (unsigned long long)curr2[pr_idx][c];
				curr2[idx][c] *= (unsigned long long)power;
				curr2[idx][c] -= (unsigned long long)power2 * (unsigned long long)curr[idx][c];
			}

			curr[idx][j] = (unsigned long long)curr[idx][j - 1];
			curr[idx][j] *= (unsigned long long)base;
			curr[idx][j] += (unsigned long long)(pr_ch[j] - 'a' + 1);

			curr2[idx][j] += (unsigned long long)curr[idx][j];
		}

		//cout << curr2[idx][c] << endl;

		if(curr2[idx][c] == real_hash){
			ans++;
		}

		for(int j = c + 1; j <= m; j++){
			cin >> pr_ch[j];

			curr2[idx][j] = (unsigned long long)curr2[pr_idx][j];
			curr2[idx][j] *= (unsigned long long)power;
			curr2[idx][j] -= (unsigned long long)power2 * (unsigned long long)curr[idx][j];

			curr[idx][j] = (unsigned long long)curr[idx][j - 1];
			curr[idx][j] *= (unsigned long long)base;
			curr[idx][j] -= (unsigned long long)(pr_ch[j - c] - 'a' + 1) * power;
 			curr[idx][j] += (unsigned long long)(pr_ch[j] - 'a' + 1);
 			
			curr2[idx][j] += (unsigned long long)curr[idx][j];

			//cout << curr2[idx][j] << endl;

			if(curr2[idx][j] == real_hash){
				ans++;
			}
		}
	}

	cout << ans << "\n";

	return 0;
}
