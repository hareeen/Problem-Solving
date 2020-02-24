

def solve1D(l: list):
    N = len(l)
    p = 0
    ret = []
    
    while p<N-3:
        if l[p+1] != l[p+2]:
            ret.append([p+1, p+2])
            l[p+1] = l[p+2] = (l[p+1]+l[p+2])%3
        

