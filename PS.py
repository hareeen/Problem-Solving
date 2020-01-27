k, n = map(int, input().split())
q = [[1, k, k*(k+1)]]
qa = [True]
s = {1, k, k*(k+1)}
p = 0
t = 0
lim = 10**100


def qapp(tup):
    global q, t
    tup.sort()
    if tup[-1] >= lim or tup[0] <= -lim:
        return
    if tup in q:
        return

    q.append(tup)
    qa.append(False)

    if tup[0] > 0 and not (tup[0] in s or tup[1] in s or tup[2] in s):
        t += 1
        qa[-1] = True
        s.add(tup[0])
        s.add(tup[1])
        s.add(tup[2])


while t < n:
    cur = q[p]
    qapp([k*(cur[1]+cur[2])-cur[0], cur[1], cur[2]])
    qapp([cur[0], k*(cur[0]+cur[2])-cur[1], cur[2]])
    qapp([cur[0], cur[1], k*(cur[0]+cur[1])-cur[2]])
    p += 1

m = 0
for i in range(len(q)):
    if m == n:
        break
    if qa[i]:
        m += 1
        print(*q[i])
