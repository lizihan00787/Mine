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
    inline int dcmp(double x) { return (x < -eps) ? -1 : (x > eps ? 1 : 0); }
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
    inline double angle(const vec &a) { return atan2(a.y, a.x); }
    inline double operator * (const vec &a, const vec &b) { return a.x * b.x + a.y * b.y; }
    inline double operator ^ (const vec &a, const vec &b) { return a.x * b.y - a.y * b.x; }
	inline double dis_PP(pt a, pt b) { return (a - b).len(); }
	inline double S(pt a, pt b, pt c) { return ((c - a) ^ (c - b)) / 2.0; }
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
    inline double diam(vector<pt> p) {
        int n = (int)(p.size());
        double ans = 0;
        // if (n == 2) return ans = dis_PP(p[0], p[1]);
        for (int i = 0, j = 1; i < n; ++i) {
            for (;; j = (j + 1) % n)
                if (dcmp(S(p[j], p[i], p[(i + 1) % n]) - S(p[(j + 1) % n], p[i], p[(i + 1) % n])) >= 0) break;
            ans = max(ans, max(dis_PP(p[i], p[j]), dis_PP(p[(i + 1) % n], p[j])));
        }
        return ans;
    }
}
using namespace CG;

int n;
vector<pt> p;

inline void solve() {
    read(n);
    for (int i = 1; i <= n; ++i) {
        double x, y;
        scanf("%lf%lf", &x, &y);
        p.emplace_back(pt(x, y));
    }
    double ans = diam(con(p));
    printf("%.0lf\n", ans * ans);
}

signed main() {
    // freopen("P1452_10.in","r",stdin);
    // freopen("my.out","w",stdout);
    // read(T);
    while (T--) solve();
    return 0;
}