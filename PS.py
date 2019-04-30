from math import sqrt, floor, ceil


def get_min_tup(n):
  min_p = (0, 0)
  m = 2.5
  for i in range(1, floor(sqrt(n)) + 1):
    if n % i == 0:
      cp = (1 / float(i)) + (float(i) / float(n))
      if cp < m:
        m = cp
        min_p = (i, n // i)
  return (m, min_p)


def main():
  min_p = (0, 0, 0)
  m = 3.5
  N = int(input())
  for i in range(1, floor(sqrt(N)) + 1):
    if N % i == 0:
      gmt = get_min_tup(N // i)
      cp = (1 / float(i)) + gmt[0]
      if cp < m:
        m = cp
        min_p = gmt[1] + (i,)
  print(' '.join(map(str, min_p)))


main()
