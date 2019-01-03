#include <bits/stdc++.h>

using namespace std;

const int N = 2e5 + 7;

int a[N];

int main ()
{
        ios::sync_with_stdio(false);
        cin.tie(NULL);

        int n;

        cin >> n;

        for(int i = 0; i < n; i++)
                cin >> a[i];

        int mn = n, mx = 0;
        int cnt1 = 0, cnt2 = 0;

        for(int i = n - 1; i >= 0; i--)
        {
                mn = min(mn, a[i] + cnt1);
                mx = max(mx, a[i] + cnt2);

                if(a[i] == i)
                        cnt1++;
                if(a[i])
                        cnt2++;
        }

        cout << mx << "\n" << mn << "\n";

        return 0;
}
