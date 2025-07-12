#include <bits/stdc++.h>
#define endl '\n'
#define ll long long
#define int unsigned int
#define PII pair<int, int>
#define mk(a, b) make_pair(a, b)
#define rep(i, a, b) for (int i = (a); i <= (b); ++i)
#define per(i, a, b) for (int i = (a); i >= (b); --i)
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

const int N = 4e5+20, K = 10;
std::mt19937 rnd(233);

int n, m, rt, fac[N], C[K + 5][K + 5];

namespace FHQ_Treap {
    #define lson (t[rt].l)
    #define rson (t[rt].r)
    struct node {
        int l, r, siz, val, key;
        int res[K + 5];
    } t[N];
    int cnt=0;
    void pushup(int rt) {
        t[rt].siz = t[lson].siz + t[rson].siz + 1;
        fac[0] = 1;
        rep (i, 1, K) fac[i] = fac[i - 1] * (t[lson].siz + 1);
        rep (i, 0, K) {
            t[rt].res[i] = t[lson].res[i] + t[rt].val * fac[i];
            rep (j, 0, i) t[rt].res[i] += C[i][j] * fac[i - j] * t[rson].res[j];
        }
    }
    int newnode(int val) {
        t[++cnt].siz = 1;
        t[cnt].key = rnd();
        t[cnt].val = val;
        rep (i, 0, K) t[cnt].res[i] = val;
        return cnt;
    }
    void split(int rt, int &l, int &r, int k) {
        if (!rt) 
            return (void)(l = r = 0);
        if (t[lson].siz < k) {
            l = rt;
            split(rson, rson, r, k - t[lson].siz - 1);
        }
        else {
            r = rt;
            split(lson, l, lson, k);
        }
        pushup(rt);
    }
    int merge(int x, int y) {
        if (!x || !y) return x + y;
        if (t[x].key < t[y].key) {
            t[x].r = merge(t[x].r, y);
            return pushup(x), x;
        }
        else {
            t[y].l = merge(x, t[y].l);
            return pushup(y), y;
        }
    }
}
using namespace FHQ_Treap;

inline void solve() {
    read(n);
    C[0][0] = 1;
    rep (i, 1, K) {
        C[i][0] = 1;
        rep (j, 1, i)
            C[i][j] = (C[i - 1][j] + C[i - 1][j - 1]);
    }
    rep (i, 1, n) {
        int x;
        read(x);
        rt = merge(rt, newnode(x));
    }
    read(m);
    while (m--) {
        int x, y, z, a, b, k;
        char op[2];
        scanf("%s", op);
        if (op[0] == 'I') {
            read(a, b);
            split(rt, x, y, a);
            rt  = merge(merge(x, newnode(b)), y);
        }
        else if (op[0] == 'D') {
            read(a);
            split(rt, x, y, a); split(y, y, z, 1);
            rt = merge(x, z);
        }
        else if (op[0] == 'R') {
            read(a, b);
            split(rt, x, y, a); split(y, y, z, 1);
            t[y].val = b; pushup(y);
            rt = merge(merge(x, y), z);
        }
        else if (op[0] == 'Q') {  
            read(a, b, k);
            split(rt, x, y, a); split(y, y, z, b - a + 1);
            cout << t[y].res[k] << endl;
            rt = merge(merge(x, y), z);
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