def fact(n: int):
    mul = 1
    for i in range(n):
        mul *= (i+1)
    return mul


def nCr(n: int, r: int):
    return fact(n)//fact(r)//fact(n-r)


ans = 0
n, k = map(int, input().split())
for i in range(k+1):
    ans += ((-1)**(i))*nCr(k, i)*((10-i)**n)
print(ans)
