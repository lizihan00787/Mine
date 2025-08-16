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
const double eps = 1e-8;
struct pt {
    double x, y;
    pt(double _x = 0, double _y = 0) { x = _x, y = _y; }
    inline double len() { return sqrt(x * x + y * y); }
} O;
typedef pt vec;
inline bool cmpx(const pt &a, const pt &b) { return (a.x != b.x) ? a.x < b.x : a.y < b.y; }
inline vec operator + (const vec &a, const vec &b) { return vec(a.x + b.x, a.y + b.y); }
inline vec operator - (const vec &a, const vec &b) { return vec(a.x - b.x, a.y - b.y); }
inline vec operator * (const vec &x, double y) { return vec(x.x * y, x.y * y); }
inline vec operator / (const vec &x, double y) { return vec(x.x / y, x.y / y); }
inline double operator ^ (const vec &a, const vec &b) { return a.x * b.y - a.y * b.x; }
inline double operator * (const vec &a, const vec &b) { return a.x * b.x + a.y * b.y; }
inline double angle(const vec &a) { return atan2(a.y, a.x); }
inline int dcmp(double x) { return (x < -eps ? -1 : (x > eps ? 1 : 0)); }
inline double dis_PP(pt a, pt b) { return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y)); }
inline bool operator < (const pt &a, const pt &b) { double p = angle(a - O), q = angle(b - O); return p != q ? p < q : dis_PP(a, O) < dis_PP(b, O); }

inline vector<pt> Graham(vector<pt> vec) {
    int n = ((int)vec.size());
    for (int i = 1; i < n; ++i) if (vec[i].y < vec[0].y || (vec[i].y == vec[0].y && vec[i].x < vec[0].x)) swap(vec[0], vec[i]);
    O = vec[0];
    sort(vec.begin() + 1, vec.end());
    vector<pt> s(n + 1);
    int ed = 0;
    for (int i = 0; i < n; ++i) {
        while (ed >= 2 && dcmp((s[ed] - s[ed - 1]) ^ (vec[i] - s[ed - 1])) <= 0) --ed;
        s[++ed] = vec[i];
    }
    s[++ed] = vec[0];
    vector<pt> res;
    for (int i = 1; i <= ed; ++i) res.emplace_back(s[i]);
    return res;
}
pt q[N];

inline void solve() {
    read(n);
    pt tmp;
    vector<pt> p(n);
    for (int i = 0; i < n; ++i) scanf("%lf%lf", &p[i].x, &p[i].y);
    p = Graham(p);
    int n = (int)(p.size());
    double ans = 0;
    for (int i = 0; i < n - 1; ++i) ans += 1.0 * (p[i + 1] - p[i]).len();
    printf("%.2lf\n", ans);
}

signed main() {
    // freopen("P2742_1.in","r",stdin);
    // freopen(".out","w",stdout);
    // read(T);
    while (T--) solve();
    return 0;
}