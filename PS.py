v=[];exec("v+=[['.O|-\\/<v>^'['.O-|/\\^<v>'.index(e)]for e in input()[::-1]]];"*int(input().split()[0]))
for i in zip(*v):print(*i,sep='')