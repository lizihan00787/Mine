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

namespace CG {
    const double eps = 1e-9;
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
        line(pt _s = pt(0, 0), pt _t = pt(0, 0)) { s = _s, t = _t; }
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
        inline double area() { // 面积
            double ans = 0;
            for (int i = 1; i < pts.size() - 1; ++i) ans += (pts[i] - pts[0]) ^ (pts[nxt(i)] - pts[0]);
            return Abs(ans) / 2;
        }
    };
}
using Polygon::polygon;

namespace Hull {
    inline polygon SI(vector<line> p) {
        int n = (int)(p.size());
        sort(p.begin(), p.end());
        vector<line> s(n + 10), vec(n + 10);
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
        q[r + 1] = cross_LL(s[r], s[l]), ++r;
        polygon res;
        for (int j = l + 1; j <= r; ++j) res.pts.emplace_back(q[j]);
        return res;
    }
}
using Hull::SI;

int n, m;
vector<line> a;

inline void solve() {
    read(n);
    for (int i = 1; i <= n; ++i) {
        read(m);
        vector<pt> w;
        for (int j = 1; j <= m; ++j) {
            double x, y;
            scanf("%lf%lf", &x, &y);
            w.emplace_back(pt(x, y));
        }
        for (int j = 0; j < m; ++j) printf("%.3lf %.3lf\n", w[j].x, w[j].y);
        for (int j = 0; j < m; ++j) a.emplace_back(line(w[j], w[(j + 1) % m]));
    }
    polygon res = SI(a);
    double ans = res.area();
    printf("%.3lf\n", ans);
}

signed main() {
    // freopen(".in","r",stdin);
    // freopen(".out","w",stdout);
    // read(T);
    while (T--) solve();
    return 0;
}