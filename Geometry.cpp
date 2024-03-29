#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef vector<pii> vpii;
typedef vector<vi> vvi;
typedef complex<double> cd;
typedef vector<cd> vcd;
#define endl '\n'
#define rp(x, i, j) for (int x = (i); x < (j); ++x)
#define rpr(x, i, j) for (int x = (i)-1; x >= j; --x)
#define rpe(e, arr) for (auto& e : arr)
#define all(x) begin(x), end(x)
int INF = 1e9;
ll LINF = 1e18;
int dy[]{0, -1, 0, 1};
int dx[]{-1, 0, 1, 0};

struct v2 {
    /*
    2차원 벡터정보를 저장하는 구조체
    */
    ll y, x;
    auto operator<(const v2& o) const {
        return y < o.y || y == o.y && x < o.x;
    }
    v2 operator-(const v2& o) const {
        return {y - o.y, x - o.x};
    }
};

istream& operator>>(istream& is, v2& o) {
    is >> o.x >> o.y;
    return is;
}

ll ccw(const v2& a, const v2& b) {
    /*
    두 벡터 a와 b의 ccw를 계산하여 반환
    */
    return a.x * b.y - b.x * a.y;
}

ll ccw(const v2& a, const v2& b, const v2& c) {
    /*
    두 벡터 b - a와 c - a의 ccw를 계산하여 반환
    a, b, c가 위치벡터라고 생각하자
    */
    return ccw(b - a, c - a);
}

vector<v2> get_hull(vector<v2> pt) {
    /*
    주어진 점들 중 볼록껍질에 속하는 점들을 반환
    모노톤 체인 알고리즘을 사용 (O(logN), N=pt.size())
    
    Property:
        -pt(vector<v2>): points, 볼록껍질을 구할 여러 점들의 정보가 담긴 벡터, 순서는 상관없다.
    
    Return:
        -vector<v2>: 볼록껍질에 속하는 점 중 y가 가장 작은 점에서 시작하여 반시계방향순으로 저장된 배열
    
    */
    if (pt.size() <= 3) return pt;
    sort(begin(pt), end(pt));
    vector<v2> l, r;
    for (auto& e : pt) {
        for (int i = l.size() - 1; i >= 1 && ccw(l[i - 1], l[i], e) >= 0; --i)
            l.pop_back();
        l.push_back(e);
        for (int i = r.size() - 1; i >= 1 && ccw(r[i - 1], r[i], e) <= 0; --i)
            r.pop_back();
        r.push_back(e);
    }
    r.insert(end(r), rbegin(l) + 1, rend(l) - 1);
    return r;
}

pair<v2, v2> get_farthest_pair(const vector<v2>& pt) {
    /*
    볼록껍질이 주어졌을 때 가장 먼 두 점을 반환
    회전하는 캘리퍼스 알고리즘을 사용 (O(N), N=pt.size())
    
    Property:
        -pt(vector<v2>): points, 볼록껍질에 속하는 점의 정보가 담긴 벡터, 순서는 반드시 반시계방향순이어야 한다.
    */
    double dist = 0;
    v2 ans1, ans2;
    for (int i = 0, a = 0, b = 1; i < ssize(pt) * 2; ++i) {
        int na = (a + 1) % ssize(pt);
        int nb = (b + 1) % ssize(pt);
        if (double ndist = (pt[a] - pt[b]).norm(); ndist > dist) {
            dist = ndist;
            ans1 = pt[a];
            ans2 = pt[b];
        }
        int cross = ccw(pt[na] - pt[a], pt[nb] - pt[b]);
        if (cross > 0) b = nb;
        else a = na;
    }
    return {ans1, ans2};
}
