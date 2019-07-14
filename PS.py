tet = [[[1, 1, 1, 1]], [[1], [1], [1], [1]],
       [[1, 1, 1], [0, 1, 0]], [[0, 1, 0], [1, 1, 1]],
       [[0, 1], [1, 1], [0, 1]], [[1, 0], [1, 1], [1, 0]],
       [[1, 1, 0], [0, 1, 1]], [[0, 1, 1], [1, 1, 0]],
       [[0, 1], [1, 1], [1, 0]], [[1, 0], [1, 1], [0, 1]],
       [[1, 1], [1, 1]],
       [[1, 0, 0], [1, 1, 1]], [[0, 0, 1], [1, 1, 1]],
       [[1, 1, 1], [0, 0, 1]], [[1, 1, 1], [1, 0, 0]],
       [[1, 0], [1, 0], [1, 1]], [[0, 1], [0, 1], [1, 1]],
       [[1, 1], [1, 0], [1, 0]], [[1, 1], [0, 1], [0, 1]]]

N, M = map(int, input().split())
mp = []
for i in range(N):
    mp.append(list(map(int, input().split())))

ans = 0
for fragment in tet:
    for i in range(M-len(fragment[0])+1):
        for j in range(N-len(fragment)+1):
            _s = 0
            for k in range(len(fragment[0])):
                for l in range(len(fragment)):
                    _s += mp[l+j][k+i]*fragment[l][k]
            ans = max(ans, _s)

print(ans)
