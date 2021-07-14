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

const double PI = acos(0) * 2;

void fft(vcd& p) {
    /*
    고속 푸리에 변환을 한다.
    
    Property:
        p(vector<complex<double>>): 방정식의 계수를 담고 있는 배열. 크기는 반드시 2의 거듭제곱수이어야 한다.
        
    How to Use:
        fft(p);
        fft(q);
        rp(i, 0, p.size()) p[i] *= q[i];
        ifft(p);
        
        다음 링크의 3.길쌈(convolution)의 대수적 성질과 길쌈정리 참고
        https://ghebook.blogspot.com/2020/10/properties-of-fourier-transform.html
    */
    int n = p.size();
    for (int i = 1, j = 0; i < n; ++i) {
        int bit = n >> 1;
        while (!((j ^= bit) & bit)) bit >>= 1;
        if (i < j) swap(p[i], p[j]);
    }

    for (int len = 1; len < n; len <<= 1) {
        double u = -PI / len;
        cd w(cos(u), sin(u));
        for (int pos = 0; pos < n; pos += len << 1) {
            cd a(1, 0);
            rp(i, 0, len) {
                cd x = p[pos + i], y = p[len + pos + i] * a;
                p[pos + i] = x + y;
                p[len + pos + i] = x - y;
                a *= w;
            }
        }
    }
}

void ifft(vcd& p) {
    /*
    역 푸리에 변환을 한다.
    
    Property:
        p(vector<complex<double>>): 푸리에 변환된 배열. 크기는 반드시 푸리에 변환을 했을 때와 같아야 한다.
    */
    fft(p);
    double n = p.size();
    rpe(e, p) e /= n;
    reverse(1 + all(p));
}
