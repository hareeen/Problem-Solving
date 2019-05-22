def main():
  tc = int(input())
  for _ in range(tc):
    n, s = input().split()
    print(''.join(map(lambda x: x * int(n), list(s))))


main()
