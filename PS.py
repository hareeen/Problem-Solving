l = []
for i in range(int(input())):
    l.append(input())

ret = []
for j in range(len(l[0])):
    last = ''
    same = True
    for i in range(len(l)):
        if i == 0:
            last = l[i][j]
        else:
            same = (same and (last == l[i][j]))
    if same:
        ret.append(last)
    else:
        ret.append('?')

print(''.join(ret))
