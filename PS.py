_s = 0
a = 0
lst = ''
for i in input():
    if i == '(':
        a += 1
    else:
        a -= 1
        _s += 1
        if i != lst:
            _s += (a-1)
    lst = i
print(_s)
