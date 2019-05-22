def main():
  l=[1,1]
  for i in range(2,int(input())+1):
    l.append((l[-1]+l[-2])%10007)
  print(l[-1])


main()
