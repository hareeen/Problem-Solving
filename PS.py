n,l=map(int,input().split())

flag=False
for i in range(l,101):
	if i%2==1 and n%i==0:
		st=(n//i)-(i//2)
		if st>=0:
			print(' '.join(map(str,range(st,st+i))))
			flag=True
			break
	elif i%2==0 and (2*n)%i==0:
		t=(2*n)//i
		if t%2==0: continue
		st=(t//2)-(i//2)+1
		if st>=0:
			print(' ' .join(map(str,range(st,st+i))))
			flag=True
			break

if not flag: print(-1)
