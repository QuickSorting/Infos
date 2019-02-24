#include <bits/stdc++.h>

using namespace std;

const int N = 1e5 + 7;

vector<int> adj[N];
int used[N];
vector<vector<int> > cycles;
vector<map<int, int> > pos;
vector<int> st;

bool to_use[N];

map<pair<int, int>, int> edge;

void dfs(int u, int p){
	used[u] = 1;
	st.push_back(u);

	for(int to: adj[u]){
		if(to == p){
			continue;
		}
		if(used[to] == 1){
			vector<int> path;
			map<int, int> mp;

			for(int i = st.size() - 1; i >= 0; i--){
				path.push_back(st[i]);
				mp[st[i]] = (int)path.size() - 1;
				if(st[i] == to){
					break;
				}
				edge[make_pair(st[i], st[i-1])] = (int)cycles.size();
				edge[make_pair(st[i-1], st[i])] = (int)cycles.size();
			}

			edge[make_pair(path.back(), path[0])] = (int)cycles.size();
			edge[make_pair(path[0], path.back())] = (int)cycles.size();

			cycles.push_back(path);
			pos.push_back(mp);
		}
		if(used[to] == 0){
			dfs(to, u);
		}
	}

	used[u] = 2;
	st.pop_back();
}

int max_dist(int c, int pos1, int pos2){
	int diff = abs(pos1 - pos2);

	return max(diff, (int)cycles[c].size() - diff);
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	int n, m, a, b;

	cin >> n >> m >> a >> b;

	for(int i = 0; i < m; i++){
		int u, v;

		cin >> u >> v;

		adj[u].push_back(v);
		adj[v].push_back(u);
	}

	for(int i = 1; i <= n; i++){
		if(!used[i]){
			dfs(i, -1);
		}
	}

	for(int i = 1; i <= n; i++){
		used[i] = 0;
	}

	queue<int> q;

	q.push(a);
	used[a] = a;

	int x;

	while(!q.empty()){
		x = q.front();
		q.pop();

		if(x == b){
			break;
		}

		for(int to: adj[x]){
			if(!used[to]){
				q.push(to);
				used[to] = x;
			}
		}
	}

	vector<int> path;
	vector<pair<int, int> > clean_path;

	while(x != a){
		path.push_back(x);
		x = used[x];
	}
	path.push_back(a);

	to_use[0] = true;
	for(int i = 1; i < (int)path.size()-1; i++){
		if(edge[make_pair(path[i-1], path[i])] != edge[make_pair(path[i], path[i+1])]){
			to_use[i] = true;
		}
	}
	to_use[(int)path.size() - 1] = true;

	for(int i = 0; i < path.size() - 1; i++){
		if(to_use[i]){
			clean_path.push_back(make_pair(path[i], edge[make_pair(path[i], path[i+1])]));
		}
	}
	clean_path.push_back(make_pair(path.back(), -1));

	int res = 0;

	for(int i = 0; i < clean_path.size() - 1; i++){;
		int pos1 = clean_path[i].first;
		int pos2 = clean_path[i+1].first;
		int c = clean_path[i].second;

		res += max_dist(c, pos[c][pos1], pos[c][pos2]);
	}

	cout << res << "\n";

	return 0;
}


/*
10 12 2 5
1 10
10 9
9 8
8 7
7 6
6 5
5 4
4 6
6 10
10 3
3 2
2 1
*/