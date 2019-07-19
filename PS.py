ans=1
rt=0
for _ in range(int(input())):
    a,b,s=map(int, input().split())
    ans*=b
    ans//=a
    rt^=s
print(rt, ans)