e, s, m = map(int, input().split())
e %= 15
s %= 28
m %= 19
res = 0
while(True):
    res += 1
    if res % 15 == e and res % 28 == s and res % 19 == m:
        print(res)
        break
