import functools
n=int(input())
print(1 if n==0 else functools.reduce(int.__mul__,range(1,n+1)))