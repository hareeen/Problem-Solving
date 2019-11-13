from math import gcd
from fractions import Fraction

N = int(input())

l = []
l.append(Fraction(1, 1))
for i in range(N-1):
    l.append(Fraction(0, 1))

grp = []
for i in range(N):
    grp.append([])

for i in range(N-1):
    a, b, p, q = map(int, input().split())
    grp[a].append((b, Fraction(q, p)))
    grp[b].append((a, Fraction(p, q)))


def dfs(u: int):
    global l, grp
    for v, w in grp[u]:
        if l[v] == 0:
            l[v] = l[u]*w
            dfs(v)


dfs(0)


def lcm(a: int, b: int):
    return a//gcd(a, b)*b


lc = 1
for rat in l:
    lc = lcm(rat.denominator, lc)

for i in range(N):
    l[i] *= lc

print(' '.join(map(lambda x: str(x.numerator), l)))
