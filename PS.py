def calc(l: list):
    _s = 0
    for i in l:
        if i == 4:
            _s += 4000000
        elif i == 3:
            _s += 30000
        elif i == 2:
            _s += 200
        else:
            _s += 1
    return _s


for i in range(int(input())):
    a = calc(list(map(int, input().split()))[1:])
    b = calc(list(map(int, input().split()))[1:])

    if a > b:
        print('A')
    elif a == b:
        print('D')
    else:
        print('B')
