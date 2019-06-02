n=int(input());x=1;z=3;exec("x,z=z,z+x*2;"*(n-2));print(1 if n==1 else z%10007)
