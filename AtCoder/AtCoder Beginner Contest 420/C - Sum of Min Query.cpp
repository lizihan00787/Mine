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

const int N = 2e5 + 20;

int n, m;
int a[N], b[N];

inline void solve() {
    read(n, m);
    int sum = 0;
    for (int i = 1; i <= n; ++i) read(a[i]);
    for (int i = 1; i <= n; ++i) read(b[i]), sum += min(a[i], b[i]);
    while (m--) {
        char op;
        int x, v;
        cin >> op;
        read(x, v);
        if (op == 'A') {
            if (v <= min(a[x], b[x])) sum -= (min(a[x], b[x]) - v);
            else if (a[x] == min(a[x], b[x]) && v >= a[x]) sum += (min(b[x], v) - a[x]);
            a[x] = v;
            printf("%lld\n", sum);
        }
        else {
            if (v <= min(a[x], b[x])) sum -= (min(a[x], b[x]) - v);
            else if (b[x] == min(a[x], b[x]) && v >= b[x]) sum += (min(a[x], v) - b[x]);
            b[x] = v;
            printf("%lld\n", sum);
        }
    }
}

signed main() {
    // freopen(".in","r",stdin);
    // freopen(".out","w",stdout);
    // read(T);
    while (T--) solve();
    return 0;
}