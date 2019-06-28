l=[]
m=-999999
id=-1
for i in range(9):
    l.append(int(input()))
for el in enumerate(l):
    if m<el[1]:
        m=el[1]
        id=el[0]+1
print(m)
print(id)