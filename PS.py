N, M, X = map(int, input().split())
Hl = list(map(int, input().split()))
res = []
for i in range(N):
  res.append(['.'] * M)
for i in range(M):
  for j in range(N - Hl[i], N):
    res[j][i] = '#'
br_l = []
for i in range(M):
  if res[N - X][i] == '.':
    if i % 3 == 2:
      br_l.append(i)
    res[N - X][i] = '-'
  else:
    res[N - X][i] = '*'
for i in br_l:
  for j in range(N - X + 1, N):
    if res[j - 1][i] in ('-', '|') and res[j][i] != '#':
      res[j][i] = '|'
for i in range(N):
  res[i] = ''.join(res[i])
print('\n'.join(res))
