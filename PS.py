N=int(input())
l=[]
for i in range(N):
    s=input().split()
    l.append((int(s[0]), i, s[1]))
l.sort()
for i in l:
    print(i[0], i[2])