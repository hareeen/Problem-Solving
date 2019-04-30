a = 0
b = 0
input()
for i in input():
  (a, b) = (min(a, b) + 1, b) if i == 'B' else (a, min(a, b) + 1)
print(a)
