#include <bits/stdc++.h>
#define endl '\n'
#define ll long long
#define PII pair<int, int>
#define mk(a, b) make_pair(a, b)
using namespace std;
template <typename P>
inline void read(P &x) {
    P res = 0, f = 1;
    char ch = getchar();
    while (ch < '0' || ch > '9') {
        if (ch == '-') f = -1;
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9') {
        res = (res << 3) + (res << 1) + (ch ^ 48);
        ch = getchar();
    }
    x = res * f;
}
template <typename Ty, typename... Args>
inline void read(Ty &x, Args &...args) { read(x); read(args...); }
int T = 1;

const int N = 250010;

int n, q, a[N], sum[2][N], diffsum[N];

inline void solve() {
    read(n, q);
    for (int i = 1; i <= n; ++i) {
        read(a[i]);
        sum[1][i] = (a[i] == 1) + sum[1][i - 1];
        sum[0][i] = (a[i] == 0) + sum[0][i - 1];
        diffsum[i] = (a[i] != a[i - 1]) + diffsum[i - 1];
    }
    while (q--) {
        int l, r;
        read(l, r);
        if ((sum[0][r] - sum[0][l - 1]) % 3 != 0 || (sum[1][r] - sum[1][l - 1]) % 3 != 0) { puts("-1"); continue; }
        int res = (sum[0][r] - sum[0][l - 1]) / 3 + (sum[1][r] - sum[1][l - 1]) / 3;
        if (diffsum[r] - diffsum[l] == (r - l)) res++;
        printf("%d\n", res);
    }
}

signed main() {
    // freopen(".in","r",stdin);
    // freopen(".out","w",stdout);
    read(T);
    while (T--) solve();
    return 0;
}