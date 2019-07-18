from math import ceil, log2


class segmentTree:
    def __init__(self, N):
        self.treeSize = 2**(ceil(log2(N))+2)
        self.value = [0]*self.treeSize
        self.lazy = [0]*self.treeSize

    def init(self, s, e, node, arr: list):
        if s == e:
            self.value[node] = arr[s]
        else:
            self.value[node] = self.init(s, (s+e)//2, node*2, arr) + \
                self.init((s+e)//2+1, e, node*2+1, arr)
        return self.value[node]

    def update(self, l, r, s, e, node, diff):
        if self.lazy[node] != 0:
            self.value[node] += self.lazy[node]*(e-s+1)
            if s != e:
                self.lazy[node*2] += self.lazy[node]
                self.lazy[node*2+1] += self.lazy[node]
            self.lazy[node] = 0

        if e < l or r < s:
            return

        if l <= s and e <= r:
            self.value[node] += diff*(e-s+1)
            if s != e:
                self.lazy[node*2] += diff
                self.lazy[node*2+1] += diff
            return

        self.update(l, r, s, (s+e)//2, node*2, diff)
        self.update(l, r, (s+e)//2+1, e, node*2+1, diff)

        self.value[node] = self.value[node*2]+self.value[node*2+1]
        return

    def query(self, l, r, s, e, node):
        if self.lazy[node] != 0:
            self.value[node] += self.lazy[node]*(e-s+1)
            if s != e:
                self.lazy[node*2] += self.lazy[node]
                self.lazy[node*2+1] += self.lazy[node]
            self.lazy[node] = 0

        if e < l or r < s:
            return 0
        elif l <= s and e <= r:
            return self.value[node]
        else:
            return self.query(l, r, s, (s+e)//2, node*2)+self.query(l, r, (s+e)//2+1, e, node*2+1)


N, M, K = map(int, input().split())

arr = [0]
for i in range(N):
    arr.append(int(input()))

sg = segmentTree(N)
sg.init(1, N, 1, arr)
for i in range(M+K):
    inp = list(map(int, input().split()))
    if inp[0] == 1:
        sg.update(inp[1], inp[2], 1, N, 1, inp[3])
    else:
        print(sg.query(inp[1], inp[2], 1, N, 1))
