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

const int N = 9, M = 55;

namespace CG {
    struct pt {
        double x, y;
        pt(double _x = 0, double _y = 0) { x = _x, y = _y; }
    };
    typedef pt vec;
    inline vec operator + (const vec &a, const vec &b) { return vec(a.x + b.x, a.y + b.y); }
    inline vec operator - (const vec &a, const vec &b) { return vec(a.x - b.x, a.y - b.y); }
    inline vec operator * (const vec &a, double b) { return vec(a.x * b, a.y * b); }
    inline vec operator / (const vec &a, double b) { return vec(a.x / b, a.y / b); }
    inline double Len(const vec &a) { return sqrt(a.x * a.x + a.y * a.y); }
    inline double operator * (const vec &a, const vec &b) { return a.x * b.x + a.y * b.y; }
    inline double operator ^ (const vec &a, const vec &b) { return a.x * b.y - a.y * b.x; }
    struct line {
        pt s, t;
        line(pt _x = pt(0, 0), pt _y = pt(0, 0)) { s = _x, t = _y; }
    };
    inline pt Foot(pt a, line b) {
        pt x = a - b.s, y = a - b.t, z = b.t - b.s;
        double s1 = x * z, s2 = -1.0 * (y * z);
        return b.s + z * (s1 / (s1 + s2));
    }
    inline pt reflect(pt a, line b) { return a + (Foot(a, b) - a) * 2.0; }
}
using namespace CG;

const double eps = 1e-7;

int n, m;
vector<line> opts;

int query(const pt o, const int T) {
    if (T == -1) return (eps <= o.x && o.x <= 100.0 - eps) && (eps <= o.y && o.y <= 100.0 - eps);
    double cross = ((opts[T].s - o) ^ (opts[T].t - o));
    if (cross < -eps) return 0;
    if (-eps <= cross && cross <= eps) return 0;
    return query(o, T - 1) + query(reflect(o, opts[T]), T - 1);
}

inline void solve() {
    read(n);
    for (int i = 1; i <= n; ++i) {
        double x1, x2, y1, y2;
        scanf("%lf%lf%lf%lf", &x1, &y1, &x2, &y2);
        opts.emplace_back(line(pt(x1, y1), pt(x2, y2)));
    }
    read(m);
    while (m--) {
        double x, y;
        scanf("%lf%lf", &x, &y);
        printf("%d\n", query(pt(x, y), n - 1));
    }
}

signed main() {
    // freopen(".in","r",stdin);
    // freopen(".out","w",stdout);
    // read(T);
    while (T--) solve();
    return 0;
}