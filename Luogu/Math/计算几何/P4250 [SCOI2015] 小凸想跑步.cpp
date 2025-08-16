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
    const double eps = 1e-6;
    struct pt {
        double x, y;
        pt(double _x = 0, double _y = 0) { x = _x, y = _y; }
        inline double len() { return sqrt(x * x + y * y); }
    };
    typedef pt vec;
    inline vec operator + (const vec &a, const vec &b) { return vec(a.x + b.x, a.y + b.y); }
    inline vec operator - (const vec &a, const vec &b) { return vec(a.x - b.x, a.y - b.y); }
    inline vec operator * (const vec &a, double b) { return vec(a.x * b, a.y * b); }
    inline vec operator / (const vec &a, double b) { return vec(a.x / b, a.y / b); }
    inline double operator * (const vec &a, const vec &b) { return (a.x * b.x + a.y * b.y); }
    inline double operator ^ (const vec &a, const vec &b) { return (a.x * b.y - a.y * b.x); }
    inline int dcmp(double x) { return x < -eps ? -1 : (x > eps ? 1 : 0); }
    inline double angle(const vec &a) { return atan2(a.y, a.x); }
    inline bool cmpx (const pt &a, const pt &b) { return a.x == b.x ? a.y < b.y : a.x < b.y; }
    inline double Abs(double x) { return x * dcmp(x); }
    struct line {
        pt s, t;
        line(pt _s = pt(0, 0), pt _t = pt(0, 0)) { s = _s, t = _t; }
    };
    inline bool operator<(const line &a, const line &b) {
        double a1 = angle(a.t - a.s), a2 = angle(b.t - b.s);
        if (dcmp(a2 - a1) != 0) return dcmp(a2 - a1) > 0;
        return dcmp((b.t - a.s) ^ (a.t - a.s)) > 0;
    }
    inline double ang(line a) { return angle(a.t - a.s); }
    inline pt cross_LL(line a, line b) {
        pt x = a.t - a.s, y = b.t - b.s, z = a.s - b.s;
        return a.s + x * ((y ^ z) / (x ^ y));
    }
}
using namespace CG;
namespace Hull {
    inline vector<pt> SI(vector<line> q) {
        int n = q.size();
        sort(q.begin(), q.end());
        vector<line> li(n + 2), L(n + 2);
        vector<pt> p(n + 2);
        int len = 0;
        for (int i = 0; i < n; ++i) {
            if (i > 0 && !dcmp(ang(q[i]) - ang(q[i - 1]))) continue;
            L[++len] = q[i];
        }
        int l = 1, r = 0;
        for (int i = 1; i <= len; ++i) {
            while (l < r && dcmp((L[i].t - p[r]) ^ (L[i].s - p[r])) >= 0) --r;
            while (l < r && dcmp((L[i].t - p[l + 1]) ^ (L[i].s - p[l + 1])) >= 0) ++l;
            li[++r] = L[i];
            if (r > l) p[r] = cross_LL(li[r], li[r - 1]);
        }
        while (l < r && dcmp((li[l].t - p[r]) ^ (li[l].s - p[r])) >= 0) --r;
        while (l < r && dcmp((li[r].t - p[l + 1]) ^ (li[r].s - p[l + 1])) >= 0) ++l;
        p[r + 1] = cross_LL(li[r], li[l]), ++r;
        vector<pt> P;
        for (int j = l + 1; j <= r; ++j) P.emplace_back(p[j]);
        return P;
    }
    inline double area(vector<pt> pts) {
        double ans = 0;
        int n = (int)(pts.size());
        for (int i = 1; i < n - 1; ++i) ans += (pts[i] - pts[0]) ^ (pts[(i + 1) % n] - pts[0]);
        return Abs(ans) / 2;
    }
}
using namespace Hull;

int n;
vector<pt> p;
vector<line> a;

inline void solve() {
    read(n);
    for (int i = 0; i < n; ++i) {
        double x, y;
        scanf("%lf%lf", &x ,&y);
        p.emplace_back(pt(x, y));
    }
    for (int i = 0; i < n; ++i) a.emplace_back(line(p[i], p[(i + 1) % n]));
    double S = area(p);
    for (int i = 1; i < n; ++i) {
        int x = i, y = (i + 1) % n;
        double A = p[y].y - p[x].y - p[1].y + p[0].y, B = p[1].x - p[0].x + p[x].x - p[y].x, C = -p[y].x * p[x].y + p[y].y * p[x].x + p[1].x * p[0].y - p[1].y * p[0].x;
        if (dcmp(B) != 0) a.push_back(line(pt(0, C / B), pt(-B, A + C / B)));
        else a.push_back(line(pt(C / A, 0), pt(C / A - B, A)));
    }
    vector<pt> ans = SI(a);
    printf("%.4lf\n", area(ans) / S);
}

signed main() {
    // freopen(".in","r",stdin);
    // freopen(".out","w",stdout);
    // read(T);
    while (T--) solve();
    return 0;
}