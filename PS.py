l = [1, 1]
g = list(map(int, list(input())))
for i in range(len(g)):
    l.append(((l[-1] if g[i] != 0 else 0) +
              (l[-2] if i > 0 and g[i-1] != 0 and g[i-1]*10+g[i] <= 26 else 0)) % 1000000)
print(l[-1])
