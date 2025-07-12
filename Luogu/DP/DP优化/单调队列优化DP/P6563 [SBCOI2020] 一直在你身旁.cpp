#include <bits/stdc++.h>
#define endl '\n'
#define int long long
#define PII pair<int, int>
#define mk(a, b) make_pair(a, b)
#define rep(i, a, b) for (int (i) = (a); (i) <= (b); ++(i))
#define per(i, a, b) for (int (i) = (a); (i) >= (b); --(i))
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
inline void read(Ty &x, Args &...args) {read(x); read(args...);}
int T = 1;

const int N = 8e3 + 20;

int n, a[N];
int f[N][N],q[N];

inline void solve() {
    read(n);
    rep (i, 1, n) read(a[i]);
    rep (r, 2, n) {
        int p = r;
        int lx = 1, rx = 2; q[1] = r;
        per (l, r, 1) {
            if (l == r) {f[l][r] = 0; continue;}
            else if (r - l == 1) {f[l][r] = a[l]; continue;}
            while (p > l &&  f[l][p - 1] > f[p][r]) p--; 
            f[l][r] = f[l][p] + a[p];
            while (lx < rx && q[lx] >= p) lx++;
            if (lx < rx) f[l][r] = min(f[l][r], f[q[lx] + 1][r]+a[q[lx]]);
            while (lx < rx && f[q[rx - 1] + 1][r] + a[q[rx - 1]] >= f[l + 1][r] + a[l]) rx--;
            q[rx++] = l;
        }
    }
    cout << f[1][n] << endl;
}

signed main() {
    // freopen(".in","r",stdin);
    // freopen(".out","w",stdout);
    read(T);
    while (T--) solve();
    return 0;
}