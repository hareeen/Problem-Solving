N = int(input())
l = []
dp = []
for i in range(N):
  l.append(list(map(int, input().split())))
  dp.append([0] * (i + 1))
dp[0][0] = l[0][0]
for i in range(1, N):
  dp[i][0] = dp[i - 1][0] + l[i][0]
  dp[i][i] = dp[i - 1][i - 1] + l[i][i]
  for j in range(1, i):
    dp[i][j] = max(dp[i - 1][j], dp[i - 1][j - 1]) + l[i][j]
print(max(dp[-1]))
