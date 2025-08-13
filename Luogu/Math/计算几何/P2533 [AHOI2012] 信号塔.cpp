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
        double len() { return sqrt(x * x + y * y); }
        pt(double _x = 0, double _y = 0) { x = _x, y = _y; }
    };
    typedef pt vec;
    inline vec operator + (const vec &a, const vec &b) { return vec(a.x + b.x, a.y + b.y); }
    inline vec operator - (const vec &a, const vec &b) { return vec(a.x - b.x, a.y - b.y); }
    inline vec operator * (const vec &a, double b) { return vec(a.x * b, a.y * b); }
    inline vec operator / (const vec &a, double b) { return vec(a.x / b, a.y / b); }
    inline double operator * (const vec &a, const vec &b) { return a.x * b.x + a.y * b.y; }
    inline double operator ^ (const vec &a, const vec &b) { return a.x * b.y - a.y * b.x; }
    inline int dcmp(double a) { return (a < -eps ? -1 : (a > eps ? 1 : 0)); }
    inline double Abs(double x) { return x * dcmp(x); }
    inline double angle(const vec &a) { return atan2(a.y, a.x); }
    inline vec rotate(vec a, double theta) { //逆时针转
        double x = a.x * cos(theta) - a.y * sin(theta);
        double y = a.x * sin(theta) + a.y * cos(theta);
        return pt(x, y);
    }
    inline vec rotate_90(vec a) { return pt(a.y, -a.x); } // 顺时针
    struct line {
        pt s, t;
        line(pt _s = pt(0, 0), pt _t = pt(0, 0)) { s = _s, t = _t; }
    };
    inline double ang(const line &l) { return angle(l.t - l.s); }
    inline bool operator < (const line &a, const line &b) {
        double x = ang(a), y = ang(b);
        if (dcmp(y - x) != 0) return dcmp(y - x) > 0;
        return dcmp((b.t - a.s) ^ (a.t - b.s)) > 0;
    }
    inline double dis_PP(pt a, pt b) { return (a - b).len(); }
    inline pt cross_LL(line a, line b) {
        pt x = a.t - a.s, y = b.t - b.s, z = a.s - b.s;
        return a.s + x * ((y ^ z) / (x ^ y));
    }
}
using namespace CG;
namespace Circle {
    struct circle {
        pt o;
        double r;
        circle(pt _o = pt(0, 0), double _r = 0) { o = _o, r = _r; }
        circle(pt A, pt B, pt C) {
            pt D = (A + B) / 2, E = (B + C) / 2;
            o = cross_LL(line(D, D + rotate_90(B - A)), line(E, E + rotate_90(C - B)));
            r = dis_PP(o, A);
        }
        inline bool include(pt p) { return dcmp(r - dis_PP(o, p)) >= 0; }
    };
    inline circle mincv(const vector<pt> p) {
        int n = (int)(p.size());
        circle c = circle(0, 0);
        for (int i = 0; i < n; ++i) {
            if (!c.include(p[i])) {
                c = circle(p[i], 0);
                for (int j = 0; j < i ; ++j) {
                    if (!c.include(p[j])) {
                        c = circle((p[i] + p[j]) / 2.0, dis_PP(p[i], p[j]) / 2.0);
                        for (int k = 0; k < j; ++k)
                            if (!c.include(p[k])) c = circle(p[i], p[j], p[k]);
                    }
                }
            }
        }
        return c;
    }
}
using namespace Circle;

const int N = 1e6 + 20;

int n;
vector<pt> a;

inline void solve() {
    read(n);
    for (int i = 1; i <= n; ++i) {
        double x, y;
        scanf("%lf%lf", &x, &y);
        a.emplace_back(pt(x, y));
    }
    random_shuffle(a.begin(), a.end());
    circle ans = mincv(a);
    printf("%.2lf %.2lf ", ans.o.x, ans.o.y);
    printf("%.2lf\n", ans.r);
}

signed main() {
    // freopen(".in","r",stdin);
    // freopen(".out","w",stdout);
    // read(T);
    while (T--) solve();
    return 0;
}