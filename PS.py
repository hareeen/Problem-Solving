import random
import base64


def pow_simple(n, e, MOD):  # O(e)
    _mul = 1
    for _ in range(e):
        _mul *= n
        _mul %= MOD
    return _mul


def pow_fast(n, e, MOD):  # O(log e)
    _mul = n
    _res = 1
    for digit in str(bin(e))[2:][::-1]:
        if digit == '1':
            _res *= _mul
            _res %= MOD
        _mul *= _mul
        _mul %= MOD
    return _res


def pow_negone(n):
    return 1 if n % 2 == 0 else -1


def gcd(a, b):  # 유클리드 호제법
    return a if b == 0 else gcd(b, a % b)


def jacobi(a, n):  # Jacobi Symbol (n이 홀수일 때만 정의됨)
    if a == 1:
        return 1
    elif a % 2 == 0:
        # J(a*b,n)=J(a,n)*J(b,n) && J(2,n)=(-1)**((n**2-1)/8)
        return jacobi(a // 2, n) * pow_negone((n * n - 1) // 8)
    else:
        return jacobi(n % a, a) * pow_negone((a - 1) * (n - 1) // 4)  # 이차상호법칙


def primality_test(p, loops=32):  # Solovay-Strassen Primality Test
    if p == 1:
        return False
    for _ in range(loops):
        r = random.randint(1, p - 1)
        if not (gcd(r, p) == 1 and jacobi(r, p) % p == pow_fast(r, (p - 1) // 2, p)):
            return False
    return True


N = int(input())
M = int(input())
res = list(filter(primality_test, range(N, M+1)))
if len(res):
    print(sum(res))
    print(min(res))
else:
    print(-1)
