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

double a, l, r;
const double eps = 1e-10;

inline double f(double x) { return pow(x, (a/x) - x); }
inline double simpson(double l, double r) {
    double mid = (l + r) / 2;
    return (f(l) + f(r) + 4 * f(mid)) * (r - l) / 6;
}
double ask(double l, double r, double ans) {
    double mid = (l + r) / 2;
    double _l = simpson(l, mid), _r = simpson(mid, r);
    if (fabs(_l + _r - ans) <= 15 * eps) return _l + _r;
    return ask(l, mid, _l) + ask(mid, r, _r);
}

inline void solve() {
    scanf("%lf", &a);
    if (a < 0) return (void)(puts("orz"));
    printf("%.5lf", ask(eps, 15, simpson(l, r)));
}

signed main() {
    // freopen(".in","r",stdin);
    // freopen(".out","w",stdout);
    // read(T);
    while (T--) solve();
    return 0;
}