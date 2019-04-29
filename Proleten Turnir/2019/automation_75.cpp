#include <bits/stdc++.h>

using namespace std;

const int N = 3e5 + 7;

long long subtask, n, a[N];
long long st[4 * N], eq[4 * N], lp[4 * N];

void init2(int idx, int l, int r){
	if(l == r){
		st[idx] = a[l];
		eq[idx] = a[l];
		lp[idx] = 0;
		return;
	}

	int mid = (l + r) / 2;

	init2(2 * idx, l, mid);
	init2(2 * idx + 1, mid + 1, r);

	st[idx] = st[2 * idx] + st[2 * idx + 1];

	if(eq[2 * idx] == eq[2 * idx + 1]){
		eq[idx] = eq[2 * idx];
	}
	else{
		eq[idx] = -1;
	}
}

long long query(int idx, int l, int r, int sl, int sr){
	//cout << "query " << l << " " << r << endl;
	if(idx != 1 && eq[idx / 2] != -1){
		eq[idx] = eq[idx / 2];
		st[idx] = eq[idx] * (r - l + 1);
	}
	if(l > sr || r < sl){
		return 0;
	}
	if(sl <= l && r <= sr){
		return st[idx];
	}

	int mid = (l + r) / 2;

	long long lvalue = query(2 * idx, l, mid, sl, sr);
	long long rvalue = query(2 * idx + 1, mid + 1, r, sl, sr);

	return lvalue + rvalue;
}

void update_eq(int idx, int l, int r, int sl, int sr, long long k){
	//cout << "update_eq " << l << " " << r << endl;
	if(idx != 1 && eq[idx / 2] != -1){
		eq[idx] = eq[idx / 2];
		st[idx] = eq[idx] * (r - l + 1);
	}
	if(l > sr || r < sl){
		return;
	}
	if(sl <= l && r <= sr){
		eq[idx] = k;
		st[idx] = k * (r - l + 1);
		return;
	}

	int mid = (l + r) / 2;

	update_eq(2 * idx, l, mid, sl, sr, k);
	update_eq(2 * idx + 1, mid + 1, r, sl, sr, k);

	st[idx] = st[2 * idx] + st[2 * idx + 1];

	if(eq[2 * idx] == eq[2 * idx + 1]){
		eq[idx] = eq[2 * idx];
	}
	else{
		eq[idx] = -1;
	}
}

void update_div(int idx, int l, int r, int sl, int sr, long long k){
	//cout << "update_div" << endl;
	if(idx != 1 && eq[idx / 2] != -1){
		eq[idx] = eq[idx / 2];
		st[idx] = eq[idx] * (r - l + 1);
	}
	if(l > sr || r < sl){
		return;
	}
	if(sl <= l && r <= sr && eq[idx] != -1){
		eq[idx] = eq[idx] / k;
		st[idx] = (r - l + 1) * eq[idx];
		return; 
	}

	int mid = (l + r) / 2;

	update_div(2 * idx, l, mid, sl, sr, k);
	update_div(2 * idx + 1, mid + 1, r, sl, sr, k);

	st[idx] = st[2 * idx] + st[2 * idx + 1];

	if(eq[2 * idx] == eq[2 * idx + 1]){
		eq[idx] = eq[2 * idx];
	}
	else{
		eq[idx] = -1;
	}
}

void init(int _subtask, int _n, const int _a[]){
    subtask = _subtask;
    n = _n;

    for(int i = 0; i < n; i++){
        a[i] = _a[i];
    }

    init2(1, 0, n-1);
}

long long getSum(int l, int r){
    return query(1, 0, n-1, l, r);
}

void setValues(int l, int r, int k){
    update_eq(1, 0, n-1, l, r, k);
}

void divideValues(int l, int r, int k){
    update_div(1, 0, n-1, l, r, k);
}
