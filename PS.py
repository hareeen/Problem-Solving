from math import sqrt as s
n=int(input())
t=int(s(n*2+s(n*2-2)-1))
v=t*(t+1)//2-n
print("%d/%d"%((v+1,t-v) if t%2==1 else (t-v,v+1)))