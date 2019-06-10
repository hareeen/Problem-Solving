l = 'qwertyuiopasdfghjklzxcvbnm'
s = 0
for i in range(int(input())):
    wd = input()
    flg = True
    for c in l:
        if c in wd:
            lst = -1
            for j in range(len(wd)):
                if wd[j] == c:
                    if lst != -1 and lst != j-1:
                        flg = False
                    else:
                        lst = j
    if flg:
        s += 1
print(s)
