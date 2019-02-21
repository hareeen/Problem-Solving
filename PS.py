def legal(l):
    ind0=l.index(0)
    if ind0==0:
        return False
    targ=l[ind0-1]+1
    if max(l)<targ:
        return False
    targ_ind=l.index(targ)
    l[ind0], l[targ_ind] = l[targ_ind], l[ind0]
    return l
