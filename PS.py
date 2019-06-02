N = int(input())
dp = [[0] + [1] * 9]
for i in range(1, N):
  apd = [0] * 10
  for j in range(10):
    if j in (0, 9):
      apd[j] = dp[-1][7 * (j // 9) + 1]
    else:
      apd[j] = dp[-1][j - 1] + dp[-1][j + 1]
  dp.append(apd)
print(sum(dp[-1]) % 1000000000)
