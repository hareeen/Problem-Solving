for i in range(int(input())):
  s=[1,2,4]
  t=int(input())
  l=lambda x:x if x>0 else 0
  exec("s.append((s[-1]+s[-2]+s[-3]));"*l(t-3))
  print(s[t-1])
