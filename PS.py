N=int(input())
l=list(map(int, input().split()))
dp=[]
for _ in range(N):
  dp.append([-10**10]*(N+1))
for i in range(N):
  for j in range(N+1):
    if i==0:
      dp[i][j]=l[i]*j
    else:
      M=-10**10
      k=0
      while j-k*(i+1)>=0:
        M=max(M, dp[i-1][j-k*(i+1)]+l[i]*k)
        k+=1
      dp[i][j]=M
print(max(dp[-1]))
