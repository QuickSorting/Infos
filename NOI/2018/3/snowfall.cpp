#include <bits/stdc++.h>

using namespace std;

const int N = 5e4 + 7;
const int inf = 1e9;

vector<int> adj[N], snow[N];
bool used[N];

int n;

bool connected(int mid){
	stack<int> st;

	for(int i = 1; i <= n; i++){
		used[i] = false;
	}

	st.push(1);
	used[1] = true;

	while(!st.empty()){
		int x = st.top();
		st.pop();

		for(int i = 0; i < adj[x].size(); i++){
			int to = adj[x][i], s = snow[x][i];

			if(mid < s && !used[to]){
				used[to] = true;
				st.push(to);
			}
		}
	}

	for(int i = 1; i <= n; i++){
		if(!used[i]){
			return false;
		}
	}

	return true;
}

int tin[N], low[N];
int timer;
vector<int> res;
bool in_res[N];

void dfs(int u, int p, int mid){
	used[u] = true;
	tin[u] = low[u] = timer++;

	//cout << u << " p " << p << " " << mid << endl;

	int children = 0;

	for(int i = 0; i < adj[u].size(); i++){
		int to = adj[u][i], s = snow[u][i];

		if(mid >= s){
			continue;
		}
		if(to == p){
			continue;
		}

		if(used[to]){
			low[u] = min(low[u], tin[to]);
		}
		else{
			dfs(to, u, mid);

			low[u] = min(low[u], low[to]);

			if(low[to] >= tin[u] && p != -1){
				if(!in_res[u]){
					res.push_back(u);
					in_res[u] = true;
				}
			}
			++children;
		}
	}

	//cout << low[u] << " low[u] " << u << endl;

	if(p == -1 &&  children >= 2){
		res.push_back(u);
	}

	return ;
}

int articulation_points(int mid){
	for(int i = 1; i <= n; i++){
		used[i] = false; 
		in_res[i] = false;
	}
	timer = 0;
	res.clear();

	dfs(1, -1, mid);

	return res.size();
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	int m, k;

	cin >> n >> m >> k;

	for(int i = 0; i < m; i++){
		int a, b, c;

		cin >> a >> b >> c;

		adj[a].push_back(b);
		snow[a].push_back(c);
		adj[b].push_back(a);
		snow[b].push_back(c);
	}

	int l = -1, r = inf, mid;

	while(l != r){
		mid = (l + r + 1) / 2;

		if(connected(mid)){
			l = mid;
		}
		else{
			r = mid - 1;
		}
	}

	if(l == -1){
		cout << "-1 0\n";

		return 0;
	}

	//cout << l << endl;

	int mx = l+1;

	r = mx;
	l = 0;

	while(l != r){
		mid = (l + r)/2;

		//cout << articulation_points(mid) << " mid " << mid << endl;

		if(articulation_points(mid) >= k){
			r = mid;
		}
		else{
			l = mid + 1;
		}
	}

	if(l == mx){
		cout << "-1 0\n";

		return 0;
	}

	cout << l << " " << articulation_points(l) << "\n";

	sort(res.begin(), res.end());

	for(int x: res){
		cout << x << " ";
	}
	cout << "\n";

	return 0;
}
