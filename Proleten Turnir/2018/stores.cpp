#include <bits/stdc++.h>

using namespace std;

const long long N = 6e5 + 7;

struct point{
	long long x, y, idx;

	point(long long x = -1, long long y = -1){
		this->x = x;
		this->y = y;
	}

	friend bool operator<(point lvalue, point rvalue){
		return (lvalue.x == rvalue.x) ? (lvalue.y < rvalue.y) : (lvalue.x < rvalue.x);
	}
};

long long area(point p1, point p2, point p3){
	long long ret = p1.x * p2.y + p2.x * p3.y + p3.x * p1.y;
	ret -= p1.x * p3.y + p2.x * p1.y + p3.x * p2.y;

	return ret;  
}

point p[N];

bool cmp(point lvalue, point rvalue){
	return area(p[1], lvalue, rvalue) > 0;
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	long long n;

	cin >> n;

	for(long long i = 1; i <= n; i++){
 		cin >> p[i].x >> p[i].y;
 		p[i].idx = i;
	}

	for(long long i = 1; i <= n; i++){
 		cin >> p[i + n].x >> p[i + n].y;
 		p[i + n].idx = i + n;
	}

	sort(p + 1, p + 2 * n + 1);
	
	sort(p + 2, p + 2 * n + 1, cmp);

	point pr = point(-1, -1);

	vector<point> w;

	cout << 2 * n - 1 << "\n";
	for(long long i = 2; i <= 2 * n; i++){
		if((p[i].idx > n) != (p[1].idx > n)){
			cout << p[1].idx << " " << p[i].idx << "\n";
			pr = p[i];
			if(!w.empty()){
				for(point pnt: w){
					cout << p[i].idx << " " << pnt.idx << "\n";
				}
				w.clear();
			}
		}
		else{
			if(pr.x != -1){
				cout << pr.idx << " " << p[i].idx << "\n";  
			}
			else{
				w.push_back(p[i]);
			}
		}
	}

	
	return 0;
}
/*
6
6 5
3 3
5 2
7 2
9 5
9 1
5 8
2 4
6 3
8 0
10 4
8 7
*/
