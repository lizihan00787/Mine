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
    const double eps = 1e-8;
    const double theta = 1.0 / 180 * acos(-1);
    const double Cos = cos(theta), Sin = sin(theta);
    struct pt {
        double x, y;
        pt(double _x = 0, double _y = 0) { x = _x, y = _y; }
        double len() { return sqrt(x * x + y * y); }
    };
    typedef pt vec;
    inline vec operator + (const vec &a, const vec &b) { return vec(a.x + b.x, a.y + b.y); }
    inline vec operator - (const vec &a, const vec &b) { return vec(a.x - b.x, a.y - b.y); }
    inline vec operator * (const vec &a, double b) { return vec(a.x * b, a.y * b); }
    inline vec operator / (const vec &a, double b) { return vec(a.x / b, a.y / b); }
    inline double operator * (const vec &a, const vec &b) { return a.x * b.x + a.y * b.y; }
    inline double operator ^ (const vec &a, const vec &b) { return a.x * b.y - a.y * b.x; }
    inline double angle(const vec &a) { return atan2(a.y, a.x); }
    inline int dcmp(double x) { return (x < -eps ? -1 : (x > eps ? 1 : 0)); }
    inline double Abs(double x) { return x * dcmp(x); }
    inline bool operator < (const pt &a, const pt &b) { return a.x < b.x; }
    inline vec rotate(vec a) {
        double x = a.x * Cos - a.y * Sin;
        double y = a.x * Sin + a.y * Cos;
        return vec(x, y);
    }
    inline double dis_PP(pt a, pt b) { return (a - b).len(); }
    struct line {
        pt s, t;
        line(pt _s = pt(0, 0), pt _t = pt(0, 0)) { s = _s, t = _t; }
    };
    inline pt cross_LL(line a, line b) {
        pt x = a.t - a.s, y = b.t - b.s, z = a.s - b.s;
        return a.s + x * ((y ^ z) / (x ^ y));
    }
}
using namespace CG;
namespace Circle {
    struct circle {
        double r;
        pt o;
        circle(pt _o = pt(0, 0), double _r = 0) { o = _o, r = _r; }
        circle(pt A, pt B, pt C) {
            pt D = (A + B) / 2, E = (B + C) / 2;
            o = cross_LL(line(D, D + vec((B - A).y, -(B - A).x)), line(E, E + vec((C - B).y, -(C - B).x)));
            r = dis_PP(o, A);
        }
        inline bool include(pt p) { return dcmp(r - dis_PP(p, o)) >= 0; }
    };
    inline double mincv(const vector<pt> &p, int l, int r) {
        if (l > r) return 0;
        vector<pt> vec;
        for (int i = l; i <= r; ++i) vec.emplace_back(p[i]);
        random_shuffle(vec.begin(), vec.end());
        circle c = circle(0, 0);
        int n = (int)(vec.size());
        for (int i = 0; i < n; ++i) {
            if (!c.include(vec[i])) {
                c = circle(vec[i], 0);
                for (int j = 0; j < i; ++j) {
                    if (!c.include(vec[j])) {
                        c = circle((vec[i] + vec[j]) / 2.0, dis_PP(vec[i], vec[j]) / 2.0);
                        for (int k = 0; k < j; ++k)
                            if (!c.include(vec[k])) c = circle(vec[i], vec[j], vec[k]);
                    }
                }
            }
        }
        return c.r;
    }
}
using namespace Circle;

int n;

signed main() {
    while(read(n), n != 0) {
        vector<pt> a(n);
        for (int i = 0; i < n; ++i) scanf("%lf%lf", &a[i].x, &a[i].y);
        double R = 1e9;
        for (int p = 1; p <= 180; ++p) {
            for (int i = 0; i < n; ++i) a[i] = rotate(a[i]);
            sort(a.begin(), a.end());
            int l = 0, r = n - 1;
            while (l <= r) {
                int mid = (l + r) / 2;
                double r1 = mincv(a, 0, mid), r2 = mincv(a, mid + 1, n - 1); 
                // printf("%.2lf %.2lf\n", r1, r2);
                if (min(r1, r2) > R) break;
                if (r1 < r2) l = mid + 1;
                else r = mid - 1;
                R = min(R, max(r1, r2));
            }
        }
        printf("%.2lf\n", R);
        a.clear();
    }
    return 0;
}