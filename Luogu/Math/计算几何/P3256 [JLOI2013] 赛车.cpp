#include <bits/stdc++.h>
#define endl '\n'
#define int long long
#define double long double 
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

namespace CG {
    const double eps = 1e-18;
    struct pt {
        double x, y;
        pt(double _x = 0, double _y = 0) { x = _x, y = _y; }
    };
    typedef pt vec;
    inline int dcmp(double x) { return (x < -eps) ? -1 : (x > eps ? 1 : 0); }
    inline vec operator + (const vec &a, const vec &b) { return vec(a.x + b.x, a.y + b.y); }
    inline vec operator - (const vec &a, const vec &b) { return vec(a.x - b.x, a.y - b.y); }
    inline vec operator * (const vec &a, double b) { return vec(a.x * b, a.y * b); }
    inline vec operator / (const vec &a, double b) { return vec(a.x / b, a.y / b); }
    inline double Len(const vec &a) { return sqrt(a.x * a.x + a.y * a.y); }
    inline double angle(const vec &a) { return atan2(a.y, a.x); }
    inline double Abs(double x) { return x * dcmp(x); }
    inline double operator * (const vec &a, const vec &b) { return (a.x * b.x + a.y * b.y); }
    inline double operator ^ (const vec &a, const vec &b) { return (a.x * b.y - a.y * b.x); }
    struct line {
        pt s, t;
        int id;
        line(pt _s = pt(0, 0), pt _t = pt(0, 0), int _id = 0) { s = _s, t = _t, id = _id; }
    };
    inline double ang(line a) { return angle(a.t - a.s); }
    inline bool operator < (const line &a, const line &b) {
        double x = angle(a.t - a.s), y = angle(b.t - b.s);
        if (dcmp(y - x) != 0) return dcmp(y - x) > 0;
        return dcmp((b.t - a.s) ^ (a.t - b.s)) > 0;
    }
    inline pt cross_LL(line a, line b) {
        pt x = a.t - a.s, y = b.t - b.s, z = a.s - b.s;
        return a.s + x * ((y ^ z) / (x ^ y));
    }
}
using namespace CG;

namespace Polygon {
    struct polygon {
        vector<pt> pts;
        inline pt &operator[](int x) { return pts[x]; }
        inline void clear() { pts.clear(); }
        inline int nxt(int x) { return x < pts.size() - 1 ? x + 1 : 0; }
    };
}
using Polygon::polygon;

const int N = 1e5 + 20, lim = 1e18 + 10;

namespace Hull {
    vector<line> s(N);
    inline int SI(vector<line> p) {
        int n = (int)(p.size());
        sort(p.begin(), p.end());
        vector<line> vec(n + 10);
        vector<pt> q(n + 10);
        int tot = 0, l = 1, r = 0;
        for (int i = 0; i < n; ++i) {
            if (i > 0 && !dcmp(ang(p[i]) - ang(p[i - 1]))) continue;
            vec[++tot] = p[i];
        }
        for (int i = 1; i <= tot; ++i) {
            while (l < r && dcmp((vec[i].t - q[r]) ^ (vec[i].s - q[r])) > 0) --r;
            while (l < r && dcmp((vec[i].t - q[l + 1]) ^ (vec[i].s - q[l + 1])) > 0) ++l;
            s[++r] = vec[i];
            if (r > l) q[r] = cross_LL(s[r], s[r - 1]);
        }
        while (l < r && dcmp((s[l].t - q[r]) ^ (s[l].s - q[r])) > 0) --r;
        while (l < r && dcmp((s[r].t - q[l + 1]) ^ (s[r].s - q[l + 1])) > 0) ++l;
        q[r + 1] = cross_LL(s[r], s[l]);
        if (r - l + 1 == 2) return 0;
        return r - l + 1;
    }
}
using namespace Hull;


int n, m;
double st[N], k[N];
int ans[N];
vector<line> a;

inline void solve() {
    read(n);
    for (int i = 1; i <= n; ++i) scanf("%Lf", &st[i]);
    for (int i = 1; i <= n; ++i) scanf("%Lf", &k[i]);
    a.emplace_back(line(pt(0, 0), pt(lim, 0), 0));a.emplace_back(line(pt(lim, 0), pt(lim, lim), 0));
    a.emplace_back(line(pt(lim, lim), pt(0, lim), 0));a.emplace_back(line(pt(0, lim), pt(0, 0), 0));
    for (int i = 1; i <= n; ++i) a.emplace_back(line(pt(0, st[i]), pt(1, st[i] + k[i]), i));
    int res = SI(a), tot = 0;
    for (int i = 1; i <= res; ++i) {
        for (int j = 1; j <= n; ++j) {
            if (st[j] == st[s[i].id] && k[j] == k[s[i].id]) ans[++tot] = j;
        }
    }
    sort(ans + 1, ans + tot + 1);
    printf("%lld\n", tot);
    for (int i = 1; i <= tot; ++i) printf("%lld ", ans[i]);
    puts("");
}

signed main() {
    // freopen(".in","r",stdin);
    // freopen(".out","w",stdout);
    // read(T);
    while (T--) solve();
    return 0;
}