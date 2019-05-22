def main():
  l = []
  s = list(map(ord, input().upper()))
  for i in range(65, 65 + 26):
    l.append((s.count(i), chr(i)))
  l.sort(reverse=True)
  if l[0][0]==l[1][0]:
    print('?')
  else:
    print(l[0][1])


main()
