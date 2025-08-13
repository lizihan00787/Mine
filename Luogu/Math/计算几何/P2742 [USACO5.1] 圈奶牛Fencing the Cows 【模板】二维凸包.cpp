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

const int N = 1e5 + 20;

int n;
struct pt {
    double x, y;
    pt(double _x = 0, double _y = 0) { x = _x, y = _y; }
} p[N];
typedef pt vec;
inline vec operator + (const vec &a, const vec &b) { return vec(a.x + b.x, a.y + b.y); }
inline vec operator - (const vec &a, const vec &b) { return vec(a.x - b.x, a.y - b.y); }
inline vec operator * (const vec &a, double b) { return vec(a.x * b, a.y * b); }
inline vec operator / (const vec &a, double b) { return vec(a.x / b, a.y / b); }
inline double Len(const vec &a) { return sqrt(a.x * a.x + a.y * a.y); }
inline double operator * (const vec &a, const vec &b) { return a.x * b.x + a.y * b.y; }
inline double operator ^ (const vec &a, const vec &b) { return a.x * b.y - a.y * b.x; }

bool cmp(pt a, pt b) {
    double tmp = (a - p[1]) ^ (b - p[1]);
    if (tmp > 0) return 1;
    else if (tmp == 0 && Len(a) < Len(b)) return 1;
    return 0;
}

int cnt = 1;
pt s[N];

inline void solve() {
    read(n);
    pt tmp;
    for (int i = 1; i <= n; ++i) {
        scanf("%lf%lf", &p[i].x, &p[i].y);
        if (i != 1 && p[i].y < p[1].y) tmp = p[i], p[i] = p[1], p[1] = tmp;
    }
    sort(p + 2, p + n + 1, cmp);
    s[1] = p[1];
    for (int i = 2; i <= n; ++i) {
        while (cnt > 1 && ((s[cnt] - s[cnt - 1]) ^ (p[i] - s[cnt])) < 0) cnt--;
        s[++cnt] = p[i];
    }
    s[cnt + 1] = p[1];
    double ans = 0;
    for (int i = 1; i <= cnt; ++i) ans += 1.0 * Len(s[i + 1] - s[i]);
    printf("%.2lf\n", ans);
}

signed main() {
    // freopen(".in","r",stdin);
    // freopen(".out","w",stdout);
    // read(T);
    while (T--) solve();
    return 0;
}