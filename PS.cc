#include <bits/stdc++.h>

using namespace std;

using i64 = long long;
using d64 = long double;
using pi = pair<int, int>;
using pli = pair<i64, i64>;
using ti = tuple<int, int, int>;
using tli = tuple<i64, i64, i64>;

#define iterall(cont) cont.begin(), cont.end()
#define prec(n) setprecision(n) << fixed

using cpx = complex<d64>;

const size_t SIMPLE_LIMIT = 8;

void FFT(vector<cpx> &v, cpx w) {
    const auto N = v.size();

    if (N <= SIMPLE_LIMIT) {
        vector<cpx> ret(N);
        cpx cur(1);
        for (int i = 0; i < N; i++) {
            cpx su(0), mul(1);
            for (int j = 0; j < N; j++) {
                su += (mul * v[j]);
                mul *= cur;
            }
            ret[i] = su;
            cur *= w;
        }
        v = ret;
        return;
    }

    vector<cpx> even(N / 2), odd(N / 2);
    for (int i = 0; i < N; i++) {
        if (i % 2) odd[i / 2] = v[i];
        else even[i / 2] = v[i];
    }

    FFT(even, w * w);
    FFT(odd, w * w);

    cpx mul(1);
    for (int i = 0; i < N / 2; i++) {
        v[i] = even[i] + mul * odd[i];
        v[i + N / 2] = even[i] - mul * odd[i];
        mul *= w;
    }
}

const d64 PI = acos(-1);

vector<cpx> convolution(vector<cpx> lhs, vector<cpx> rhs) {
    i64 N = 1;
    while (N <= lhs.size() || N <= rhs.size()) N *= 2;
    N *= 2;

    lhs.resize(N), rhs.resize(N);

    cpx w(cos(2 * PI / N), sin(2 * PI / N));
    FFT(lhs, w), FFT(rhs, w);

    vector<cpx> ret(N);
    generate(iterall(ret), [&, i = -1]() mutable {
        i++;
        return lhs[i] * rhs[i];
    });

    FFT(ret, cpx(1) / w);
    for (auto &el:ret) el /= cpx(N);

    return ret;
}

const int digit = 4;

void cpx_slice(string &s, vector<cpx> &v) {
    for (int i = 0; i < s.size(); i += digit) {
        i64 su = 0, mul = 1;
        for (int j = i; j < min(static_cast<int>(s.size()), i + digit); j++) {
            su += (static_cast<i64>(s[j] - '0') * mul);
            mul *= 10;
        }
        v.emplace_back(cpx(su));
    }
}

string tidify(i64 x) {
    vector<i64> v;
    while (x) v.push_back(x % 10), x /= 10;
    while (v.size() < digit) v.push_back(0);

    string s;
    for (auto el:v) s.push_back('0' + el);

    return s;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    string s1, s2;
    cin >> s1 >> s2;

    reverse(iterall(s1));
    reverse(iterall(s2));

    bool minus = false;
    if (s1.back() == '-') minus = !minus, s1.pop_back();
    if (s2.back() == '-') minus = !minus, s2.pop_back();

    vector<cpx> cpx1, cpx2;
    cpx_slice(s1, cpx1);
    cpx_slice(s2, cpx2);

    auto ret = convolution(cpx1, cpx2);
    vector<i64> res(ret.size());
    for (int i = 0; i < ret.size(); i++) res[i] = static_cast<i64>(round(ret[i].real()));

    i64 mod = 1;
    for (int i = 0; i < digit; i++) mod *= 10;
    for (int i = 0; i < res.size() - 1; i++) {
        res[i + 1] += (res[i] / mod), res[i] %= mod;
        if (res[i] < 0) res[i + 1] -= 1, res[i] += mod;
    }

    string prt;
    for (auto el:res) prt += tidify(el);
    while (prt.back() == '0' && prt.size() > 1) prt.pop_back();
    reverse(iterall(prt));

    if (minus && prt.front() != '0') cout << '-';
    cout << prt << endl;
    return 0;
}