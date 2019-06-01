a,b,c=map(int, input().split())
if a>b: a,b=b,a
b=min(a+1, b)
print(a+b+2*c)
