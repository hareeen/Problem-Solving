import itertools

N, M = map(int, input().split())
l = list(map(int, input().split()))
res = list(set(itertools.combinations_with_replacement(sorted(l), M)))
for i in sorted(res):
    print(' '.join(map(str, i)))
