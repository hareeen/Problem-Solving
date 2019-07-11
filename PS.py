from math import sqrt


def gcd(a, b):
    return a if b == 0 else gcd(b, a % b)


g, l = map(int, input().split())
c = int(sqrt(l//g))
while True:
    if (l//g) % c == 0 and gcd(c, l//c//g) == 1:
        print(c*g, l//c)
        break
    c -= 1
