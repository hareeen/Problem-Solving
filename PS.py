from itertools import combinations
while True:
    l = list(map(int, input().split()))[1:]
    if len(l) == 0:
        break
    for combi in combinations(l, 6):
        print(*combi)
    print()
