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

double a, b, c, d, l, r;

inline double f(double x) { return (c * x + d) / (a * x + b); }
inline double simpson(double l, double r) {
    double mid = (l + r) / 2;
    return (f(l) + f(r) + 4 * f(mid)) * (r - l) / 6;
}
double ask(double l, double r, double eps, double ans) {
    double mid = (l + r) / 2;
    double _l = simpson(l, mid), _r = simpson(mid, r);
    if (fabs(_l + _r - ans) <= 15 * eps) return (_l + _r - ans) / 15 + _l + _r;
    return ask(l, mid, eps / 2, _l) + ask(mid, r, eps / 2, _r);
}
inline double asr(double l,double r,double eps) {
	return ask(l,r,eps,simpson(l, r));
}

inline void solve() {
    scanf("%lf%lf%lf%lf%lf%lf", &a, &b, &c, &d, &l, &r);
    printf("%.6lf", asr(l, r, 1e-6));
}

signed main() {
    // freopen(".in","r",stdin);
    // freopen(".out","w",stdout);
    // read(T);
    while (T--) solve();
    return 0;
}