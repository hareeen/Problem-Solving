from math import ceil
d = [0]*10
for i in map(int, input()):
    if i in (6, 9):
        d[6] += 0.5
        d[9] += 0.5
    else:
        d[i] += 1
print(max(map(ceil, d)))
