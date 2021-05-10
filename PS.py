A = int(input())
X = int(input())

adex = [A]

mod = int(1e9 + 7)
for i in range(70):
    adex.append(adex[-1]**2)
    adex[-1]%=mod

ans = 1
l = [*map(int, bin(X)[2:][::-1])]
for i in range(len(l)):
    if l[i] == 1:
        print(l)
        ans *= adex[i]
    ans %= mod

print(ans)