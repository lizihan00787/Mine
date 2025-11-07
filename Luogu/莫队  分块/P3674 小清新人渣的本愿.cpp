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

const int N = 1e5;

int n, m, siz;
int a[N + 10], id[N + 10];
bitset<N + 10> b1, b2;
int ans[N + 10];
int c[N + 10];
struct que {
    int op, l, r, x;
    int idd;
    bool operator < (const que &a) const {
        return id[l] == id[a.l] ? id[l] & 1 ? r < a.r : r > a.r : id[l] < id[a.l];
    }
} q[N + 10];

void add(int x) { if (c[x]++ == 0) b1[x] = 1, b2[N - x] = 1; }
void del(int x) { if (--c[x] == 0) b1[x] = 0, b2[N - x] = 0; }

inline void solve() {
    read(n, m);
    siz = sqrt(n);
    for (int i = 1; i <= n; ++i) read(a[i]), id[i] = (i - 1) / siz + 1;
    for (int i = 1; i <= m; ++i) read(q[i].op, q[i].l, q[i].r, q[i].x), q[i].idd = i;
    sort(q + 1, q + m + 1);
    int l = 1, r = 0;
    for (int i = 1; i <= m; ++i) {
        while (l > q[i].l) add(a[--l]);
        while (r < q[i].r) add(a[++r]);
        while (l < q[i].l) del(a[l++]);
        while (r > q[i].r) del(a[r--]);
        int op = q[i].op, x = q[i].x;
        if (op == 1) if ((b1 & (b1 << x)).any()) ans[q[i].idd] = 1;
        if (op == 2) if ((b1 & (b2 >> (N - x))).any()) ans[q[i].idd] = 1;
        if (op == 3) {
            for (int j = 1; j * j <= x; ++j) {
                if (x % j == 0) 
                if (b1[j] && b1[x / j]) { ans[q[i].idd] = 1; break; }
            }
        }
    }
    for (int i = 1; i <= m; ++i) puts(ans[i] ? "hana" : "bi");
}

signed main() {
    // freopen(".in","r",stdin);
    // freopen(".out","w",stdout);
    // read(T);
    while (T--) solve();
    return 0;
}