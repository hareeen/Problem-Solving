exec('''n=int(input())+1;k=int(input());l=[[1]*(k+1)]
for _ in range(n):l+=[[0]*(k+1)]
for i in range(n):
    for j in range(k):l[i+1][j+1]=l[i][j+1]+l[i+1][j]
print(l[-1][-1]);'''*int(input()))