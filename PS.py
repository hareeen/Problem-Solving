N=int(input())
s=input()
p=1
res=0
for i in range(N):
    res+=(p*(ord(s[i])-ord('a')+1))
    res%=1234567891
    p*=31
    p%=1234567891

print(res)