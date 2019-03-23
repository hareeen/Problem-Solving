l=list(map(int, input().split()))
s=sorted(l)
if s==l:
  print("ascending")
elif s[::-1]==l:
  print("descending")
else:
  print("mixed")
