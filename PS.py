def vps(s):
  a=[0,0]
  for i in s:
    a[int(i=='(')]+=1
    if a[0]>a[1]: return False
  return a[0]==a[1]
for i in range(int(input())):
  print('YES' if vps(input()) else 'NO')
