n = int(input())
l = list(map(int, input().split()))
l.sort()
for i in range(n):
    l[i] *= (n-i)
print(sum(l))
