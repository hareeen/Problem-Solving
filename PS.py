from math import ceil
arr = [[0, 0, 0], [0, 0, 0]]
N, K = map(int, input().split())
for i in range(N):
    s, y = map(int, input().split())
    arr[s][(y-1)//2] += 1
s = ceil((arr[0][0]+arr[1][0])/K)
for i in range(2):
    for j in range(1, 3):
        s += ceil(arr[i][j]/K)
print(s)
