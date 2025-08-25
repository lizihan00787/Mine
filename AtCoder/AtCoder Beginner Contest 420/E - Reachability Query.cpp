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

const int N = 2e5 + 20;

int n, m;

int fa[N];
int col[N], cnt[N];

int find(int x) {
    if (x == fa[x]) return x;
    return fa[x] = find(fa[x]);
}

inline void solve() {
    read(n, m);
    for (int i = 1; i <= n; ++i) fa[i] = i;
    while (m--) {
        int op, u, v;
        read(op);
        if (op == 1) {
            read(u, v);
            int a = find(u), b = find(v);
            if (a != b) fa[b] = a, cnt[a] += cnt[b];
        }
        else if (op == 2) {
            read(u);
            col[u] ^= 1;
            if (col[u] == 1) cnt[find(u)]++;
            else cnt[find(u)]--;
        }
        else {
            read(u);
            if (cnt[find(u)] >= 1) puts("Yes");
            else puts("No");
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