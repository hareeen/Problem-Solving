mp = []
for i in range(100):
    mp.append([0]*100)
for i in range(4):
    x1, y1, x2, y2 = map(int, input().split())
    for x in range(x1, x2):
        for y in range(y1, y2):
            mp[x][y] = 1
ans = 0
for i in mp:
    ans += sum(i)
print(ans)
