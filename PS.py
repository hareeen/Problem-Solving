import queue

def tup_plus(a: tuple, b: tuple):
    c = list()
    for i in range(len(a)):
        c.append(a[i]+b[i])
    return tuple(c)


def main():
    N, M = map(int, input().split())
    mp = []
    for _ in range(N):
        mp.append(list(map(bool, list(input()))))
    que = queue.Queue()
    que.put(((0, 0), 1))
    while que.qsize():
        curtup = que.get()
        if curtup[0] == (N-1, M-1):
            print(curtup[1])
            break

        def check(tup, plus):
            ret = tup_plus(tup, plus)
            return (ret[0] >= 0 and ret[0] < N and ret[1] >= 0 and ret[1] < M and mp[ret[0]][ret[1]] == 1)
        for i in range(4):
            pl = [(0, -1), (0, 1), (1, 0), (-1, 0)][i]
            if check(curtup[0], pl):
                que.put((tup_plus(curtup[0], pl), curtup[1]+1))
        mp[curtup[0][0]][curtup[0][1]] = 0
    return


main()
