def process(case_num):
  N = int(input())
  s = ''.join(map(lambda x: '0' if x == 'O' else '1', input()))
  res = []
  for i in range(N):
    res.append(chr(int(s[8 * i:8 * (i + 1)], 2)))
  print('Case #{}: {}'.format(case_num + 1, ''.join(res)))


def main():
  TC = int(input())
  for _ in range(TC):
    process(_)


main()
