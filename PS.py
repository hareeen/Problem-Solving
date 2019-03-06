from math import sqrt
s=lambda x: int(sqrt(x))
x=(int(input())-2)//6*2
print(1 if x<0 else s(x-s(x))+2)
