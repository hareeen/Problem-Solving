def main():
    l = []
    for i in range(9):
        l.append(int(input()))
    l.sort()
    bf = []
    for i in range(9):
        for j in range(9):
            if i != j:
                bf.append((i, j, l[i]+l[j]))
    for i in bf:
        if sum(l)-i[2] == 100:
            for j in range(9):
                if not j in i[:2]:
                    print(l[j])
            return
    return


main()
