def main():
  n = int(input()) - 1
  l = [(0, 1)]
  for _ in range(n):
    l.append((sum(l[-1]), l[-1][0]))
  print(sum(l[-1]))


main()
