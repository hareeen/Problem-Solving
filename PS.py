box1 = list(map(int, input().split()))
box2 = list(map(int, input().split()))
b1 = ((box1[0], box1[2]), (box1[1], box1[3]))
b2 = ((box2[0], box2[2]), (box2[1], box2[3]))


def mtch(l1, l2):
    if l1[0] > l2[0]:
        l1, l2 = l2, l1
    if l2[0] > l1[1]:
        return 0
    elif l2[0] == l1[1]:
        return 1
    else:
        return 2


print([['NULL', 'NULL', 'NULL'],
       ['NULL', 'POINT', 'LINE'],
       ['NULL', 'LINE', 'FACE']][mtch(b1[0], b2[0])][mtch(b1[1], b2[1])])
