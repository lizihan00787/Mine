#include <bits/stdc++.h>
#define endl '\n'
#define int long long
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

const int N = 1e4 + 10, M = 1e5 + 5e4 + 10;

const int cp[2][22] = {{0, 400, 417, 417, 434, 434, 451, 451, 470, 470, 485, 485, 500, 500, 515, 515, 530, 530, 540, 540, 0x3f3f3f3f3f3f3f3f},
                    {0, 750, 780, 780, 810, 810, 840, 840, 870, 870, 910, 910, 950, 950, 990, 990, 1030, 1030, 1080, 1080, 0x3f3f3f3f3f3f3f3f}};
const int cj[22] = {20, 20, 18, 18, 16, 16, 14, 14, 12, 12, 10, 10, 8, 8, 6, 6, 4, 4, 2, 2, 0};
const int ygcs[12] = {0, 3, 3, 7, 7, 11, 11, 14, 17, 19, 21, 0x3f3f3f3f3f3f3f3f};
const int cqcs[12] = {0, 6, 9, 12, 15, 18, 0x3f3f3f3f3f3f3f3f};
const int yue[13] = {0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334, 365};
const int fina[15] = {0, 60, 63, 67, 70, 73, 77, 80, 85, 90, 95, 0x3f3f3f3f3f3f3f3f};
const string fi[15] = {"F", "D", "D+", "C-", "C", "C+", "B-", "B", "B+", "A-", "A"};

int n, m;

int timez(char *s) {
    int minute, second;
    sscanf(s, "%lld'%lld\"", &minute, &second);
    return minute * 60 + second;
}
int timep(char *s) {
    int hour, minute, second;
    sscanf(s, "%lld:%lld:%lld", &hour, &minute, &second);
    return hour * 3600 + minute * 60 + second;
}
int timcz(int month1, int date1, int month2, int date2, char *s1, char *s2) {
    int czm = timep(s2) - timep(s1);
    int czd = yue[month2 - 1] - yue[month1 - 1] + (date2 - date1);
    return czd * 3600 * 24 + czm;
}
int time(int month, int date, int tim) {
    int czd = yue[month - 1] + date;
    return czd * 3600 * 24 + tim;
}

struct record {
    int year, month, date;
    int sttim, edtim;
    double dis;
    int pastim;
    int step;
    bool operator < (const record &b) const {
        return time(month, date, sttim) < time(b.month, b.date, b.sttim);
    }
};

struct stu {
    string number;
    int ismale, res_ketang, res_cp, res_phy, res_zhuan, cntpart, cntsun, finals;
    vector<record> data;
    bool operator < (const stu &b) const {
        return number < b.number;
    }
} a[N];
map<string, int> q;

inline void solve() {
    read(n);
    for (int i = 1; i <= n; ++i) {
        char re_cp[10];
        char sex, ist;
        cin >> a[i].number >> sex >> a[i].res_ketang >> re_cp >> ist >> a[i].res_zhuan >> a[i].cntpart;
        q[a[i].number] = i;
        a[i].ismale = (sex == 'M');
        a[i].res_phy = (ist == 'P') * 10;
        a[i].res_cp = timez(re_cp);
    }
    getchar();
    read(m);
    for (int i = 1; i <= m; ++i) {
        int id;
        record tmp;
        string num;
        char st[12], ed[12], pas[12];
        scanf("%4lld%2lld%2lld", &tmp.year, &tmp.month, &tmp.date);
        cin >> num;
        id = q[num];
        cin >> st >> ed >> tmp.dis >> pas >> tmp.step;
        tmp.sttim = timep(st); tmp.edtim = timep(ed);
        tmp.pastim = timez(pas);
        if ((tmp.dis < 3.000 && a[id].ismale) || (tmp.dis < 1.500 && !a[id].ismale)) continue;
        if (1.0 * tmp.dis * 1000 / (tmp.edtim - tmp.sttim) < 2.0 || 1.0 * tmp.dis * 1000 / (tmp.edtim - tmp.sttim) > 5.0) continue;
        if (tmp.pastim > 270) continue;
        if (1.0 * tmp.dis * 1000 / tmp.step > 1.5) continue;
        a[id].data.emplace_back(tmp);
    }
    sort(a + 1, a + n + 1);
    for (int i = 1; i <= n; ++i) {
        stu &t = a[i];
        sort(t.data.begin(), t.data.end());
        int tot = 1, las = 0, jg = 1;
        for (int j = 1; j < (int)(t.data.size()); ++j) {
            if (time(t.data[j].month, t.data[j].date, t.data[j].sttim) - time(t.data[las].month, t.data[las].date, t.data[las].edtim) < 6 * 3600) { jg++; continue; }
            tot++; las += jg; jg = 1;
        }
        t.res_cp = cj[lower_bound(cp[t.ismale], cp[t.ismale] + 20, t.res_cp) - cp[t.ismale]];
        t.res_zhuan += upper_bound(cqcs, cqcs + 7, t.cntpart + tot) - cqcs - 1;
        int pre = upper_bound(ygcs, ygcs + 11, tot) - ygcs - 1;
        t.finals = t.res_cp + t.res_ketang + t.res_phy + t.res_zhuan + pre;
    }
    for (int i = 1; i <= n; ++i) {
        string grade = fi[upper_bound(fina, fina + 12, a[i].finals) - fina - 1];
        cout << a[i].number << ' ' << a[i].finals << ' ' << grade << endl;
    }
}

signed main() {
    // freopen(".in","r",stdin);
    // freopen(".out","w",stdout);
    // read(T);
    while (T--) solve();
    return 0;
}