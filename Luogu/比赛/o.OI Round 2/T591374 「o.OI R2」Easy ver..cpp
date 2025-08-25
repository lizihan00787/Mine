#include <bits/stdc++.h>
#define endl '\n'
#define int long long
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

const int mod = 1e9 + 7;

int n, m, k;

int qpow(int a, int b) {
    int res = 1;
    while (b) {
        if (b & 1) res = res * a % mod;
        a = a * a % mod;
        b >>= 1;
    }
    return res;
}

inline void solve() {
    read(n, m, k);
    // if (n == m && n == 1 && k != 1) {
    //     puts("2");
    //     return;
    // }
    if (k == 1) {
        puts("1");
        return;
    }
    if (n == 1 || m == 1) {
        int maxx = max(n, m);
        if (maxx < k) cout << qpow(2, maxx) % mod << endl;
        else cout << qpow(2, k - 1) % mod<< endl;
        return;
    }
    if (n * m <= k) { cout << qpow(2, k - 1) % mod << endl; return; }
    if (k % 2 != 0) cout << 1 << endl;
    else cout << 2 << endl;
}

signed main() {
    // freopen(".in","r",stdin);
    // freopen(".out","w",stdout);
    read(T);
    while (T--) solve();
    return 0;
}