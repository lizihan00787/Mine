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
    const double eps = 1e-10;
	struct pt{
		double x, y;
		pt(): x(0), y(0) {}
		pt(double X, double Y): x(X), y(Y) {}
		double len() { return sqrt(x * x + y * y); }
	}; pt O;
    typedef pt vec;
    inline vec operator + (const vec &a, const vec &b) { return vec(a.x + b.x, a.y + b.y); }
    inline vec operator - (const vec &a, const vec &b) { return vec(a.x - b.x, a.y - b.y); }
    inline vec operator * (const vec &a, double b) { return vec(a.x * b, a.y * b); }
    inline vec operator / (const vec &a, double b) { return vec(a.x / b, a.y / b); }
    inline int dcmp(double a) { return (a < -eps ? -1 : (a > eps ? 1 : 0)); }
    inline double Abs(double x) { return x * dcmp(x); }
    inline double angle(const vec &a) { return atan2(a.y, a.x); }
    inline double operator * (const vec &a, const vec &b) { return a.x * b.x + a.y * b.y; }
    inline double operator ^ (const vec &a, const vec &b) { return a.x * b.y - a.y * b.x; }
	inline double dis_PP(pt a, pt b) { return (a - b).len(); }
	inline double S(pt a, pt b, pt c) { return Abs(((c - a) ^ (c - b)) / 2.0); }
    bool operator < (pt a, pt b) {
		double p = angle(a - O), q = angle(b - O);
		return p != q ? p < q : dis_PP(a, O) < dis_PP(b, O);
    }
    vector<pt> con(vector<pt> vec) {
        int n = ((int)vec.size());
        for (int i = 1; i < n; ++i) if (vec[i].x < vec[0].x || (vec[i].x == vec[0].x && vec[i].y < vec[0].y)) swap(vec[0], vec[i]);
        O = vec[0];
        sort(vec.begin() + 1, vec.end());
        vector<int> s(n + 1);
        int ed = 0;
        for (int i = 0; i < n; ++i) {
            while (ed >= 2 && dcmp((vec[s[ed]] - vec[s[ed - 1]]) ^ (vec[i] - vec[s[ed - 1]])) <= 0) --ed;
            s[++ed] = i;
        }
        vector<pt> res;
        for (int i = 1; i <= ed; ++i) res.emplace_back(vec[s[i]]);
        return res;
    }
}
using namespace CG;

const int N = 2020;

int n;
vector<pt> a;

inline void solve() {
    read(n);
    for (int i = 1; i <= n; ++i) {
        double x, y;
        scanf("%lf%lf", &x, &y);
        a.emplace_back(pt(x, y));
    }
    vector<pt> res = con(a);
    n = res.size();
    if (n < 3) return (void)(puts("0.000"));
    if (n < 4) {
        double ans = 0;
        for (int i = 1; i < n - 1; ++i) ans += (res[i] - res[0]) ^ (res[(i + 1) % n] - res[0]);
        return (void)(printf("%.3lf\n", Abs(ans) / 2));
    }
    double ans = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1, x = i, y = (i + 1) % n; j < n; ++j) {
            for(; dcmp(S(res[j], res[i], res[x]) - S(res[j], res[i], res[(x + 1) % n])) < 0; x = (x + 1) % n);
            for(; dcmp(S(res[j], res[i], res[y]) - S(res[j], res[i], res[(y + 1) % n])) < 0; y = (y + 1) % n);
            ans = max(ans, S(res[i], res[j], res[x]) + S(res[i], res[j], res[y]));
            // printf("%d %d %d %d %.3lf\n", i, j, x, y, S(res[i], res[j], res[x]) + S(res[i], res[j], res[y]));
        }
    }
    printf("%.3lf\n", ans);
}

signed main() {
    // freopen(".in","r",stdin);
    // freopen(".out","w",stdout);
    // read(T);
    while (T--) solve();
    return 0;
}