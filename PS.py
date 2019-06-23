def pow_fast(n, e, MOD=10):  # O(log e)
    _mul = n
    _res = 1
    for digit in str(bin(e))[2:][::-1]:
        if digit == '1':
            _res *= _mul
            _res %= MOD
        _mul *= _mul
        _mul %= MOD
    return _res


for _ in range(int(input())):
    n, e = map(int, input().split())
    print((pow_fast(n, e)-1) % 10+1)
