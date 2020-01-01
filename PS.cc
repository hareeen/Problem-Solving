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

void FFT(vector<cpx> &v, cpx z) {
    const auto N = v.size();
    if (N == 1) return;

    vector<cpx> even, odd;
    for (int i = 0; i < N; i++) {
        if (i % 2) odd.push_back(v[i]);
        else even.push_back(v[i]);
    }

    FFT(even, z * z), FFT(odd, z * z);

    cpx mul(1);
    for (int i = 0; i < N / 2; i++) {
        v[i] = even[i] + mul * odd[i];
        v[i + N / 2] = even[i] - mul * odd[i];
        mul *= z;
    }
}

const d64 PI = acos(-1);

vector<cpx> convolution(vector<cpx> a, vector<cpx> b) {
    int N = 1;
    while (N < a.size() || N < b.size()) N *= 2;
    N *= 2;

    const auto originalSize = b.size();
    a.resize(N), b.resize(N);
    for (int i = 0; i < originalSize; i++) b[N - originalSize + i] = b[i];

    cpx z(cos(2 * PI / N), sin(2 * PI / N));
    FFT(a, z), FFT(b, z);

    vector<cpx> c(N);
    generate(iterall(c), [&, i = -1]() mutable {
        i++;
        return a[i] * b[i];
    });

    FFT(c, cpx(1) / z);
    for (auto &el:c) el /= cpx(N);

    return c;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int N;
    cin >> N;

    vector<i64> a(N), b(N);
    for (int i = 0; i < N; i++) cin >> a[i];
    for (int i = 0; i < N; i++) cin >> b[i];
    reverse(iterall(b));

    vector<cpx> ac, bc;
    transform(iterall(a), back_inserter(ac), [](i64 x) -> cpx { return cpx(x); });
    transform(iterall(b), back_inserter(bc), [](i64 x) -> cpx { return cpx(x); });

    auto cc = convolution(ac, bc);
    vector<i64> c;
    for (int i = 0; i < N; i++) c.push_back(round(cc[i].real()));

    cout << *max_element(iterall(c)) << endl;
    return 0;
}