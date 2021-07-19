M = int(1e9 + 7)
mod = M**16


def ext_euc(a, b):
    if b == 0:
        return (a, 1, 0)
    g, x, y = ext_euc(b, a % b)
    return (g, y, x-(a//b)*y)


def matmul(l, r):
    return [[(l[0][0]*r[0][0]+l[0][1]*r[1][0]) % mod, (l[0][0]*r[0][1]+l[0][1]*r[1][1]) % mod],
            [(l[1][0]*r[0][0]+l[1][1]*r[1][0]) % mod, (l[1][0]*r[0][1]+l[1][1]*r[1][1]) % mod]]


def fibo(n):
    if n == -1:
        return 1

    base = [[1, 1], [1, 0]]
    target = [[1, 0], [0, 1]]
    while n:
        if n % 2:
            target = matmul(target, base)
        base = matmul(base, base)
        n //= 2

    return target[0][1]


N, K = map(int, input().split())

Fnk = fibo(N*K)
Fk = fibo(K)
Fnkm1 = fibo(N*K-1)
Fkm1 = fibo(K-1)

while Fk % M == 0 and Fnk % M == 0:
    Fk //= M
    Fnk //= M

A = (Fnk * ext_euc(Fk, mod)[1]) % M
B = (Fnkm1 - A * Fkm1) % M
print(A, B)
