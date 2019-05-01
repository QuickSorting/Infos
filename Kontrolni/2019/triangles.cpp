#include <bits/stdc++.h>
//#include "triangles.h"

using namespace std;

const int N = 6e5 + 7;

const double PI = acos(-1);

void fft(vector<complex<double> > &a, bool invert){
    int n = a.size();

    for(int i = 1, j = 0; i < n; i++){
        int bits = n / 2;
        for(; j & bits; bits /= 2){
            j ^= bits;
        }
        j ^= bits;

        if(i < j){
            swap(a[i], a[j]);
        }
    }

    //swap(a[0], a[1]);

    for(int len = 2; len <= n; len *= 2){
        double ang = 2 * PI / (double)len * (invert ? -1 : 1);
        complex<double> wlen(cos(ang), sin(ang));

        for(int i = 0; i < n; i += len){
            complex<double> w(1);
            for(int j = 0; j < len / 2; j++){
                complex<double> u = a[i + j], v = a[i + j + len / 2] * w;

                a[i + j] = (u + v);
                a[i + j + len / 2] = (u - v);
                w *= wlen;
            }
        }
    }

    if(invert){
        for(auto &x: a){
            x /= n;
        }
    }
}

vector<long long> multiply(const vector<long long> &a, const vector<long long> &b){
    vector<complex<double> > wa, wb;

    for(int i = 0; i < a.size(); i++){
        wa.push_back(complex<double>(a[i], 0.0));
    }
    for(int i = 0; i < b.size(); i++){
        wb.push_back(complex<double>(b[i], 0.0));
    }

    int n = 1;
    while(n < a.size() + b.size()){
        n *= 2;
    }

    wa.resize(n);
    wb.resize(n);

    fft(wa, false);
    fft(wb, false);

    for(int i = 0; i < n; i++){
        wa[i] *= wb[i];
    }

    fft(wa, true);

    vector<long long> ans;

    for(int i = 0; i < n; i++){
        ans.push_back(round(wa[i].real()));
    }

    return ans;
}

long long a[N];
vector<long long> cnt, v;

long long triangles(const int lens[], int n){
    cnt.resize(N, 0);

    for(int i = 0; i < n; i++){
        a[i] = lens[i];
        cnt[a[i]]++;
    }

    sort(a, a + n);

    v = multiply(cnt, cnt);

    for(int i = 2 * N - 3; i >= 0; i--){
        v[i] += v[i + 1];
    }
    for(int i = N - 2; i >= 0; i--){
        cnt[i] += cnt[i + 1];
    }

    long long ret = 0;
    int j = 0;

    for(int i = 0; i < n; i++){
        long long b = (n - i - 1);

        while(2 * a[j] <= a[i]){
            j++;
        }

        long long curr = v[a[i] + 1] - (n - j);

        //cout << v[a[i] + 1] << " - " << curr << endl;

        ret += curr / 2 - b * (n - b) - b * (b - 1) / 2;
        ret += (i - j + 1);
    }

    return ret;
}

/*int n, arr[N];

int main(){
    cin >> n;

    for(int i = 0; i < n; i++){
        cin >> arr[i];
    }

    cout << triangles(arr, n) << "\n";

    return 0;
}*/
