import itertools


def toNumber(l: tuple):
    _s = ''
    for i in l:
        _s = _s+i
    return int(_s)


a, b = input().split()
ans = 0
for i in range(1, max(len(a), len(b))+1):
    for num_tup in itertools.product(['4', '7'], repeat=i):
        if int(a) <= toNumber(num_tup) and toNumber(num_tup) <= int(b):
            ans += 1
print(ans)
