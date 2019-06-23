l=[1,1,1,2,2];exec("l+=[l[-1]+l[-5]];"*95)
for _ in range(int(input())):print(l[int(input())-1]) 