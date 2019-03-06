sec=0
cnt=0
pos=[0,0]
n=int(input())
di=[[0,1],[1,0],[0,-1],[-1,0]]

while True:
  for _ in range(cnt//2+1):
    if n==sec:
      print(pos[0], pos[1])
      exit()
    pos[0]+=di[cnt%4][0]
    pos[1]+=di[cnt%4][1]
    sec+=1
  cnt+=1
