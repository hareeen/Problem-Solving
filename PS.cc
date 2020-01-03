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

vector<cpx> nrU; // nth root of unity

void FFT(vector<cpx> &v, i64 idx) {
    const i64 N = v.size();
    if (N == 1) return;

    vector<cpx> odd, even;
    for (int i = 0; i < N; i++) {
        if (i % 2) odd.push_back(v[i]);
        else even.push_back(v[i]);
    }

    FFT(even, (idx * 2) % nrU.size());
    FFT(odd, (idx * 2) % nrU.size());

    i64 pos = 0;
    for (int i = 0; i < N / 2; i++) {
        v[i] = even[i] + nrU[pos] * odd[i];
        v[i + N / 2] = even[i] - nrU[pos] * odd[i];
        pos += idx;
        pos %= nrU.size();
    }
}


vector<cpx> convolution(vector<cpx> a, vector<cpx> b) {
    i64 N = 1;
    while (N <= a.size() || N <= b.size()) N *= 2;
    N *= 2;

    const d64 PI = acos(static_cast<long double>(-1));
    for (i64 i = 0; i < N; i++) {
        const d64 theta = static_cast<d64>(2 * i) * PI / static_cast<d64>(N);
        nrU.emplace_back(cpx(cos(theta), sin(theta)));
    }

    a.resize(N), b.resize(N);
    FFT(a, 1), FFT(b, 1);

    vector<cpx> c(N);
    generate(iterall(c), [&, i = -1]() mutable -> cpx {
        i++;
        return a[i] * b[i];
    });

    FFT(c, N - 1);
    for (auto &el:c) el /= cpx(static_cast<d64>(N));

    return c;
}

using ui64 = unsigned long long;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int N, M;
    cin >> N >> M;
    N++, M++;

    vector<i64> a(N), b(M);
    for (int i = 0; i < N; i++) cin >> a[i];
    for (int i = 0; i < M; i++) cin >> b[i];

    vector<cpx> ac, bc;
    transform(iterall(a), back_inserter(ac), [](i64 x) -> cpx { return cpx(x); });
    transform(iterall(b), back_inserter(bc), [](i64 x) -> cpx { return cpx(x); });

    auto c = convolution(ac, bc);

    vector<ui64> ret;
    transform(iterall(c), back_inserter(ret), [](cpx x) -> ui64 {
        return static_cast<ui64>(x.real() + (x.real() > 0 ?
                                             static_cast<d64>(0.5) : static_cast<d64>(-0.5)));
    });

    cout << accumulate(iterall(ret), static_cast<ui64>(0), [](ui64 su, ui64 x) -> ui64 { return su ^ x; }) << endl;

    return 0;
}