def conseq(n):
  if len(bin(n)[3:].replace('0', '')) == 0:
    return None
  for i in range(2, n):
    if (2 * n) % i == 0:
      if i % 2 == 0 and ((2 * n) // i) % 2 == 1:
        if n // i - i // 2 >= 0:
          return list(range(n // i - i // 2 + 1, n // i + i // 2 + 1))
      elif i % 2 == 1:
        if n // i - i // 2 > 0:
          return list(range(n // i - i // 2, n // i + i // 2 + 1))


for i in range(int(input())):
  n = int(input())
  csq = conseq(n)
  print('IMPOSSIBLE' if not csq else '{} = {}'.format(
      n, ' + '.join(map(str, csq))))
