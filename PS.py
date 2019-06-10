def main():
    s = 0
    l = ['ABC', 'DEF', 'GHI', 'JKL', 'MNO', 'PQRS', 'TUV', 'WXYZ']
    for i in input():
        for j in range(len(l)):
            if i in l[j]:
                s += (j+3)
                break
    print(s)


main()
