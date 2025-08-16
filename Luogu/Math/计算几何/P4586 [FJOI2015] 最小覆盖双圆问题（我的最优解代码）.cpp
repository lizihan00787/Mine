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

const double eps = 1e-8;
const double theta = 1.0 / 180 * acos(-1);
const double Cos = cos(theta), Sin = sin(theta);
struct pt {
    double x, y;
    pt(double _x = 0, double _y = 0) { x = _x, y = _y; }
};
typedef pt vec;
inline vec operator + (const vec &a, const vec &b) { return vec(a.x + b.x, a.y + b.y); }
inline vec operator - (const vec &a, const vec &b) { return vec(a.x - b.x, a.y - b.y); }
inline vec operator * (const vec &a, double b) { return vec(a.x * b, a.y * b); }
inline vec operator / (const vec &a, double b) { return vec(a.x / b, a.y / b); }
inline double operator * (const vec &a, const vec &b) { return a.x * b.x + a.y * b.y; }
inline double operator ^ (const vec &a, const vec &b) { return a.x * b.y - a.y * b.x; }
inline int dcmp(double x) { return (x < -eps ? -1 : (x > eps ? 1 : 0)); }
inline bool operator < (const pt &a, const pt &b) { return a.x < b.x; }
inline vec rotate(vec a) {
    double x = a.x * Cos - a.y * Sin;
    double y = a.x * Sin + a.y * Cos;
    return pt(x, y);
}
inline double dis_PP(pt a, pt b) {return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y)); }
struct line {
    pt s, t;
    line(pt _s = pt(0, 0), pt _t = pt(0, 0)) { s = _s, t = _t; }
};
inline pt cross_LL(line a, line b) { return a.s + (a.t - a.s) * (((b.t - b.s) ^ (a.s - b.s)) / ((a.t - a.s) ^ (b.t - b.s))); }
struct circle {
    double r;
    pt o;
    circle(pt _o = pt(0, 0), double _r = 0) { o = _o, r = _r; }
    inline circle(pt A, pt B, pt C) {
        pt D = (A + B) / 2, E = (B + C) / 2;
        o = cross_LL(line(D, D + vec((B - A).y, -(B - A).x)), line(E, E + vec((C - B).y, -(C - B).x)));
        r = dis_PP(o, A);
    }
    inline bool include(pt p) { return dcmp(r - dis_PP(p, o)) >= 0; }
};
pt ve[1005];
double R = 1e9;
double mincv(pt *p, int l, int r) {
    if (l > r) return 0;
    int n = 0;
    for (int i = l; i <= r; ++i) ve[++n] = p[i];
    random_shuffle(ve + 1, ve + n + 1);
    circle c = circle(0, 0);
    for (int i = 1; i <= n; ++i) {
        if (!c.include(ve[i])) {
            c = circle(ve[i], 0);
            if (c.r > R) continue;
            for (int j = 1; j < i; ++j) {
                if (!c.include(ve[j])) {
                    c = circle((ve[i] + ve[j]) / 2.0, dis_PP(ve[i], ve[j]) / 2.0);
                    if (c.r > R) continue;
                    for (int k = 1; k < j; ++k) 
                        if (!c.include(ve[k])) {
                            c = circle(ve[i], ve[j], ve[k]);
                            if (c.r > R) continue;
                        }
                }
            }
        }
    }
    return c.r;
}

int n;
pt a[1005];

signed main() {
    while(read(n), n != 0) {
        R = 1e9;
        for (int i = 1; i <= n; ++i) scanf("%lf%lf", &a[i].x, &a[i].y);
        for (int p = 1; p <= 180; ++p) {
            for (int i = 1; i <= n; ++i) a[i] = rotate(a[i]);
            sort(a + 1, a + n + 1);
            int l = 1, r = n;
            while (l <= r) {
                int mid = (l + r) / 2;
                double r1 = mincv(a, 1, mid), r2 = mincv(a, mid + 1, n); 
                // printf("%.2lf %.2lf\n", r1, r2);
                if (min(r1, r2) > R) break;
                if (r1 < r2) l = mid + 1;
                else r = mid - 1;
                R = min(R, max(r1, r2));
            }
        }
        printf("%.2lf\n", R);
    }
    return 0;
}