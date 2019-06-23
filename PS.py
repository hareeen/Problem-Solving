l=[1]*10
for i in range(int(input())):l=list(map(lambda x:sum(l[:(x+1)]),range(10)))
print(l[-1]%10007)