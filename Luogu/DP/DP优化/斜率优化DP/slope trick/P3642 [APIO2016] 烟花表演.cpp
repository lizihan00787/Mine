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

const int N = 6e5 + 20;

int n, m, tot, fa[N], a[N], son[N], rt[N];
ll sum;

struct node {
    int l, r, dis;
    ll v;
} t[N];

int merge(int x, int y) {
    if(!x || !y) return x + y;
    if(t[x].v < t[y].v) swap(x, y);
    t[x].r = merge(t[x].r, y);
    if(t[t[x].l].dis < t[t[x].r].dis) swap(t[x].l, t[x].r);
    if(!t[x].r) t[x].dis = 0;
    else t[x].dis = t[t[x].r].dis + 1;
    return x;
}
int uninn(int x) { return merge(t[x].l, t[x].r); }

inline void solve() {
    read(n, m);
    for (int i = 2; i <= n + m; ++i) {
        read(fa[i], a[i]);
        sum += a[i], son[fa[i]]++;
    }
    for (int i = n + m; i >= 2; --i) {
        ll l = 0, r = 0;
        if (i <= n) {
            while (--son[i]) rt[i] = uninn(rt[i]);
            r = t[rt[i]].v; rt[i] = uninn(rt[i]);
            l = t[rt[i]].v; rt[i] = uninn(rt[i]);
        }
        t[++tot].v = l + a[i]; t[++tot].v = r + a[i];
        rt[i] = merge(rt[i], merge(tot, tot - 1));
        rt[fa[i]] = merge(rt[fa[i]], rt[i]);
    }
    while (son[1]--) rt[1] = uninn(rt[1]);
    while (rt[1]) { sum -= t[rt[1]].v; rt[1] = uninn(rt[1]); }
    cout << sum << endl;
}

signed main() {
    // freopen(".in","r",stdin);
    // freopen(".out","w",stdout);
    // read(T);
    while (T--) solve();
    return 0;
}