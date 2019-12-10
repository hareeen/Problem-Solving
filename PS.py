from math import sqrt
from decimal import *

getcontext().prec = 50

a, b, c = map(lambda x: Decimal(float(x)), input().split())
s = (a+b+c)/2
S = (s*(s-a)*(s-b)*(s-c)).sqrt()
R = a*b*c/4/S
r = 2*S/(a+b+c)
d = max(Decimal(0), (R*(R-2*r))).sqrt()
k = (R*R-a*a/4).sqrt()+(R*R-b*b/4).sqrt()+(R*R-c*c/4).sqrt()
print(S)
print(R)
print(r)
print(d)
print(k)
