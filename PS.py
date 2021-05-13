def ext_euc(a, b):
    if b == 0:
        return (a, 1, 0)

    g, x, y = ext_euc(b, a % b)
    return (g, y, x-(a//b)*y)


def powmod(b, e, m):
    b %= m
    ret: int = 1
    while e > 0:
        if e & 1:
            ret = (ret * b) % m
        b = (b * b) % m
        e >>= 1

    return ret


m = int(1e9 + 7)
for i in range(int(input())):
    r, g, b, k = map(int, input().split())
    print((r*(1-powmod(b*ext_euc(b+1, m)[1],k,m))+k*(b+g)*ext_euc(b, m)[1]) % m)
