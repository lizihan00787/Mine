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

const double pi = acos(-1), eps = 1e-12;

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
    inline double Len (const vec &a) { return sqrt(a.x * a.x + a.y * a.y); }
    inline double operator * (const vec &a, const vec &b) { return a.x * b.x + a.y * b.y; }
    inline double operator ^ (const vec &a, const vec &b) { return a.x * b.y - a.y * b.x; }
    inline vec ronate(vec a, double theta) {
        double x = a.x * cos(theta) - a.y * sin(theta);
        double y = a.x * sin(theta) + a.y * cos(theta);
        return pt(x, y);
    }
}
using namespace CG;

const int N = 1e5 + 20;

int n;
double a, b, r;

int cnt = 1, tot = 0;
pt s[N], p[N];

bool cmp1(pt a, pt b) {
    double tmp = (a - p[1]) ^ (b - p[1]);
    if (tmp > 0) return 1;
    else if (tmp == 0 && Len(a) < Len(b)) return 1;
    return 0;
}
bool cmp2(pt a, pt b) {
    return a.y == b.y ? a.x < b.x : a.y < b.y;
}

inline void solve() {
    read(n);
    scanf("%lf%lf%lf", &b, &a, &r); // 注意题目说的是高和宽，故a和b要反过来
    a /= 2.0, b /= 2.0;
    for (int i = 1; i <= n; ++i) {
        double x, y, t;
        scanf("%lf%lf%lf", &x, &y, &t);
        x += eps, y += eps, t += eps;
        pt center = pt(x, y);
        p[++tot] = (ronate(pt(a - r, b - r), t) + center);
        if (p[tot].y < p[1].y) swap(p[tot], p[1]);
        p[++tot] = (ronate(pt(r - a, b - r), t) + center);
        if (p[tot].y < p[1].y) swap(p[tot], p[1]);
        p[++tot] = (ronate(pt(a - r, r - b), t) + center);
        if (p[tot].y < p[1].y) swap(p[tot], p[1]);
        p[++tot] = (ronate(pt(r - a, r - b), t) + center);
        if (p[tot].y < p[1].y) swap(p[tot], p[1]);
    }
    sort(p + 2, p + tot + 1, cmp1);
    s[1] = p[1];
    for (int i = 2; i <= tot; ++i) {
        while (cnt > 1 && ((s[cnt] - s[cnt - 1]) ^ (p[i] - s[cnt])) <= 0) cnt--; // 这里要取等因为题中可能会出现两个一样的点，此时应该只加入一个点
        s[++cnt] = p[i];
    }
    s[cnt + 1] = p[1];
    double ans = 0;
    for (int i = 1; i <= cnt; ++i) ans += 1.0 * Len(s[i + 1] - s[i]);
    ans += pi * 2.0 * r;
    printf("%.2lf\n", ans);
}

signed main() {
    // freopen(".in","r",stdin);
    // freopen(".out","w",stdout);
    // read(T);
    while (T--) solve();
    return 0;
}